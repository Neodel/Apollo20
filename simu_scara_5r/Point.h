#ifndef POINT_H
#define POINT_H


struct Point{
	float x;
	float y;
	
	Point(float X, float Y) : x(X), y(Y)
	{}
	
	Point() : x(-1), y(-1)
	{}
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
