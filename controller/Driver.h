#include <iostream>
#include <fstream>
#include <unistd.h>

//motor 1 pwm chip3:0 p9_14 gpio_31 p9_13 
//motor 2 pwm chip3:1 p9_16 gpio_48 p9_15

//exemples: 
// Driver driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/");
// Driver driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/");
// driver1.write(-50);

//#define DEBUG_DRIVER

#ifndef DRIVER_H
#define DRIVER_H
/**
 * @brief      Class for driver.
 */
class Driver{

public:
    /**
     * @brief      Constructor of the driver
     *
     * @param[in]  pwmPath   The pwm path needed
     * @param[in]  gpioPath  The gpio path needed
     */
    Driver(std::string pwmPath, std::string gpioPath);
    /**
     * @brief      Write into the port
     *
     * @param[in]  value  The value
     */
    void write(int value);
    /**
     * @brief      Destructor of the class
     */
    ~Driver();
    
    // TODO destructeur
    
private:
	/**
	 * @brief The defined pwm path
	 */
    std::string _pwmPath;
	/**
	 * @brief The defined gpio path
	 */
    std::string _gpioPath;
	/**
	 * @brief File containing the active time of the pwm
	 */
    std::ofstream _dutyCycle;
	/**
	 * @brief File setting the activation of the GPIO
	 */
    std::ofstream _gpio;
	/**
	 * @brief Period setting
	 */
    int _period;
    /**
     * @brief Buffer value
     */
    int _value;
};

#endif
