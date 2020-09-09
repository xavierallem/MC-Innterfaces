# Summary 


## Tips

### Power Suppy 

- Make sure to connect supply voltage matching the input voltage of the board
- Never connect a higher output(12V/3Amp) to a lower (5V/2Amp) input .
- Make sure all the connections are proper before supplying the voltage with proper connector.


### Handling

- Never do changes to the board while power is ON and do the changes when its turned OFF or Unplugged.
- Keeep the Board on flat surfaces and avoid wet hands while touching the board.
- Keep all electrical circuit contact points enclosed and dont touch the metal contacts.
- If the board becomes too hot try to cool it with a external usb fan.

### GPIO 

- Connection must be proper according to board logic and connect only according to that 5v or 3.3v else use converters.
- Use ressitors with LEDs
- Avoid changes while Board is ON
- Use motors with transistors and never connect  voltage higher than board voltage.


## Guidelines for using interfaces(UART,I2C,SPI)

### UART

- While connecting the Tx Rx pins ensure that they are connected properly
- f the device1 works on 5v and device2 works at 3.3v use voltage divider
- Senor interfacing using UART might require a protection circuit.


### I2C

- SDA and SDL lines must be protected by using pull-up registers on both lines.
- If you use the inbuilt pull-up registers in the board you won't need an external circuit for pull-up resistors


### SPI

- Spi is in default Push-pull mode however if you are using more than one slaves it is possible that the device2 can "hear" and "respond" to the master's communication with device1- which is a disturbance 
- To overcome this problem , we use a protection circuit with pullup resistors on each the Slave Select line(CS).
Resistors value can be between 1kOhm ~10kOhm . Generally 4.7kOhm resistor is used.