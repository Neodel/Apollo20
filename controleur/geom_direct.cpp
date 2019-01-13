#include "geom_direct.hpp"



Point geomDirect(Cmd const& cmd)
{
	float q1(cmd.q1), q5(cmd.q5);
	
	// Configurations Operationnal space
	Point X1(0,0);
	Point X2(L1*std::cos(q1), L1*std::sin(q1));
	Point X4(D+L1*std::cos(q5), L1*std::sin(q5));
	Point X5(D,0);	

	// X3 computation
	Point O2O4(X4.x-X2.x,X4.y-X2.y); // vect from O2 to O4
	Point O2OI(0.5*O2O4.x,0.5*O2O4.y); // vect from O2 to OI : middle of O2O4

	Point minusX2(-X2.x, -X2.y);
	float q2 = PI - std::acos(O2OI.norm()/L2) - std::acos( Point::dot(minusX2,O2OI)/(minusX2.norm()*O2OI.norm()) );
	
	Point X3(L1*std::cos(q1) + L2* std::cos(q1-q2), L1*std::sin(q1) + L2* std::sin(q1-q2));

	// Xterm computation
	float qterm = PI/4;

	Point Xterm(X3.x + LT*std::cos(qterm), X3.y + LT*std::sin(qterm));

	return Xterm; 
}


// Main to test
#ifdef DEBUG_GEOM_DIR

int main(int argc,char** argv)
{
	Cmd cmd(PI/3,PI/2);
	
	Point p = geomDirect(cmd);
	p.disp();
	

	return 0;    
}

#endif
