#ifndef GEOM_INVERSE_HPP
#define GEOM_INVERSE_HPP

/*!
 * \file geom_inv.hpp
 * \brief Inverse geometric model's resolution
 * \version 1
 */

#include <iostream>
#include <cmath>
#include "Point.h"


#define COSPI_4 sqrt(2)/2
#define L1 0.065
#define L2 0.08
#define D 0.02
#define LT 0.01

#define R_OT_O2 sqrt( (L2 + LT*sqrt(2)/2)*(L2 + LT*sqrt(2)/2) +  (LT*sqrt(2)/2)*(LT*sqrt(2)/2) ) // = rayon1


/*!
 *  \brief Circles intersection finding
 *
 *  Method that permits to find the intersection of two circles, and choose one of it if solutions exist
 *
 *  \param p1 : center of the first circle
 *  \param r1 : radius of the first circle
 *	\param p2 : center of the second circle
 *  \param r2 : radius of the second circle
 *  \param side : choose one of the solution
 *  \return Needed intersection point
 */

Point interCerle(Point p1, float r1, Point p2, float r2, SolSide side);

/*!
 *  \brief Inverse geometric model
 *
 *  Method that permits the calculation of inverse geometric model
 *
 *  \param Reached point by articular parameters
 *  \return Joint parameters of the system
 */

Cmd geomInv(Point X);



#endif
