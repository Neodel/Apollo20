#ifndef POINT_H
#define POINT_H

/*!
 * \file Point.h
 * \brief Definition of two classes usefull for geometric models
 * \version 1
 */

#include <cmath>


/*!
 * \class Point [<Point.h>]
 * \brief Definition of a 2D point
 * \version 1
 */
struct Point{
	float x;
	float y;
	
	Point(float X, float Y) : x(X), y(Y)
	{}
	
	Point() : x(-1), y(-1)
	{}
	
	float norm()
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}
	
	static float dot(Point x1, Point x2)
	{
		return (x1.x*x2.x + x1.y*x2.y);
	}	
	
};

/*!
 * \class Cmd [<Point.h>]
 * \brief Definition of an angular command for the system
 * \version 1
 */
struct Cmd{
	float q1;
	float q5;
	
	Cmd(float Q1, float Q5) : q1(Q1), q5(Q5)
	{}
	
	Cmd() : q1(-1), q5(-1)
	{}
};

/*! Solution side */
enum SolSide {
	RIGHT_SOL, /*!< This is Right solution */
	LEFT_SOL   /*!< This is Left solution */
};


#endif
