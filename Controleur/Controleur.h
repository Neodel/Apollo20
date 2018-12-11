#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "Driver.h"
#include "Pid.h"
#include "Codeur.h"

#define DEBUG_CONTROLEUR

class Controleur {
    
    public:
        Controleur();
        
        void write(float m1, float m2);
        
        void loop();
    
    private:
    
        float _target1, _target2;
        
        Pid    _pid1   , _pid2;
        Codeur _codeur1, _codeur2;
        Driver _driver1, _driver2;
        
    
};




#endif