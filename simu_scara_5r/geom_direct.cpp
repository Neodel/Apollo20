#include "Point.h"
#include <cmath>
#include <iostream>

#define L 0.02
#define L1 0.065
#define L2 0.08
#define DECALAGE 0.01
#define PI 3.14159265

using namespace std; 

Point modelDirect(float q1, float q5);

/*int main(int argv, char* argc[]) {
	float q1 = 5*PI/6;
	float q2 = PI/4;
	
	Point test;
	test = modelDirect(q1,q2);
	
	cout<<test.x<<" "<<test.y<<"\n";
}*/

float norm(Point X)
{
	return sqrt(X.x*X.x + X.y*X.y);
}
Point modelDirect(float q1, float q5) {
	Point xTerm,x2,x4,o2o4,o2oI,x3;
	x2.x = L1*cos(q1);
	x2.y = L1*sin(q1);
	x4.x = L + L1*cos(q5);
	x4.y = L1*sin(q5);

	o2o4.x = x4.x - x2.x;
	o2o4.y = x4.y - x2.y;
	o2oI.x = o2o4.x/2;
	o2oI.y = o2o4.y/2;

	float scalar = o2oI.x*(-x2.x) + o2oI.y*(-x2.y); 	

	float q2 = PI - acos(norm(o2oI)/L2) - acos( scalar/( norm(x2)*norm(o2oI) ) );

	x3.x = L1*cos(q1) + (L2)* cos(q1-q2);
	x3.y = L1*sin(q1) + (L2)* sin(q1-q2);
	
	xTerm.x = x3.x + DECALAGE*cos(PI/4);
	xTerm.y = x3.y + DECALAGE*sin(PI/4);
	return xTerm;

}
