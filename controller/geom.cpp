#include "geom.h"

Point interCerle(Point const& p1, float const& r1, Point const& p2, float const& r2, SolSide const& side)
{
	float distPts = sqrt( (p1.x -p2.x)*(p1.x -p2.x) + (p1.y - p2.y)*(p1.y -p2.y) );
	
	Point u1( (p2.x-p1.x)/distPts , (p2.y-p1.y)/distPts); // vecteur unitaire p1p2
	Point v1( u1.y, -u1.x); // vecteur unitaire orthogonal à u1
	
	Point c( (p1.x+p2.x)/2 , (p1.y+p2.y)/2 ); // centre de p1p2
	
	if( distPts > r1+r2)
	{
    std::cout <<"Pas possible O2 \n";
    return Point(-1,-1);
	}
	else
	{
		float a = (r1*r1 - r2*r2)/(2*distPts);
		float b = sqrt( (r1*r1 + r2*r2)/2 - (r1*r1-r2*r2)*(r1*r1-r2*r2)/(4*distPts*distPts) - distPts*distPts/4);
		
		// Solutions
		Point s1 ( c.x + a*u1.x + b*v1.x, c.y + a*u1.y + b*v1.y);
		Point s2 ( c.x + a*u1.x - b*v1.x, c.y + a*u1.y - b*v1.y);
		
		if(side == LEFT_SOL)
		{
			if(s1.x < s2.x) //solution à gauche
				return s1;
			else return s2;
		}
		else // cas : RIGHT_SOL
		{
			if(s1.x > s2.x) //solution à droite
				return s1;
			else return s2;
		}
	}
} 

Cmd geomInv(Point const& X)
{
	Point O1(0,0);
	Point O5(D,0);

	Point O2 = interCerle(O1, L1, X, R_OT_O2, LEFT_SOL);
	Point O3 = interCerle(O2, L2, X, LT, RIGHT_SOL); // solution de droite !!!
	Point O4 = interCerle(O5, L1, O3, L2, RIGHT_SOL); // idem
	
	float q1 = acos((O2.x-O1.x)/L1);
	float q5 = acos((O4.x-O5.x)/L1);
	
	return Cmd(q1,q5); 
}

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

	Point Xterm(X3.x + LT*std::cos(q2-qterm), X3.y + LT*std::sin(q2-qterm));

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

#ifdef DEBUG_GEOM_INV
int main()
{
	Cmd cmd = geomInv(Point(0.1,0.1));
    std::cout << "q1 = " << cmd.q1 << ",q2 = " << cmd.q5 << '\n';
    return 1;
}
#endif
