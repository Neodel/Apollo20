#include "Controleur.h"


Controleur::Controleur():
    _codeur1 ("/sys/devices/platform/ocp/48304000.epwmss/48304180.eqep/"),
    _codeur2 ("/sys/devices/platform/ocp/48300000.epwmss/48300180.eqep/"),
    
    _driver1("/sys/class/pwm/pwmchip3/pwm1/","/sys/class/gpio/gpio48/"),
    _driver2("/sys/class/pwm/pwmchip3/pwm0/","/sys/class/gpio/gpio31/"),
    
    _pid1(1,0,0),
    _pid2(1,0,0),
    
    _ratio( 2 * PI / (TIC_CODEUR * REDUCTION))
{
    this->_target1 = this->_getPos1();
    this->_target2 = this->_getPos2();
}

inline float Controleur::_getPos1(){
    return this->_codeur1.read() * this->_ratio;
}

inline float Controleur::_getPos2(){
    return this->_codeur2.read() * this->_ratio;
}

void Controleur::write(float m1, float m2){
    this->_target1 = m1;
    this->_target2 = m2;
}

void Controleur::loop(){
    
    this->_order1 = this->_pid1.correction(this->_target1 - this->_getPos1());
    this->_order2 = this->_pid2.correction(this->_target2 - this->_getPos2());
    
    this->_driver1.write(this->_order1);
    this->_driver2.write(this->_order2);
    
    #ifdef DEBUG_CONTROLEUR
        std::cout << "loop 1 , pos: " << this->_getPos1() << " target: " ;
        std::cout << this->_target1 << " order: " << this->_order1 ;
        std::cout << " achieved: " << this->achieved() ;
        
        std::cout << "    loop 2 , pos: " << this->_getPos2() << " target: " ;
        std::cout << this->_target2 << " order: " << this->_order2 ;
        std::cout << " achieved: " << this->achieved() << std::endl;
    #endif
}

bool Controleur::achieved(){
    return  (this->_order1 < SEUIL) && (this->_order2 < SEUIL) &&  
            (this->_order1 > -SEUIL) && (this->_order2 > -SEUIL);
}


#ifdef DEBUG_CONTROLEUR

    int main(void){
        Controleur controleur;
        
        int tempo = 100000;
        int iter = 10;
        
        for(int i=0; i<iter ; i++){
            controleur.loop();
            usleep(tempo);
        }
        
        controleur.write(100,100);
        
        for(int i=0; i<iter ; i++){
            controleur.loop();
            usleep(tempo);
        }
        
        controleur.write(-100,-100);
        
        for(int i=0; i<iter ; i++){
            controleur.loop();
            usleep(tempo);
        }
        
    }

#endif