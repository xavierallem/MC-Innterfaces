
/*
@file           pro1.cpp 
@description    Read value of charachteristic from GATT service   

@author         Chanchal Choudhary
*
* gcc read_gatt.c `pkg-config --cflags glib-2.0 gio-2.0` -Wall -Wextra -o read_gatt `pkg-config --libs glib-2.0 gio-2.0`
*
*/


/* 
***************************************
Initailization block
***************************************
*/

#include <glib.h>
#include <gio/gio.h>
#include <signal.h>
#include <stdio.h>

GMainLoop *loop;
GDBusConnection *con;
static void bluez_property_value(const gchar *key, GVariant *value)
{
	const gchar *type = g_variant_get_type_string(value);

	g_print("\t%s : ", key);
	switch(*type) {
		case 'o':
		case 's':
			g_print("%s\n", g_variant_get_string(value, NULL));
			break;
		case 'b':
			g_print("%d\n", g_variant_get_boolean(value));
			break;
		case 'u':
			g_print("%d\n", g_variant_get_uint32(value));
			break;
		case 'a':
		/* TODO Handling only 'as', but not array of dicts */
			if(g_strcmp0(type, "as"))
				break;
			g_print("\n");
			const gchar *uuid;
			GVariantIter i;
			g_variant_iter_init(&i, value);
			while(g_variant_iter_next(&i, "s", &uuid))
				g_print("\t\t%s\n", uuid);
			break;
		default:
			g_print("Other\n");
			break;
	}
}

typedef void (*method_cb_t)(GObject *, GAsyncResult *, gpointer);
static int bluez_adapter_call_method(const char *method, GVariant *param, method_cb_t method_cb)
{
	g_dbus_connection_call(con,
			     "org.bluez",
			/* TODO Find the adapter path runtime */
			     "/org/bluez/hci0",
			     "org.bluez.Adapter1",
			     method,
			     param,
			     NULL,
			     G_DBUS_CALL_FLAGS_NONE,
			     -1,
			     NULL,
			     method_cb,
			     (void *)method);
	return 0;
}

static void bluez_result_async_cb(GObject *con,
				  GAsyncResult *res,
				  gpointer data)
{
	const gchar *key = (gchar *)data;
	GVariant *result = NULL;
	GError *error = NULL;

	result = g_dbus_connection_call_finish((GDBusConnection *)con, res, &error);
	if(error != NULL) {
		g_print("Unable to get result: %s\n", error->message);
		return;
	}

	if(result) {
		result = g_variant_get_child_value(result, 0);
		bluez_property_value(key, result);
	}
	g_variant_unref(result);
}

static void bluez_device_appeared(GDBusConnection *sig,
				const gchar *sender_name,
				const gchar *object_path,
				const gchar *interface,
				const gchar *signal_name,
				GVariant *parameters,
				gpointer user_data)
{
	(void)sig;
	(void)sender_name;
	(void)object_path;
	(void)interface;
	(void)signal_name;
	(void)user_data;

	GVariantIter *interfaces;
	const char *object;
	const gchar *interface_name;
	GVariant *properties;

	g_variant_get(parameters, "(&oa{sa{sv}})", &object, &interfaces);
	while(g_variant_iter_next(interfaces, "{&s@a{sv}}", &interface_name, &properties)) {
		if(g_strstr_len(g_ascii_strdown(interface_name, -1), -1, "device")) {
			g_print("[ %s ]\n", object);
			const gchar *property_name;
			GVariantIter i;
			GVariant *prop_val;
			g_variant_iter_init(&i, properties);
			while(g_variant_iter_next(&i, "{&sv}", &property_name, &prop_val))
				bluez_property_value(property_name, prop_val);
			g_variant_unref(prop_val);
		}
		g_variant_unref(properties);
	}
	return;
}

#define BT_ADDRESS_STRING_SIZE 18
static void bluez_device_disappeared(GDBusConnection *sig,
				const gchar *sender_name,
				const gchar *object_path,
				const gchar *interface,
				const gchar *signal_name,
				GVariant *parameters,
				gpointer user_data)
{
	(void)sig;
	(void)sender_name;
	(void)object_path;
	(void)interface;
	(void)signal_name;

	GVariantIter *interfaces;
	const char *object;
	const gchar *interface_name;

	char address[BT_ADDRESS_STRING_SIZE];	//Enter  mac address
	printf("Enter MAC address of device you want to connect:");
	scanf("%s",address);

	g_variant_get(parameters, "(&oas)", &object, &interfaces);
	while(g_variant_iter_next(interfaces, "s", &interface_name)) {
		if(g_strstr_len(g_ascii_strdown(interface_name, -1), -1, "device")) {
			int i;
			char *tmp = g_strstr_len(object, -1, "dev_") + 4;

			for(i = 0; *tmp != '\0'; i++, tmp++) {
				if(*tmp == '_') {
					address[i] = ':';
					continue;
				}
				address[i] = *tmp;
			}
			g_print("\nDevice %s removed\n", address);
			g_main_loop_quit((GMainLoop *)user_data);
		}
	}
	return;
}

static void bluez_signal_adapter_changed(GDBusConnection *conn,
					const gchar *sender,
					const gchar *path,
					const gchar *interface,
					const gchar *signal,
					GVariant *params,
					void *userdata)
{
	(void)conn;
	(void)sender;
	(void)path;
	(void)interface;
	(void)userdata;

	GVariantIter *properties = NULL;
	GVariantIter *unknown = NULL;
	const char *iface;
	const char *key;
	GVariant *value = NULL;
	const gchar *signature = g_variant_get_type_string(params);

	if(strcmp(signature, "(sa{sv}as)") != 0) {
		g_print("Invalid signature for %s: %s != %s", signal, signature, "(sa{sv}as)");
		goto done;
	}

	g_variant_get(params, "(&sa{sv}as)", &iface, &properties, &unknown);
	while(g_variant_iter_next(properties, "{&sv}", &key, &value)) {
		if(!g_strcmp0(key, "Powered")) {
			if(!g_variant_is_of_type(value, G_VARIANT_TYPE_BOOLEAN)) {
				g_print("Invalid argument type for %s: %s != %s", key,
						g_variant_get_type_string(value), "b");
				goto done;
			}
			g_print("Adapter is Powered \"%s\"\n", g_variant_get_boolean(value) ? "on" : "off");
		}
		if(!g_strcmp0(key, "Discovering")) {
			if(!g_variant_is_of_type(value, G_VARIANT_TYPE_BOOLEAN)) {
				g_print("Invalid argument type for %s: %s != %s", key,
						g_variant_get_type_string(value), "b");
				goto done;
			}
			g_print("Adapter scan \"%s\"\n", g_variant_get_boolean(value) ? "on" : "off");
		}
	}
done:
	if(properties != NULL)
		g_variant_iter_free(properties);
	if(value != NULL)
		g_variant_unref(value);
}

static int bluez_adapter_set_property(const char *prop, GVariant *value)
{
	GVariant *result;
	GError *error = NULL;

	result = g_dbus_connection_call_sync(con,
					     "org.bluez",
					     "/org/bluez/hci0",
					     "org.freedesktop.DBus.Properties",
					     "Set",
					     g_variant_new("(ssv)", "org.bluez.Adapter1", prop, value),
					     NULL,
					     G_DBUS_CALL_FLAGS_NONE,
					     -1,
					     NULL,
					     &error);
	if(error != NULL)
		return 1;

	g_variant_unref(result);
	return 0;
}

static int bluez_adapter_connect_device(char **argv)
{
	int rc;
	GVariantBuilder *b = g_variant_builder_new(G_VARIANT_TYPE_VARDICT);
	g_variant_builder_add(b, "{sv}", "Address", g_variant_new_string(argv[1]));
	GVariant *device_dict = g_variant_builder_end(b);
	g_variant_builder_unref(b);

	rc = bluez_adapter_call_method("ConnectDevice",
					g_variant_new_tuple(&device_dict, 1),
					bluez_result_async_cb);
	if(rc) {
		g_print("Not able to call ConnectDevice\n");
		return 1;
	}
	else
	g_print("\nDevice  Connected\n");

	return 0;
}

#define AGENT_PATH "/org/bluez/AutoPinAgent"
static int bluez_agent_call_method(const gchar *method, GVariant *param)
{
        GVariant *result;
        GError *error = NULL;

        result = g_dbus_connection_call_sync(con,
                                             "org.bluez",
                                             "/org/bluez",
                                             "org.bluez.AgentManager1",
                                             method,
                                             param,
                                             NULL,
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL,
                                             &error);
        if(error != NULL) {
		g_print("Register %s: %s\n", AGENT_PATH, error->message);
                return 1;
	}

        g_variant_unref(result);
        return 0;
}

static int bluez_register_autopair_agent(void)
{
	int rc;

	rc = bluez_agent_call_method("RegisterAgent", g_variant_new("(os)", AGENT_PATH, "NoInputNoOutput"));
	if(rc)
		return 1;

	rc = bluez_agent_call_method("RequestDefaultAgent", g_variant_new("(o)", AGENT_PATH));
	if(rc) {
		bluez_agent_call_method("UnregisterAgent", g_variant_new("(o)", AGENT_PATH));
		return 1;
	}

	return 0;
}

static void cleanup_handler(int signo)
{
	if (signo == SIGINT) {
		g_print("received SIGINT\n");
		g_main_loop_quit(loop);
	}
}


/* Create proxy object to access the DBUS API methods */
static int bluez_gatt_method(const char *method)
{
	GVariant *result;
	GError *error = NULL;

	result = g_dbus_connection_call_sync(con,
					     "org.bluez",
				
					     "/org/bluez/hci0",
					     "org.bluez.GattCharacteristic1", //GattCharachteristic1 has the GATT DBUS API
					     method,
					     NULL,
					     NULL,
					     G_DBUS_CALL_FLAGS_NONE,
					     -1,
					     NULL,
					     &error);
	if(error != NULL)
		return 1;

	g_variant_unref(result);
	return 0;
}

/* 
***************************************
Main body
***************************************
*/

int main(int argc, char **argv)
{
	
	int rc;
	guint prop_changed;
	guint iface_added;
	guint iface_removed;

	if(signal(SIGINT, cleanup_handler) == SIG_ERR)
		g_print("can't catch SIGINT\n");

	con = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, NULL);
	if(con == NULL) {
		g_print("Not able to get connection to system bus\n");
		return 1;
	}

	loop = g_main_loop_new(NULL, FALSE);

	prop_changed = g_dbus_connection_signal_subscribe(con,
						"org.bluez",
						"org.freedesktop.DBus.Properties",
						"PropertiesChanged",
						NULL,
						"org.bluez.Adapter1",
						G_DBUS_SIGNAL_FLAGS_NONE,
						bluez_signal_adapter_changed,
						NULL,
						NULL);

	iface_added = g_dbus_connection_signal_subscribe(con,
							"org.bluez",
							"org.freedesktop.DBus.ObjectManager",
							"InterfacesAdded",
							NULL,
							NULL,
							G_DBUS_SIGNAL_FLAGS_NONE,
							bluez_device_appeared,
							loop,
							NULL);

	iface_removed = g_dbus_connection_signal_subscribe(con,
							"org.bluez",
							"org.freedesktop.DBus.ObjectManager",
							"InterfacesRemoved",
							NULL,
							NULL,
							G_DBUS_SIGNAL_FLAGS_NONE,
							bluez_device_disappeared,
							loop,
							NULL);

	rc = bluez_adapter_set_property("Powered", g_variant_new("b", TRUE));
	if(rc) {
		g_print("Not able to enable the adapter\n");
		goto fail;
	}

	rc = bluez_register_autopair_agent();
	if(rc) {
		g_print("Not able to register default autopair agent\n");
		goto fail;
	}

	if(argc == 2) {
		rc = bluez_adapter_connect_device(argv);
		
		if(rc)
			goto fail;
	}

	/* Call ReadValue method to read value of charachteristic */
	rc = bluez_gatt_method("Readvalue");

        if(rc) {
        g_print("Not able to read\n");
        goto fail;
    	}

	g_main_loop_run(loop);

	rc = bluez_adapter_set_property("Powered", g_variant_new("b", FALSE));
	if(rc)
		g_print("Not able to disable the adapter\n");
	

fail:
	g_dbus_connection_signal_unsubscribe(con, prop_changed);
	g_dbus_connection_signal_unsubscribe(con, iface_added);
	g_dbus_connection_signal_unsubscribe(con, iface_removed);
	g_object_unref(con);

	return 0;


	 
}