#include <iostream>
#include <fstream>
#include <unistd.h>

//moteur 1 pwm chip3:0 p9_14 gpio_31 p9_13 
//moteur 2 pwm chip3:1 p9_16 gpio_48 p9_15

//exemples: 
// Driver driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/");
// Driver driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/");
// driver1.write(-50);

//#define DEBUG_DRIVER

#ifndef DRIVER_H
#define DRIVER_H

class Driver{

public:
    Driver(std::string pwmPath, std::string gpioPath);
    
    void write(int value);
    
    ~Driver();
    
    // TODO destructeur
    
private:
    std::string _pwmPath;
    std::string _gpioPath;
    
    std::ofstream _dutyCycle;
    std::ofstream _gpio;
    
    int _period;
    int _value;
    