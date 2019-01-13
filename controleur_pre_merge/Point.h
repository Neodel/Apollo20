#ifndef POINT_H
#define POINT_H


#include <cmath>

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


struct Cmd{
	float q1;
	float q5;
	
	Cmd(float Q1, float Q5) : q1(Q1), q5(Q5)
	{}
	
	Cmd() : q1(-1), q5(-1)
	{}
};

// Solution side
enum SolSide {RIGHT_SOL, LEFT_SOL};


#endif