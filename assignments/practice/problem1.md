# Problem 1

### Purpose : Write code for BME280 sensor connected to RPI 4 over I2C using Shunya Interfaces on Raspberry Pi 4

### Expected Outcomes
1. C/CPP code `bme280.c` which contains Functions for reading data from the BME280 sensor
1. C/CPP code `bme280_example.c` which contains the main function which calls the functions from the `bme280.c` file.
1. Document on how to use the functions from the `bme280.c`

### Description

Convert Arduino API's into Shunya Interfaces API's for BME280 Arduino library. 

Write code to interface BME280 sensor with RPI 4 over I2C and write code to get values from the sensor when these functions are called.

```c
float temperature = getTemperature();
float pressure = getPressure();
int8_t humidity = getHumidity();
float altitude = getAltitude();
```

### Inputs 
1. Bme280 Arduino library - https://github.com/adafruit/Adafruit_BME280_Library

## Important Notes 
1. BME280 can be used with either I2C or SPI interface, Please write code for I2C interface.
1. Please use the I2C and SPI API's Shunya Interfaces Core library.


### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
- Code can be either in C or in CPP.