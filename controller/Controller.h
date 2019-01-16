#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <vector>

#include "Driver.h"
#include "Pid.h"
#include "Encoder.h"
#include "Point.h"
//Should be rename controler
//#define DEBUG_CONTROLEUR

#define TIC_ENCODER 360
#define REDUCTION 1.9


#define THRESHOLD_C 0.5

#define TEMPO 100000
/**
 * @brief      class for the controler. This is the main object of the project. It is composed of drivers, encoders and pid objects.
 * During the execution of the project, the encoders will be read, these values will be changed through the pid and send to the motors.
 * 
 */
class Controller {
    
    public:
        /**
         * @brief      constructor of the controler
         */
        Controller();

        /**
         * @brief      Destroys the object.
         */
        ~Controller();

        /**
         * @brief      function that change the target value for motors. Depreciated method.
         *
         * @param[in]  m1    The  command for motor1
         * @param[in]  m2    The command for motor2
         */
        void write(float m1, float m2);

        /**
         * @brief      Function that move the motors to reach a list of points. Depreciated method.
         *
         * @param[in]  points  list of articular positions. points[i].x is the value for motor1, points[i].y for motor2.
         */
        void write(std::vector<Point*> points);

        /**
         * @brief      Function that change the target value for the motors.
         *
         * @param      cmd   The command for the motors. cmd.q1 is for motor1 and cmd.q5 for motor2.
         */
        void write(Cmd const& cmd);

        /**
         * @brief      Function that listens to the encoders, uses the pid to find the command to send and sends it.
         */
        void loop();

        /**
         * @brief      Function that checks if the joint position asked is reached. This position is reached if the difference is under a epsilon.
         * This epsilon is a constant value and must be greater than the encoder tic. 
         *
         * @return     True if the position is reached, False otherwise.
         */
        bool achieved();

        /**
         * @brief      This function sets the value of the encoder. It is used for the initialisation of the starting point.
         *
         * @param      cmd   The command. cmd.q1 is the value set to the encoder1, cmd.q5 is set to the encoder2.
         */
        void set(Cmd const& cmd);

        /**
         * @brief      Gets the position of the motor1 using its encoder.
         *
         * @return     The value of the encoder1 in radian.
         */
        float getPos1();

        /**
         * @brief      Gets the position of the motor2 using its encoder.
         *
         * @return     The value of the encoder2 in radian.
         */
        float getPos2();
        
        /**
         * @brief      stop the motrs
         * 
         */
         void endTravel();

    private:
        /**
         * the targetted joint position of the motor1 in radians. 
         */
        float  _target1;

        /**
         * the targetted joint position of the motor2 in radians.
         */
        float _target2;

        /**
         * This variable is the ratio of radians per encoder tics. It permits to transform the encoder tic value into radians.
         */
        float  _ratio;

        /**
         * 		Value sent to the pwm port for motor1. It is an int because PWM accepts int values between 0 to 100 ( the pourcentage of the pwm).
         */
        int    _order1 ;

        /**
         * Value sent to the pwm port for motor2. It is an int because PWM accepts int values between 0 to 100 ( the pourcentage of the pwm).
         */
        int    _order2;

        /**
         * The pid controller for motor1.
         */
        Pid    _pid1;

        /**
         * The pid controller for motor2.
         */
        Pid    _pid2;

        /**
         * The encoder for motor1.
         */
        Encoder _encoder1;

        /**
         * The encoder for motor2.
         */
        Encoder _encoder2;

        /**
         * The driver for motor1.
         */
        Driver _driver1;

        /**
         * The driver for motor2.
         */
        Driver _driver2;
        
    
};




#endif