#include "Controleur.h"


Controleur::Controleur():
    _codeur1 ("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/"),
    _codeur2 ("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/"),
    
    _driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/"),
    _driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/"),
    
    _pid1(1,0,0),
    _pid2(1,0,0)
{
    this->_target1 = this->_codeur1.read();
    this->_target2 = this->_codeur2.read();
}


void Controleur::write(float m1, float m2){
    this->_target1 = m1;
    this->_target2 = m2;
}

void Controleur::loop(){
    
}


#ifdef DEBUG_CONTROLEUR

int main(void){
    Controleur controleur();
    
}

#endif