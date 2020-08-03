# Problem 1

### Purpose : Write code to send Heartbeat message to an MQTT topic. 

### Outcomes
1. C Code which sends Heartbeat messages to the User specified server using MQTT 

### Description

Heartbeat messages are those messages that are sent to the cloud to say that the device is alive.

These messages are sent in JSON format so that these messages can be easily processed at the cloud.

- Sample Heartbeat JSON message
```json
 {
    "deviceId": "186b5",
    "timestamp": 1573002230757,
    "eventType": "heartbeat",
    "ipAddress": "192.0.2.0"
}
```

Currently we the architecture is that the cloud will have an MQTT broker, to which we send these messages. 


Write code to publish above JSON message as heartbeat message to the MQTT topic `"device/heartbeat"`

Use [paho MQTT client](https://github.com/eclipse/paho.mqtt.c) for sending MQTT messages.

To make a message we need to get the values for the keys of the JSON messages 

- for `deviceID` key, value should be read from a file at location `/etc/shunya/deviceid`
- for timestamp key, value should be UNIX timestamp 
- for `eventType`  key, value should always be `heartbeat`
- for `ipAddress` key, value should be read from the linux system.

These should be sent at a regular interval of `X` mins which will be defined by the user (take input from stdin).

The user will also define the URL (endpoint) of the MQTT server. (take input from stdin)

## Resources 
1. Unix timestamp - https://www.systutorials.com/how-to-get-the-epoch-timestamp-in-c/
2. Reading IP address in C - https://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code must be in C.
- Code must be compiled in the Shunya OS docker container.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.