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

#ifndef bme280.h
#define bme260.h


/*Linking*/
extern void begin(void);

extern float getTemperature(void);

extern float getPressure(void);

extern float getHumidity(void);

extern float getAltitude(void);









#endif