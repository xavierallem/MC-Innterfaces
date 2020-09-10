# Summary 

Shunya interfaces for programming the microprocessor Interfaces are given below

## Shunya Interfaces Core API

### GPIO API

- **pinmode()**:- Sets the direction of the GPIO pin to INPUT or OUTPUT

eg.
```c++
 pinmode(1,INPUT);
```
- **digitalWrite()**:- Sets the digital value of the GPIO pin

eg.
```c++
 digitalWrite(1,HIGH);
```
- **digitalRead()**:- Read digital value of the GPIO pin

eg.
```c++
 digitalRead(3);
```

### Interrupt API

- **attachInterrupt()**:- Sets the digital value of the GPIO pin with interrupt exe of isr and its mode.

eg.
```c++
attachInterrupt(30, isr, INT_EDGE_BOTH);
```

### PWM API

- **softPwmBegin()**:- Start the PWM at a initial duty cycle and a defined Pulse width

eg.
```c++
 softPwmWrite(40, 60);
```

- **softPwmWrite()**:-Change the PWM duty cycle.

eg.
```c++
 softPwmWrite(40, 60);
```

- **softPwmEnd()**:-Stop the PWM on a pin.

eg.
```c++
 softPwmEnd(40);
```

