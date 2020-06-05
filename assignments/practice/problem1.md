# Problem 1

### Goal : Write code for ADS1115 16-bit ADC module using Shunya Interfaces on Raspberry Pi 4

### Description

Convert Arduino API's into Shunya Interfaces API's for ADS1115 DAC Arduino library. 
Write code to interface ADS1115 DAC with RPI 4 over I2C and read digital values from all the channels form the ADC.

Please use Arduino ADS1115 library as reference. 

- [ADS1115 Arduino library](https://github.com/adafruit/Adafruit_ADS1X15)


### For Example: 

Lets say 
#### Given (Input)
that the ADS1115 module is connected to the RPI4 using I2C, the example code when run
#### Then (output)
should print 16-bit digital value(0-65536) read from Channels 1, 2, 3 & 4 on separate lines.


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code must be in C.
- Code must be compiled in the Shunya OS docker container.

#### Note: Documentation of the whole program is a must criteria for the completion of the Assignment.