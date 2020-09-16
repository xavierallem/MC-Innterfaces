/** @file <thingsboards_example.c
 *  @brief 
 *
 *  The code parses json file values to thingsboards
 *
 *  @author Allen
 *  @bug Didn't find any yet
 */

/*
 *#####################################################################
 *  Initialization block
 *  ---------------------
 *  This block contains initialization code for this particular file.
 *  It typically contains Includes, constants or global variables used
 *  throughout the file.
 *#####################################################################
 */

/* --- Standard Includes --- */
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* RapidJSON Includes */
#include <mqtt.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include "thingsboard.h"



/* --- Project Includes --- */
#include "thingsboard.h"

using namespace rapidjson;

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here
 *#####################################################################
 */


/**
 *  @brief Description on main
 *
 *  Connects , creates json doc
 * and publishes data
 *
 *  @return fp
 */

int main(){
    /* Connect to thingsboard */
    connectToThingsboard()
    /* Send Device info */
    notifyDeviceConnectToThingsboard("Raspi")
    /*Json file to be parsed*/
    const char* json = "{\"Temperature\":30,\"Humidity\":10}";
    /*Initializing document variable*/
    Document d;
    /*Parsing the json */
    d.Parse(json);
    /*Initializing buffer*/
    StringBuffer buffer;
    /*Wrtier stream-*/
    Writer<StringBuffer> writer(buffer);
    /* Write the JSON document `d` into the buffer`*/
    d.Accept(writer);
    /* Publish the json values*/
    publishTelemetryToThingsboard(buffer.GetString());
    /* Deisconnect device info */
    notifyDeviceConnectToThingsboard("Raspi")
    /* Disconnect from thingsboards*/
    disconnectFromThingsboard();

}