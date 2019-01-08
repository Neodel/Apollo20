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
        Pid();
        int correction(int error);
        
    
};

Pid::Pid() {

    /* To do : regler a la main */
    _kp = 1;
    _kd = 1;
    _ki = 1;
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
    
