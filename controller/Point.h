#ifndef POINT_H
#define POINT_H

/*!
 * \file Point.h
 * \brief Definition of two classes usefull for geometric models
 * \version 1
 */

#include <cmath>

#ifndef PI
#define PI 3.141597
#endif

/*!
 * \class Point [<Point.h>]
 * \brief Definition of a 2D point
 * \version 1
 */
struct Point{
	float x;
	float y;
	
	Point(float const& X, float const& Y) : x(X), y(Y)
	{}
	
	Point() : x(-1), y(-1)
	{}
	
	float norm()
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}
	
	static float norm(Point const& p1, Point const& p2)
	{
		return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	}
	
	static float dot(Point const& x1, Point const& x2)
	{
		return (x1.x*x2.x + x1.y*x2.y);
	}
	
	void disp()
	{
		std::cout << "Point : x=" << this->x << " y=" << this->y << std::endl;
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
	
	Cmd(float const& Q1, float const& Q5) : q1(Q1), q5(Q5)
	{}
	
	Cmd() : q1(-1), q5(-1)
	{}
};

// Solution side
enum SolSide {RIGHT_SOL, LEFT_SOL};


#endif
