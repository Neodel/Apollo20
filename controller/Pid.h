#ifndef PID_H
#define PID_H

#include <ctime>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>


#define N_ERROR 5
/**
 * @brief      Class that implements a proportionnal intefrated and derived controller.
 */
class Pid {
    public:
        /**
         * @brief      Constructs the object pid.
         *
         * @param[in]  kp    Proportional gain
         * @param[in]  kd    derivative gain
         * @param[in]  ki    integral gain
         */
        Pid(float kp, float kd, float ki);

        /**
         * @brief      { function_description }
         *
         * @param[in]  error  The error between the current value and the value targetted.
         *
         * @return     the command that will be sent to the pwm port of the motor. It is an int value because it is the type asked by the pwm port.
         */
        int correction(float error);
    
    private:
        /**
         * Proportionnal gain of the pid.
         */
        float _kp;

        /**
         * Derivative gain of the pid.
         */
        float _kd;

        /**
         * Integral gain of the pid.
         */
        float _ki;

        /**
         * Error at last execution of the loop. It is used to calculate the derivative part of the controller.
         */
        float _previous_error;

        /**
         * Sum of all previous errors.
         */
        float _sum_error;

        /**
         * Time at the end of the last execution. It is needed to calculate the time difference between the two executions. Used for the derivative part of the controller.
         */
        clock_t _prev_time;

        /**
         * Int value sent to the motors through the pwm ports.
         */
        int _correction;
};




#endif