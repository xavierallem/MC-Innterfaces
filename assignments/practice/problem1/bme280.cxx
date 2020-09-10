/** @file <file_name>.c
 *  @brief Give a description of the file 
 *  
 *  Give full description of the file 
 *  
 *  @author Full name of the author 
 *  @bug List Any bugs found in the file  
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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Project Includes --- */
#include <shunyaInterfaces.h>
#include <Wire.h>
#include <bme280.h>


#define seaLevel (1013.25)

#define Addr 0x76
double cTemp = 0, fTemp = 0, pressure = 0, humidity = 0;
double t_fine=0;

/* 
 *  @brief Description on Begin
 *  
 *  Initializes the i2c connections 
 * a
 *
 *  @return 0
 */

void begin(){
if(!wireBegin()){
    printf("Error initializing i2c ! \n");

}
else
{
    printf("Sucessfully Initialized i2c !\n");
}

printf("Remember to initialize temperature first !\n");

}
/* 
 *  @brief Description on getTemperature
 *  
 *  Calulates the temperature
 * 
 *
 *  @return cTemp
 */

float getTemperature(){
unsigned int b1[24];
unsigned int data[8];
int dig_H1 = 0;
for(int i = 0; i < 24; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((136+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 24 bytes of data
if(wireAvailable() == 1)
{
b1[i] = wireRead();
}
}
// Convert the data
// temp coefficents
int dig_T1 = (b1[0] & 0xff) + ((b1[1] & 0xff) * 256);
int dig_T2 = b1[2] + (b1[3] * 256);
int dig_T3 = b1[4] + (b1[5] * 256);

// Start I2C Transmission
wireBeginTransmission(Addr);
// Select control measurement register
wireWrite(0xF4);
// Normal mode, temp and pressure over sampling rate = 1
wireWrite(0x27);
// Stop I2C Transmission
wireEndTransmission();
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select config register
wireWrite(0xF5);
// Stand_by time = 1000ms
wireWrite(0xA0);
// Stop I2C Transmission
wireEndTransmission();
for(int i = 0; i < 8; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((247+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 8 bytes of data
if(wireAvailable() == 1)
{
data[i] = wireRead();
}
}

// Convert temperature data to 19-bits
long adc_t = (((long)(data[3] & 0xFF) * 65536) + ((long)(data[4] & 0xFF) * 256) + (long)(data[5] & 0xF0)) / 16;

// Temperature offset calculations
double var1 = (((double)adc_t) / 16384.0 - ((double)dig_T1) / 1024.0) * ((double)dig_T2);
double var2 = ((((double)adc_t) / 131072.0 - ((double)dig_T1) / 8192.0) * (((double)adc_t)/131072.0 - ((double)dig_T1)/8192.0)) * ((double)dig_T3);
 t_fine = (long)(var1 + var2);
double cTemp = (var1 + var2) / 5120.0;

return cTemp;

}
/* 
 *  @brief Description on getPressure
 *  
 *  Calculates Pressure
 * 
 *
 *  @return pressure
 */
float getPressure(){
unsigned int b1[24];
unsigned int data[8];
int dig_H1 = 0;
for(int i = 0; i < 24; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((136+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 24 bytes of data
if(wireAvailable() == 1)
{
b1[i] = wireRead();
}
}
// Convert the data
int dig_P1 = (b1[6] & 0xff) + ((b1[7] & 0xff ) * 256);
int dig_P2 = b1[8] + (b1[9] * 256);
int dig_P3 = b1[10] + (b1[11] * 256);
int dig_P4 = b1[12] + (b1[13] * 256);
int dig_P5 = b1[14] + (b1[15] * 256);
int dig_P6 = b1[16] + (b1[17] * 256);
int dig_P7 = b1[18] + (b1[19] * 256);
int dig_P8 = b1[20] + (b1[21] * 256);
int dig_P9 = b1[22] + (b1[23] * 256);

// Start I2C Transmission
wireBeginTransmission(Addr);
// Select control measurement register
wireWrite(0xF4);
// Normal mode, temp and pressure over sampling rate = 1
wireWrite(0x27);
// Stop I2C Transmission
wireEndTransmission();
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select config register
wireWrite(0xF5);
// Stand_by time = 1000ms
wireWrite(0xA0);
// Stop I2C Transmission
wireEndTransmission();
for(int i = 0; i < 8; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((247+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 8 bytes of data
if(wireAvailable() == 1)
{
data[i] = wireRead();
}

}

// Convert pressure  data to 19-bits
long adc_p = (((long)(data[0] & 0xFF) * 65536) + ((long)(data[1] & 0xFF) * 256) + (long)(data[2] & 0xF0)) / 16;

// Pressure offset calculations
double var1 = ((double)t_fine / 2.0) - 64000.0;
double var2 = var1 * var1 * ((double)dig_P6) / 32768.0;
var2 = var2 + var1 * ((double)dig_P5) * 2.0;
var2 = (var2 / 4.0) + (((double)dig_P4) * 65536.0);
var1 = (((double) dig_P3) * var1 * var1 / 524288.0 + ((double) dig_P2) * var1) / 524288.0;
var1 = (1.0 + var1 / 32768.0) * ((double)dig_P1);
double p = 1048576.0 - (double)adc_p;
p = (p - (var2 / 4096.0)) * 6250.0 / var1;
var1 = ((double) dig_P9) * p * p / 2147483648.0;
var2 = p * ((double) dig_P8) / 32768.0;
double pressure = (p + (var1 + var2 + ((double)dig_P7)) / 16.0) / 100 ;

return pressure;

}
/* 
 *  @brief Description on getHumidity
 *  
 *  Calculates Humidity
 * 
 *
 *  @return humidity
 */
float getHumidity(){
unsigned int b1[24];
unsigned int data[8];
int dig_H1 = 0;
for(int i = 0; i < 7; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((225+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 7 bytes of data
if(wireAvailable() == 1)
{
b1[i] = wireRead();
}
}
// Convert the data
// humidity coefficents
int dig_H2 = b1[0] + (b1[1] * 256);
int dig_H3 = b1[2] & 0xFF ;
int dig_H4 = (b1[3] * 16) + (b1[4] & 0xF);
int dig_H5 = (b1[4] / 16) + (b1[5] * 16);
int dig_H6 = b1[6];
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite(161);
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 1 byte of data
if(wireAvailable() == 1)
{
dig_H1 = wireRead();
}
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select control humidity register
wireWrite(0xF2);
// Humidity over sampling rate = 1
wireWrite(0x01);
// Stop I2C Transmission
wireEndTransmission();

// Start I2C Transmission
wireBeginTransmission(Addr);
// Select config register
wireWrite(0xF5);
// Stand_by time = 1000ms
wireWrite(0xA0);
// Stop I2C Transmission
wireEndTransmission();
for(int i = 0; i < 8; i++)
{
// Start I2C Transmission
wireBeginTransmission(Addr);
// Select data register
wireWrite((247+i));
// Stop I2C Transmission
wireEndTransmission();
// Request 1 byte of data
wireRequestFrom(Addr, 1);
// Read 8 bytes of data
if(wireAvailable() == 1)
{
data[i] = wireRead();
}
}
// Convert the humidity data
long adc_h = ((long)(data[6] & 0xFF) * 256 + (long)(data[7] & 0xFF));
// Humidity offset calculations
double var_H = (((double)t_fine) - 76800.0);
var_H = (adc_h - (dig_H4 * 64.0 + dig_H5 / 16384.0 * var_H)) * (dig_H2 / 65536.0 * (1.0 + dig_H6 / 67108864.0 * var_H * (1.0 + dig_H3 / 67108864.0 * var_H)));
double humidity = var_H * (1.0 - dig_H1 * var_H / 524288.0);
if(humidity > 100.0)
{
humidity = 100.0;
}
else if(humidity < 0.0)
{
humidity = 0.0;
}

return humidity;


}
/* 
 *  @brief Description on getAltitude
 *  
 *  Calculates Altiude
 * 
 *
 *  @return calculate Altitude
 */
 
 float getAltitude(){

     float atmospheric = getPressure() / 100.0F;
  return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 0.1903));
}


