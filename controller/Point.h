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
	/**
	 * (float) x coordinate of the point
	 */
	float x;

	/**
	 * (float) y coordinate of the point
	 */
	float y;

	/**
	 * @brief      Setter of the point structure.
	 *
	 * @param      X     Coordinate of the point.
	 * @param      Y     Coordinate of the point.
	 */
	Point(float const& X, float const& Y) : x(X), y(Y)
	{}

	/**
	 * Default setter of the point structure.
	 */
	Point() : x(-1), y(-1)
	{}

	/**
	 * @brief      This function calculates the distance between the point and the origin frame.
	 *
	 * @return     (Float) The euclidian distance between the point and the origin frame.
	 */
	float norm()
	{
		return sqrt(this->x*this->x + this->y*this->y);
	}

	/**
	 * @brief      This function calculates the distance between p1 and p2.
	 *
	 * @param      p1    The point p1
	 * @param      p2    The point p2
	 *
	 * @return     (Float) the euclidian distance between p1 and p2.
	 */
	static float norm(Point const& p1, Point const& p2)
	{
		return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
	}

	/**
	 * @brief      Calculate the dot product between p1 and p2.
	 *
	 * @param      x1    The  point x1
	 * @param      x2    The  point x2
	 *
	 * @return     (Float) the  value of the dot product.
	 */
	static float dot(Point const& x1, Point const& x2)
	{
		return (x1.x*x2.x + x1.y*x2.y);
	}

	/**
	 * @brief      This function displays the coordinates of the point. 
	 */
	void disp()
	{
		std::cout << "Point : x=" << this->x << " y=" << this->y << std::endl;
	}
	
};




/*!
 * \class Cmd [<Point.h>]
 * \brief Definition of an joint command for the system
 * \version 1
 */
struct Cmd{
	/**
	 * The joint command for the motor1.
	 */
	float q1;

	/**
	 * The joint command for the motor2.
	 */
	float q5;
	
	/**
	 * @brief     Constructor of the cmd structure.
	 *
	 * @param      Q1    The quarter 1
	 * @param      Q5    The quarter 5
	 */
	Cmd(float const& Q1, float const& Q5) : q1(Q1), q5(Q5)
	{}
	
	/**
	 * Default setter of the cmd structure.
	 */
	Cmd() : q1(-1), q5(-1)
	{}
};

/**
 * Choose for the side solution found using geom_inv.
 */
enum SolSide {RIGHT_SOL, LEFT_SOL};


#endif
