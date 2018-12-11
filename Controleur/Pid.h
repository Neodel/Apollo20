#ifndef PID_H
#define PID_H

class Pid {
    
    private:
        int _kp;
        int _kd;
        int _ki;
        int _error;
        int _previous_error;
        int _sum_error;
        
        int _correction;
    
    public:
        Pid(int kp, int kd, int ki);
        int correction(int error);
        
    
};




#endif