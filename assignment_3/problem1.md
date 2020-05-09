# Problem 1

### Goal : Write code for MPC4725 12-bit DAC module using Shunya Interfaces on Raspberry Pi 4

### Description

Convert Arduino API's into Shunya Interfaces API's for MPC4725 DAC Arduino library. 
Write code to interface MPC4725 DAC with RPI 4 over I2C and generate 0-5V output when given 
respective 12-bit Input.

Please use Arduino MPC4725 library as reference. 

- [MPC4725 Arduino library](https://github.com/adafruit/Adafruit_MCP4725/)


### For Example: 

Lets say 
#### Given (Input)
that the  MPC4725 module is connected to the RPI4 using I2C, the example code when run
#### Then (output)
should loop and generate 0-5V with 0.02 V steps and a delay of 100 ms between
each loop iteration.


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code can be either in C or in CPP.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.