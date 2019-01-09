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
 *  \param q1 : Angular parameter of the first angle (left motor)
 *  \param q5 : Angular parameter of the last angle (right motor)
 *  \return Le point atteint par les valeurs articulaire mises en paramètre
 */

Point modelDirect(float q1, float q5);



#endif
