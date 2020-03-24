# Problem 1

## Problem statement
Study all the interfaces of a board and write down the Linux file names in a YAML file.

### Steps 
1. Pick 3 unique boards from the [board list](https://docs.google.com/spreadsheets/d/1in0_qqWc5r-ngrlRduTemxfzUY_cOrZYDOE2uZ5Woqc/edit?usp=sharing) 
2. Study their interfaces by looking at their pinouts.
3. Write down all the details of the interfaces in the boardx.yaml where `x` is board 1 or 2 or 3.
4. Once done submit by pushing the branch with your full_name.

### YAML file 
1. YAML file should contain all the pins on the board with UART, SPI and I2C interfaces
2. For every pin the YAML file should contain the entry similar to this.
```yaml
pin 3: 
  i2c-details: 1
  spi-details: null
  uart-details: null
  pwm-details: null
```
Where the number `1` in front of the `i2c-details` key says that this pin 
corresponds to `/dev/i2c-1` device node in Linux. What the pin does i.e (SDA) etc 
can be written in the comments.

## Reference Links 
1. [YAML Syntax](https://learnxinyminutes.com/docs/yaml/) - This will help you understand YAML.
2. [YAML Online checker](http://www.yamllint.com/) - Use this to check all your YAML files before submitting.