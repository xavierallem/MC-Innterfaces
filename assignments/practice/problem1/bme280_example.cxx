/** @file bme280_example.c
 *  @brief Give a description of the file 
 *  
 *  Calculates Temperature, Humidity, Pressure, Altitude 
 *  
 *  @author Allen  
 *  @bug Didn't find any  
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
  printf("----Starting----");
  begin();
/*----Temperature Storing variable-------*/
float temperature = getTemperature();
/*------Pressure Storing Variable----------*/
float pressure = getPressure();
/*------Humidity Storing Variable ----------*/
int8_t humidity = getHumidity();
/*-------Altitude storing Variable---------*/
float altitude = getAltitude();

/*-------Print The Values---------*/
printf(" The Temperature is : %f \n",temperature);
printf("The Pressure is : %f \n",pressure);
printf("The humidity is : %d \n",humidity);
printf("The Altitude is : %f \n",altitude);

       
        return 0;
        
}