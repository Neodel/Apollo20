#ifndef PID_H
#define PID_H

class Pid {
    
    private:
        float _kp;
        float _kd;
        float _ki;
        float _error;
        float _previous_error;
        float _sum_error;
        
        int _correction;
    
    public:
        Pid(float kp, float kd, float ki);
        int correction(int error);
        
    
};




#endif