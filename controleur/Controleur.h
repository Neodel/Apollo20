#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <unistd.h>
#include <vector>

#include "Driver.h"
#include "Pid.h"
#include "Codeur.h"
#include "Point.h"

//#define DEBUG_CONTROLEUR

#define TIC_CODEUR 360
#define REDUCTION 1.9

#define PI 3.14159265


#define SEUIL 0.05

#define TEMPO 100000

class Controleur {
    
    public:
        Controleur();
        
        void write(float m1, float m2);
        
        void write(Cmd cmd);
        
        void write(std::vector<Point*>);
        
        void set(Cmd cmd);
        
        void loop();
        
        bool achieved();
        
        float getPos1();
        float getPos2();

    private:
    
        double  _target1, _target2;
        
        float  _ratio;
        
        int    _order1 , _order2;
        
        Pid    _pid1   , _pid2;
        Codeur _codeur1, _codeur2;
        Driver _driver1, _driver2;
        
    
};




#endif