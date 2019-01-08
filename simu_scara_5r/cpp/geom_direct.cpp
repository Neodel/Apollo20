#include "geom_direct.hpp"


int main(int argv, char* argc[]) {
	float q1 = 1.23048;
	float q2 = 0.181599;
	
	Point test;
	test = modelDirect(q1,q2);
	
	std::cout<< "X=" << test.x << ", Y=" << test.y << std::endl;
}


Point modelDirect(float q1, float q5) {
	
	Point x2(L1*cos(q1), L1*sin(q1));
	Point x4(D + L1*cos(q5), L1*sin(q5));

	Point o2o4(x4.x - x2.x, x4.y - x2.y);
	Point o2oI(o2o4.x/2, o2o4.y/2);

	float scalar = Point::dot(o2oI, Point(-x2.x,-x2.y));
	float q2 = PI - acos(o2oI.norm()/L2) - acos( scalar/( x2.norm()*o2oI.norm() ) );

	Point x3( L1*cos(q1) + (L2)* cos(q1-q2), L1*sin(q1) + (L2)* sin(q1-q2));
	
	Point xTerm( x3.x + LT*cos(PI/4), x3.y + LT*sin(PI/4));

	return xTerm;
}
