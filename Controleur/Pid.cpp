#include "Pid.h"


Pid::Pid(int kp, int kd, int ki) {
     /* To do : regler a la main */
    _kp = kp;
    _kd = kd;
    _ki = ki;
    _error = 0;
    _previous_error = 0;
    _sum_error = 0;
 }
    
int Pid::correction(int error){ 
    
    this->_previous_error = _error;
    this->_error = error;
    this->_sum_error += error;
        
    this->_correction = this->_kp*error+ this->_kd*(error-this->_previous_error) + this->_ki*(this->_sum_error);
        
    return _correction;
}