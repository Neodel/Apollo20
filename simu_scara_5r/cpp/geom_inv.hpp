#ifndef GEOM_INVERSE_HPP
#define GEOM_INVERSE_HPP


#include <iostream>
#include <cmath>
#include "Point.h"


#define COSPI_4 sqrt(2)/2
#define L1 0.065
#define L2 0.08
#define D 0.02
#define LT 0.01

#define R_OT_O2 sqrt( (L2 + LT*sqrt(2)/2)*(L2 + LT*sqrt(2)/2) +  (LT*sqrt(2)/2)*(LT*sqrt(2)/2) ) // = rayon1



Point interCerle(Point p1, float r1, Point p2, float r2, SolSide side);
Cmd geomInv(Point X);



#endif
