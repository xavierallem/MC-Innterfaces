# Problem 3

## Purpose: Write code for interacting with Bluetooth/BLE devices 

## Expected Outcomes: 
1. C/CPP code called `ble.cxx` which contain functions that 
    1. Pair and Connect to Bluetooth/BLE Device.
    1. Read data from Specified GATT service.
    1. Write data to Specified GATT service.
1. C/CPP code which is an example code called `ble_example.cxx` that contains the `main` function that "Connects to a BLE device and reads GATT attributes from the device."

## Steps to complete:

1. **Get an Overview of the BLE protocol by reading [Overview of BLE](problem3/BLE-Overview.md)**

2. **Study [Bluez Dbus API](https://git.kernel.org/pub/scm/bluetooth/bluez.git/tree/doc) So you can code using BLUEZ** 
   
3. Codes have been written for accomplishing the above tasks, you will find these codes in the folder `problem3/sampleCodes/`, but these codes 
    1. May contain logical errors 
    2. May contain memory leaks 
    3. Many common functions are repeated in the files. 
    4. Coding style is not followed.

4. You have to convert the code in the `sampleCodes` folder into one single C/CPP called `ble.cxx` code which contains functions 
```c
btConnect();
bleGattRead();
bleGattWrite();
```
While converting you will have to remove errors like
    1. Logical errors 
    2. Memory leaks 
    3. Redundant functions. 
    4. Incorrect Coding style.

5. Write example code that called `ble_example.cxx` that uses the functions in the `ble.cxx` file to connect to a BLE device and read dummy GATT attribute from the device.

### Acceptance Criteria 
This is the criteria to accept the assignment.
- The code must be divided into functions 
- **Must** have documentation for using the program.
- Code **Must** follow the Coding Standards.
