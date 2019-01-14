#ifndef GEOM_DIRECT_HPP
#define GEOM_DIRECT_HPP

/*!
 * \file geom_direct.h
 * \brief Direct geometric model's resolution
 * \version 1
 */

#include "Point.h"
#include <cmath>
#include <iostream>


#define D 0.02
#define L1 0.065
#define L2 0.08
#define LT 0.01
#define PI 3.14159265


/*!
 *  \brief Direct geometric model
 *
 *  Methode that permit the calculation of direct geometric model
 *
 *  \param (float) q1 : Joint parameter of the first angle (left motor)
 *  \param (float) q5 : Joint parameter of the last angle (right motor)
 *  \return (Point) Reached point by articular parameters
 */

Point modelDirect(float q1, float q5);



#endif
