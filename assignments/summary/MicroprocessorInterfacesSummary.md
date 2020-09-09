# Microprocessor Interfaces

## GPIO 

A GPIO (general-purpose input/output) port handles both incoming and outgoing digital signals. GPIO can be used as Input or Output.

![Gp](assignments/Assets/GPIO-Block-Diagram-3_Q640.jpg)


## Universal Asynchronous Receiver Transmitter(UART)


![U](assignments/Assets/Introduction-to-UART-Data-Transmission-Diagram.png)

![U](assignments/Assets/Introduction-to-UART-Basic-Connection-Diagram.png)

**UART** is a Universal Asynchronous Receiver Transmitter used for serial communication in embedded systems. It has two lines Tx(Transmit) and Rx(Receive).wo UARTs can communicate directly. UART can convert parallel data coming from controller device into the serial 
data it also add extra bits to it which are start,parity and stop bits.

![U](assignments/Assets/UART-Communication.jpg)

- **Start Bit**:- UART data transmission line held at high logic level when it is not transferring any data. To start transmission,
the transmitting UART pulls the transmission line from high to low for one clock cycle

- **Data Bits**:- The data frame contains the data which is to be transferred

- **Parity Bit**:- Parity is used to check evenness or oddness of the data frame.

- **Stop Bit**:- It indicates the end of one packet. 


### Working of UART

- The transmitting UART receives data in parallel from the data bus.
- The transmitting UART adds the start bit, parity bit, and the stop bit(s) to the data frame.
- The entire packet is sent serially from the transmitting UART to the receiving UART. The receiving UART samples the data line at the pre-configured baud rate.
- The receiving UART discards the start bit, parity bit, and stop bit from the data frame.
- The receiving UART converts the serial data back into parallel and transfers it to the data bus on the receiving end


### Advantages 


- Requires only two wires for full duplex data transmission.
- No need for clock or any other timing signal.
- Parity bit ensures basic error checking is integrated in to the data packet frame.


### Disadvantages



- Size of the data in the frame is limited.
- Speed for data transfer is less compared to parallel communication.
- Transmitter and receiver must agree to the rules of transmission and appropriate baud rate must be selected.

### Implementation in Linux

Typically the path of the file is /dev/ttyxxx where xxx is the UART interface
name. One board may contain many UART interfaces, and all these UART interfaces are given names.

```bash
/dev/ttyAMA0
/dev/ttyAMA6


```

## Serial Peripheral Interface(SPI)

![Sl](assignments/Assets/Introduction-to-SPI-Master-and-Slave.png)

SPI is most commonly used for interfacing of SD card modules, RFID card reader modules, and 2.4 GHz wireless transmitter/receivers with micro-controllers.
SPI is immune to interruption while communication

The Pins are,

- **MOSI (Master Output/Slave Input)** 
- **MISO (Master Input/Slave Output)** 
- **SCLK (Clock)**
- **SS/CS (Slave Select/Chip Select)**


### Clock (SCLK)

System Clock synchronizes the output of data from the master to the sampling of bits by the slave. One bit data is transferred in each clock cycle. 
The speed of communication is determined by frequency of clock signal. 

### Slave Select(SS/CS)

In SPI communication Slave Select is used to select the slave which master wants to communicate with, 
master sends logic low signal on SS(active low) line as it activate at logic low

### Multiple Slaves

SPI can set up to for only one master and one slave but it has two ways

- Master with separate Slave Select

![SS](assignments/Assets/Introduction-to-SPI-Multiple-Slave-Configuration-Separate-Slave-Select-768x787.png)

- Master with Daisy-Chained

![SS](assignments/Assets/Introduction-to-SPI-Multiple-Slave-Configuration-Daisy-Chained-768x78132254.png)

### MOSI & MISO

The master sends data to the slave bit by bit, in serial through the MOSI line. The slave receives the data sent from the master at the MOSI pin


### Working of SPI

![Ds](assignments/Assets/SPI-Protocol-Data-Transmission-and-Connection.jpg)


### Advantages

- No start and stop bits, so the data can be streamed continuously without interruption.
- No complicated slave addressing system like I2C.
- Higher data transfer rate than I2C (almost twice as fast).
- Separate MISO and MOSI lines, so data can be sent and received at the same time.


### Disadvantages 

- Uses four wires (I2C and UARTs use two).
- No acknowledgement that the data has been successfully received (I2C has this).
- No form of error checking like the parity bit in UART.
- Only allows for a single master.


