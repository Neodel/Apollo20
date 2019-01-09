#include "Pid.h"



Pid::Pid(float kp, float ki, float kd) {
     /* To do : regler a la main */
    _kp = kp;
    _kd = kd;
    _ki = ki;
    _previous_error = 0.0;
    _sum_error=0.0;
    _prev_time = clock();
 }

int Pid::correction(int error){ 
    
    
    this->_sum_error += error;
    if (this->_sum_error >100)
        this->_sum_error = 100;
        
    if (this->_sum_error <-100)
        this->_sum_error = -100;
    
    
    this->_correction = this->_kp*error;
    this->_correction += this->_ki*(this->_sum_error) ;
    this->_correction += this->_kd*(error-this->_previous_error)/(clock()-_prev_time) * CLOCKS_PER_SEC;
    
    #if true
        std::cout<< " p " << this->_kp*error;
        std::cout<< " i " << this->_ki*(this->_sum_error);
        std::cout<< " d " << this->_kd*(error-this->_previous_error)/(clock()-_prev_time) * CLOCKS_PER_SEC;
        std::cout<< " correction "<< this->_correction<< std::endl;
        
        
    #endif
    
    
    if (_correction < -100){
        _correction = -100;
    }
    else if (_correction > 100){
         _correction = 100;
    }
    this->_prev_time = clock();
    this->_previous_error = error;
    
    return _correction;
}