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

/* --- Project Includes --- */
#include <shunyaInterfaces.h>
#include <Wire.h>
#include <bme280.h>

/*
 *#####################################################################
 *  Process block
 *  -------------
 *  Solve all your problems here 
 *#####################################################################
 */

/*-------Create Object of driver----*/
BME280 bme;
unsigned long delayTime;

/** 
 *  @brief Description Func_1
 *  
 *  Initializing
 *
 *  @return  
 */
 void setup() {
    
    
    /*-------Variable for i2c---------*/
    unsigned status;
    
    /*-------Begin i2c---------*/
    status = bme.begin(0x76, &Wire2);  
    // You can also pass in a Wire library object like &Wire2
    
    if (!status) {
      /*---------Error Details-----------*/
        printf("Could not find a valid BME280 sensor, check wiring, address, sensor ID! \n");
        printf("SensorID was: 0x"); printf(bme.sensorID()); 
        printf("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
       
        while (1) delay(10);
    }
    
    printf("-- Starting --\n");
    

    printf("\n");
}
/** 
 *  @brief Description on main
 *  
 *  Initializes the i2c connections 
 * and Read and print the Values
 *
 *  @return 0
 */

int main (void)
{
  
setup();
/*----Temperature Storing variable-------*/
float temperature = bme.getTemperature();
/*------Pressure Storing Variable----------*/
float pressure = bme.getPressure();
/*------Humidity Storing Variable ----------*/
int8_t humidity = bme.getHumidity();
/*-------Altitude storing Variable---------*/
float altitude = bme.getAltitude();

/*-------Print The Values---------*/
printf(" The Temperature is : %f \n",temperature);
printf("The Pressure is : %f \n",pressure);
printf("The humidity is : %d \n",humidity);
printf("The Altitude is : %f \n",altitude);

       
        return 0;
        
}
