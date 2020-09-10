# Summary 

Shunya interfaces for programming the microprocessor Interfaces are given below

## Shunya Interfaces Core API

### GPIO API

- **pinmode()**:- Sets the direction of the GPIO pin to INPUT or OUTPUT

*eg.*
```c++
 pinmode(1,INPUT);
```
- **digitalWrite()**:- Sets the digital value of the GPIO pin

*eg.*
```c++
 digitalWrite(1,HIGH);
```
- **digitalRead()**:- Read digital value of the GPIO pin

*eg.*
```c++
 digitalRead(3);
```

### Interrupt API

- **attachInterrupt()**:- Sets the digital value of the GPIO pin with interrupt exe of isr and its mode.

*eg.*
```c++
attachInterrupt(30, isr, INT_EDGE_BOTH);
```

### PWM API

- **softPwmBegin()**:- Start the PWM at a initial duty cycle and a defined Pulse width

*eg.*
```c++
 softPwmWrite(40, 60);
```

- **softPwmWrite()**:- Change the PWM duty cycle.

*eg.*
```c++
 softPwmWrite(40, 60);
```

- **softPwmEnd()**:- Stop the PWM on a pin.

*eg.*
```c++
 softPwmEnd(40);
```

### Delay API


- **delay()**:- Code sleeps for given milliseconds

*eg.*
```c++
delay(50);
```

- **delayMicroseconds()**:- Code sleeps for given microseconds

*eg.*
```c++
delayMicroseconds(50);
```


### I2C API


- **wireBegin()**:- Initializes the I2C device
*eg.*
```c++
wireBegin(1); //1 is the board I2C 1
```

- **wireBeginTransmission()**:- Starts I2C communication

*eg.*
```c++
wireBeginTransmission(0x23); //0x23 is the device address

```

- **wireWrite()**:- Send data to the I2C device

*eg.*
```c++
wireWrite(1);

```

- **wireRequestFrom()**:- Request Data from the I2C device

*eg.*
```c++
wireRequestFrom(0x23,5); //0x23 is the address of the I2C device

```

- **wireAvailable()**:- Check number of bytes available to read from the device

*eg.*
```c++
 ret = wireAvailable();
 
```

- **wireRead()**:- Read from the I2C device.

*eg.*
```c++
 val = wireRead();
 
```

- **wireEndTransmission()**:- End communication to the I2C device

*eg.*
```c++
 wireEndTransmission();
 
```

- **wireEnd()**:- De-initialize the I2C device

*eg.*
```c++
 wireEnd();
 
```

### SPI API


- **spiBegin()**:- Initializes the SPI bus.

*eg.*
```c++
  spiBegin();
 
```


- **spiBeginTransaction()**:- Starts SPI communication with its clock frequemcy , Bit order and mode

*eg.*
```c++
 spiBeginTransaction(50000, MSBFIRST, 0);
 
```

- **spiTransfer()**:- Write 8 bits (1 byte) of data to the SPI bus.

*eg.*
```c++
 spiTransfer(0x5D);
 
```

- **spiEndTransaction()**:- Ends the SPI communication.

*eg.*
```c++
  spiEndTransaction();
 
```

- **spiEnd()**:- Ends the SPI device.

*eg.*
```c++
  spiEnd();
 
```

- **spiSetBitOrder()**:-  Set the bit order to MSB or LSB first.

*eg.*
```c++
  spiSetBitOrder(MSBFIRST);
 
```

- **spiSetClock()**:-   Set SPI clock rate

*eg.*
```c++
  spiSetClock(500000);
 
```

- **spiSetDataMode()**:-   Set SPI mode

*eg.*
```c++
  spiSetDataMode(0);//0 to 3
 
```

### UART API


- **serialOpen()**:-   Initialize the serial port

*eg.*
```c++
  serialOpen("1",115200)
 
```

- **serialEnd()**:-  Release the serial port

*eg.*
```c++
  serialEnd()
 
```

- **serialRead()**:- Get a single character from the serial device

*eg.*
```c++
  serialRead()
 
```

- **serialPrint()**:- Print over Serial interface

*eg.*
```c++
  serialPrint("Hello World");
 
```

- **serialPrintln()**:- Print over Serial interface with a new line

*eg.*
```c++
  serialPrintln("Hello World");
 
```

- **serialWrite()**:- Send a single character to the serial port

*eg.*
```c++
  serialWrite("I");
 
```

- **serialAvailable()**:- Return the number of bytes of data available to be read in the serial port

*eg.*
```c++
  serialAvailable()
 
```

- **serialFlush()**:- Flush the serial buffers (both tx & rx)

*eg.*
```c++
 serialFlush()
 
```