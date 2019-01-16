#include "Controller.h"

Controller::Controller():
    _encoder1 ("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/"),
    _encoder2 ("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/"),
    
    _driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/"),
    _driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/"),
    
    _pid1(800,20,0.01), // 6 0.2 0.0001 // 50 0 0.1
    _pid2(800,20,0.01),
    
    _ratio( 2.0 * PI / (TIC_ENCODER * 4 * REDUCTION)) // 4 for quadrature
{
    
    std::cout << " ctr controller " << _ratio<< std::endl;
    this->_target1 = this->getPos1();
    this->_target2 = this->getPos2();
}

Controller::~Controller(){
    _driver1.~Driver();
    _driver2.~Driver();
}

void Controller::endTravel(){
    _driver1.write(0);
    _driver2.write(0);
}

void Controller::write(std::vector<Point*> points ){//Depreciated
    for (auto p : points) {
       this->write(p->x, p->y);
       while(! this->achieved())
            this->loop();
    }
}


float Controller::getPos1(){
    return this->_encoder1.read() * this->_ratio;
}

float Controller::getPos2(){
    return this->_encoder2.read() * this->_ratio;
}

void Controller::write(float m1, float m2){ //depreciated
    this->_target1 = m1;
    this->_target2 = m2;
}
void Controller::write(Cmd const& cmd){
    this->_target1 = cmd.q1;
    this->_target2 = cmd.q5;
}

void Controller::loop(){
    
    
    this->_order1 = this->_pid1.correction(this->_target1 - this->getPos1());
    this->_order2 = this->_pid2.correction(this->_target2 - this->getPos2());
    
    this->_driver1.write(this->_order1);
    this->_driver2.write(this->_order2);
    
    #if false
        std::cout << "loop 1 , pos: " << this->getPos1() << " target: " ;
        std::cout << this->_target1 << " order: " << this->_order1 ;
        
        std::cout << "    loop 2 , pos: " << this->getPos2() << " target: " ;
        std::cout << this->_target2 << " order: " << this->_order2 ;
        std::cout << " achieved: " << this->achieved() << std::endl;
    #endif
}

bool Controller::achieved(){
    return  ( (std::abs(this->getPos1()-this->_target1)  < THRESHOLD_C) && ( std::abs(this->getPos2()-this->_target2) < THRESHOLD_C) );
}
void Controller::set(Cmd const& cmd){
    this->_encoder1.set(cmd.q1/this->_ratio);
    this->_encoder2.set(cmd.q5/this->_ratio);
}

#ifdef DEBUG_CONTROLLER

    int main(void){
        Controller controller;
        
        std::cout<< "pos 1 "<< controller.getPos1()  << " pos 2 " << controller.getPos2() << std::endl;
        
        int tempo = 100000;
        int iter = 100;

        
        controller.write(100,100);
        
        for(int i=0; i<iter ; i++){
            controller.loop();
            usleep(tempo);
        }
        
        
    }

#endif