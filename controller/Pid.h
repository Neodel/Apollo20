#ifndef PID_H
#define PID_H

#include <ctime>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>


#define N_ERROR 5
/**
 * @brief      Class for pid.
 */
class Pid {
    public:
        /**
         * @brief      Constructs the object pid.
         *
         * @param[in]  kp    Proportional gain
         * @param[in]  kd    derived gain
         * @param[in]  ki    integrator gain
         */
        Pid(float kp, float kd, float ki);
        /**
         * @brief      { function_description }
         *
         * @param[in]  error  The error
         *
         * @return     { description_of_the_return_value }
         */
        int correction(float error);
    
    private:
        /**
         * { item_description }
         */
        float _kp;
        /**
         * { item_description }
         */
        float _kd;
        /**
         * { item_description }
         */
        float _ki;
        /**
         * { item_description }
         */
        float _previous_error;
        /**
         * { item_description }
         */
        float _sum_error;
        /**
         * { item_description }
         */
        clock_t _prev_time;
        /**
         * { item_description }
         */
        int _correction;
};




#endif