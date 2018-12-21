#include "Point.h"
#include <cmath>
#include <iostream>

#define L 0.02
#define L1 0.065
#define L2 0.08
#define DECALAGE 0.01
#define PI 3.14159265

using namespace std; 

Point modelDirect(float q1, float q2);

int main(int argv, char* argc[]) {
	float q1 = 5*PI/6;
	float q2 = PI/4;
	
	Point test;
	test = modelDirect(q1,q2);
	
	cout<<test.x<<" "<<test.y<<"\n";
}

Point modelDirect(float q1, float q2) {
	Point xTerm;
	xTerm.x = L1*cos(q1) + (L2)* cos(q1-q2);
	xTerm.y = L1*sin(q1) + (L2)* sin(q1-q2);
	
	xTerm.x = xTerm.x + DECALAGE*cos(PI/4);
	xTerm.y = xTerm.y + DECALAGE*sin(PI/4);
	
	return xTerm;

}
