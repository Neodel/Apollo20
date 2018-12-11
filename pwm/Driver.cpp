#include "Driver.h"
#include <iostream>
#include <fstream>
#include <unistd.h>


Driver::Driver(std::string pwmPath, std::string gpioPath){
    // TODO check files
    
    this->_pwmPath = pwmPath;
    this->_gpioPath = gpioPath;
    
    // open pwm file
    std::string duty = this->_pwmPath+"duty_cycle";
    this->_dutyCycle.open(duty.c_str());
    
    // set period
    this->_period = 500000;
    std::string period = this->_pwmPath+"period";
    std::ofstream period_file;
    period_file.open(duty.c_str());
    period_file <<  this->_period << std::endl;
    period_file.close();
    
    // enable pwm
    std::string enable = this->_pwmPath+"enable";
    std::ofstream enable_file;
    enable_file.open(enable.c_str());
    enable_file <<  1 << std::endl;
    enable_file.close();
    
    // open gpio file
    std::string value = this->_gpioPath+"value";
    this->_gpio.open(value.c_str());
    
    // set gpio as output
    std::string direction = this->_pwmPath+"direction";
    std::ofstream direction_file;
    direction_file.open(direction.c_str());
    direction_file <<  "out" << std::endl;
    direction_file.close();
    
    // set speed to 0
    this->write(0);
    
    // set gpio to 0
    
    #ifdef DEBUG_DRIVER
        std::cout<< "Driver ctr:  pwm: " << this->_pwmPath << " gpio: " << this->_gpioPath << std::endl;
    #endif
}

Driver::~Driver(){
    this->_gpio.close();
    this->_dutyCycle.close();
}

void Driver::write(int value){
    if (value < 0){
        // gpio to 1 
        this->_gpio << 1 << std::endl;
        value = this->_period*(1-value)/100;
    }
    else{
        // gpio to 0
        this->_gpio << 0 << std::endl;
        value = this->_period*value/100;
    }
    this->_value = value;
    
    this->_dutyCycle << value << std::endl;
    
    #ifdef DEBUG_DRIVER
        std::cout<< "value " << value << std::endl;
    #endif
}


#ifdef DEBUG_DRIVER

    int main(void){
        Driver driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/");
        Driver driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/");
        driver1.write(-50);
    }
    
#endif