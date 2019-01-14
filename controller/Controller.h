#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <vector>

#include "Driver.h"
#include "Pid.h"
#include "Codeur.h"
#include "Point.h"
//Should be rename controler
//#define DEBUG_CONTROLEUR

#define TIC_ENCODER 360
#define REDUCTION 1.9

#define PI 3.14159265


#define THRESHOLD 0.5

#define TEMPO 100000
/**
 * @brief      class for the controler
 */
class Controller {
    
    public:
        /**
         * @brief      constructor of the controler
         */
        Controller();
        /**
         * @brief      function 
         *
         * @param[in]  m1    The m 1
         * @param[in]  m2    The m 2
         */
        void write(float m1, float m2);
        /**
         * @brief      { function_description }
         *
         * @param[in]  <unnamed>  { parameter_description }
         */
        void write(std::vector<Point*>);
        /**
         * @brief      { function_description }
         */
        void loop();
        /**
         * @brief      { function_description }
         *
         * @return     { description_of_the_return_value }
         */
        bool achieved();
        /**
         * @brief      Gets the position 1.
         *
         * @return     The position 1.
         */
        float getPos1();
        float getPos2();

    private:
    
        float  _target1, _target2;
        
        float  _ratio;
        
        int    _order1 , _order2;
        
        Pid    _pid1   , _pid2;
        Codeur _codeur1, _codeur2;
        Driver _driver1, _driver2;
        
    
};




#endif