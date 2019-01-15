#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <unistd.h>
#include <vector>

#include "Driver.h"
#include "Pid.h"
#include "Encoder.h"
#include "Point.h"
//Should be rename controler
//#define DEBUG_CONTROLEUR

#define TIC_ENCODER 360
#define REDUCTION 1.9

#define PI 3.14159265


#define THRESHOLD_C 0.5

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
         * @brief      Destroys the object.
         */
        ~Controller();
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
         *
         * @param      cmd   The command
         */
        void write(Cmd const& cmd);
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
         * @brief      { function_description }
         *
         * @param      cmd   The command
         */
        void set(Cmd const& cmd);
        /**
         * @brief      Gets the position 1.
         *
         * @return     The position 1.
         */
        float getPos1();

        float getPos2();

    private:
        /**
         * { item_description }
         */
        float  _target1, _target2;
        /**
         * { item_description }
         */
        float  _ratio;
        /**
         * { item_description }
         */
        int    _order1 , _order2;
        /**
         * { item_description }
         */
        Pid    _pid1   , _pid2;
        /**
         * { item_description }
         */
        Encoder _encoder1, _encoder2;
        /**
         * { item_description }
         */
        Driver _driver1, _driver2;
        
    
};




#endif