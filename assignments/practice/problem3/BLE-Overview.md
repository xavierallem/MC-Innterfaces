# BLE Summary 

BLE is the low energy form of the conventional Bluetooth protocol. Bluetooth is 
used to communicate between two devices.

BLE or Bluetooth low energy has 2 modes 
1. GAP 
2. GATT

**Note**: BLE and Bluetooth are separate and do not confuse between them.

## GAP
The GAP layer of the Bluetooth low energy protocol stack is responsible for connection functionality. 

The devices in the GAP profile work as an observer and broadcaster. See the state diagram for more 
![image72](uploads/0e864659bc21066f4e195d3efc040538/image72.jpeg)

For GAP the Bluetooth stack defines the uuid's for each information exported by the device.

[Assigned numbers for GAP](https://www.bluetooth.com/specifications/assigned-numbers/generic-access-profile/)

## GATT

GATT layer of the Bluetooth low energy protocol stack is used by the application for data communication between two connected devices. Data is passed and stored in the form of characteristics/attribute which are stored in memory on the Bluetooth low energy device.

When two devices are connected, from a GATT view, the devices are in either two roles
1. GATT server - the device containing the characteristic/attribute database that is being read or written by a GATT client.
2. GATT client - he device that is reading or writing data from or to the GATT server.

### GATT Characteristics and Attributes

Characteristics as groups of attributes. Attributes are the information actually transferred between devices. 

#### GATT Services and Profile
GATT services are a collection of Characteristics. And multiple services can be grouped into profiles.


GATT services are used to communicate with the devices once the connection is established using GAP

[List of predefined GATT attributes](https://www.bluetooth.com/specifications/gatt/characteristics/)

### Advanced GAP 
GAP can also be used for exchanging data without connecting to the device it is more of mass broadcasting of data than one-on-one data transfer


### GATT services using BlueZ cli 

Steps
1. Connect to the device using the device MAC id
1. Once connected the GATT services/attributes will be printed on the device  
1. Select which attribute you want to read 
1. Read the attribute to get the attribute.


### CLI Commands for bluetooth
```sh
sudo bluetoothctl
connect { MAC addr }
select-attribute { attribute id }
read  
``` 

Alternatively the same can be achieved using hcitool too.

```
# For Scanning LE devices
sudo hcitool lescan
# Connecting to devcies
sudo gatttol -b {mac-addr of the device} -I
connect
# Writing into a characteristic 
char-write-req 000f 0100
# Reading characterstic 
char-read-req 000f
```
