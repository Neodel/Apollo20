#include <iostream>
#include <cmath>

using namespace std;

void geom_inv(float* X,float l1,float l2,float d,float& q1,float&q2)
{
	// declarations des deux points de controle moteur
	float _O1[2];
	_O1[0] = 0;
	_O1[1] = 0;

	float _O2[2];
	_O2[0] = d;
	_O2[1] = 0;

	//
	float _R1 = sqrt( pow((X[0]-_O1[0]),2) + pow((X[1]-_O1[1]),2) );
	float _ua1[2];
	_ua1[0] = (X[0]-_O1[0])/_R1;
	_ua1[1]= (X[1]-_O1[1])/_R1;
	float _ub1[2];
	_ub1[0] =  _ua1[1];
	_ub1[1] = -_ua1[0];
	float _c1[2];
	_c1[0]= (X[0]+_O1[0])/2;
	_c1[1]= (X[1]+_O1[1])/2;
	float _a1,_b11,_b12;
	float _OG1[2],_OG2[2],_OG[2],_O1G[2];


	float _R2 = sqrt( pow((X[0]-_O2[0]),2) + pow((X[1]-_O2[1]),2) );
	float _ua2[2];
	_ua2[0] = (X[0]-_O2[0])/_R2;
	_ua2[1]= (X[1]-_O2[1])/_R2;
	float _ub2[2];
	_ub2[0] =  _ua2[1];
	_ub2[1] = -_ua2[0];
	float _c2[2];
	_c2[0] = (X[0]+_O2[0])/2;
	_c2[1] = (X[1]+_O2[1])/2;
	float _a2,_b21,_b22;
	float _OD1[2],_OD2[2],_OD[2],_O2D[2];

	//Test gauche
	if(_R1 > l1+l2)
	{
    cout <<"Pas possible O1 \n";
    return;
	}
	else
	{
		_a1 = (l1*l1 - l2*l2)/(2*_R1);
		_b11 = sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R1*_R1) -_R1*_R1/4);
		_b12 = -sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R1*_R1) -_R1*_R1/4);
		_OG1[0] = _c1[0] + _a1*_ua1[0] + _b11*_ub1[0]; // premiere solution
		_OG1[1] = _c1[1] + _a1*_ua1[1] + _b11*_ub1[1];
		_OG2[0] = _c1[0] + _a1*_ua1[0] + _b12*_ub1[0]; // deuxieme solution
		_OG2[1] = _c1[1] + _a1*_ua1[1] + _b12*_ub1[1];
		if(_OG1[0] < _OG2[0])
		{ // prendre solution la plus a gauche
    		_OG[0] = _OG1[0];
    		_OG[1] = _OG1[1];
    	}
		else
		{
    		_OG[0] = _OG2[0];
    		_OG[1] = _OG2[1];
    	}
	}
	//Test droit
	if(_R2 > l1+l2)
	{
    cout <<"Pas possible O2 \n";
    return;
	}
	else
	{
		_a2 = (l1*l1 - l2*l2)/(2*_R2);
		_b21 = sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R2*_R2) -_R2*_R2/4);
		_b22 = -sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R2*_R2) -_R2*_R2/4);
		_OD1[0] = _c2[0] + _a2*_ua2[0] + _b21*_ub2[0]; // premiere solution
		_OD1[1] = _c2[1] + _a2*_ua2[1] + _b21*_ub2[1];
		_OD2[0] = _c2[0] + _a2*_ua2[0] + _b22*_ub2[0]; // deuxieme solution
		_OD2[1] = _c2[1] + _a2*_ua2[1] + _b12*_ub1[1];
		if(_OD1[0] > _OD2[0])
		{ // prendre solution la plus a droite
    		_OD[0] = _OD1[0];
    		_OD[1] = _OD1[1];
    	}
		else
		{
    		_OD[0] = _OD2[0];
    		_OD[1] = _OD2[1];
    	}
	}
	_O1G[0] = _OG[0]-_O1[0];
	_O1G[1] = _OG[1]-_O1[1];
	_O2D[0] = _OD[0]-_O2[0];
	_O2D[1] = _OD[1]-_O2[1];
	float _norm1 = sqrt(_O1G[0]*_O1G[0] + _O1G[1]*_O1G[1]);
	float _norm2 = sqrt(_O2D[0]*_O2D[0] + _O2D[1]*_O2D[1]);
	q1 = acos(_O1G[0]/_norm1);
	q2 = acos(_O2D[0]/_norm2);

}

int main()
{
	float q1 = 0,q2 = 0;
	float X[2];
	X[0] =0.01;
	X[1] =0.1;
	geom_inv(X,0.065,0.080,0.02,q1,q2);
    std::cout << "q1 = " << q1 << ",q2 = " << q2 << '\n';
    return 1;
}