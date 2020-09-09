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

