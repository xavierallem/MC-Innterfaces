# Problem 1

### Purpose : Write code for reading data from the RISHI Meter 3430 using Shunya Interfaces modbus API's

## Data that needs to be read from the device
1. AC current 
1. Voltage 
1. Power
1. Active energy (kWhr), 
1. Reactive energy (kVArhr) 
1. Apparent energy (kVAhr) 
1. THD of voltage


### Description
- Follow the approach taken in the Module 1 and write code for reading the above data from the meter using Modbus.
- For Meter connections using RS485 assume that the meter will be connected to uart device node `/dev/ttyAMA0` 


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code must be in C.
- Code must be compiled in the Shunya OS docker container.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.