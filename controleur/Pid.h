#ifndef PID_H
#define PID_H

#include <ctime>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>


#define N_ERROR 5

class Pid {
    
    private:
        float _kp;
        float _kd;
        float _ki;
        float _previous_error;
        float _sum_error;
        
        clock_t _prev_time;
    
        
        int _correction;
    
    public:
        Pid(float kp, float kd, float ki);
        int correction(int error);
        
    
};




#endif