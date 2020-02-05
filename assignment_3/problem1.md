# Problem 1

## Problem statement
Study all the interfaces of a board and write them down in a yaml file.

### Steps 
1. Pick 3 unique boards from the [board list](https://docs.google.com/spreadsheets/d/1in0_qqWc5r-ngrlRduTemxfzUY_cOrZYDOE2uZ5Woqc/edit?usp=sharing) 
2. Study their all their interfaces and pinouts.
3. Write down all the details of the interfaces in the problem1.yaml
4. Once done submit by pushing the branch with your full_name.

### YAML file 
1. YAML file should contain all the pins on the board with UART, SPI, I2C or PWM interfaces
2. For every pin the YAML file should contain the entry simillar to this.
```yaml
pin 3: 
  i2c-details: 1
  spi-details: null
  uart-details: null
  pwm-details: null
```
Where the number `1` in front of the `i2c-details` key says that this pin 
corresponds to `/dev/i2c-1` device node in linux.

## Reference Links 
1. [YAML Syntax](https://learnxinyminutes.com/docs/yaml/)
2. [YAML Online checker](http://www.yamllint.com/) - Use this to check all your YAML files before submitting.