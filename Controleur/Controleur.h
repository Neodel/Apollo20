#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <unistd.h>

#include "Driver.h"
#include "Pid.h"
#include "Codeur.h"

#define DEBUG_CONTROLEUR

#define TIC_CODEUR 400
#define REDUCTION 2

#define PI 3.14159265

#define RATIO 

#define SEUIL 5

class Controleur {
    
    public:
        Controleur();
        
        void write(float m1, float m2);
        
        void loop();
        
        bool achieved();

    private:
    
        inline float _getPos1();
        inline float _getPos2();
    
        float  _target1, _target2;
        
        float  _ratio;
        
        int    _order1 , _order2;
        
        Pid    _pid1   , _pid2;
        Codeur _codeur1, _codeur2;
        Driver _driver1, _driver2;
        
    
};




#endif