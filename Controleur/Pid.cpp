#include "Pid.h"


Pid::Pid(float kp, float kd, float ki) {
     /* To do : regler a la main */
    _kp = kp;
    _kd = kd;
    _ki = ki;
    _error = 0.0;
    _previous_error = 0.0;
    _sum_error = 0.0;
 }

int Pid::correction(int error){ 
    
    this->_previous_error = _error;
    this->_error = error;
    this->_sum_error += error;
        
    this->_correction = this->_kp*error+ this->_kd*(error-this->_previous_error) + this->_ki*(this->_sum_error);
    
    if (_correction < -100){
        _correction = -100;
    }
    else if (_correction > 100){
         _correction = 100;
    }
        
    return _correction;
}