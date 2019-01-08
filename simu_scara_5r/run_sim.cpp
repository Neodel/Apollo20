#include "geom_inv.hpp"
#include "geom_direct.hpp"
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define PI 3.14159265

int main()
{
	int i;
	float q1,q5;
	float error[50];
	Point S;
	srand(time(NULL));
	Cmd cmd;
	/*
	for(i = 0;i<50;i++)
	{	
		q1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3.14));
		q5 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/3.14));
		S = modelDirect(q1,q5);
		cmd = geomInv(S);
		std::cout << "q : " << q1 << "+ " << q5 << "       cmd :" << cmd.q1<< "+" << cmd.q5 ; 
		error[i] = (q1-cmd.q1)*(q1-cmd.q1) + (q5-cmd.q5)*(q5-cmd.q5);
		std::cout << "      error " << i<< "= " << error[i] << "\n";
	}
	*/
	q1 = PI/3;
	q5 = 0;
	S = modelDirect(q1,q5);
	std::cout << "x:" << S.x << "  y:" << S.y << "\n";
	return 1;
}