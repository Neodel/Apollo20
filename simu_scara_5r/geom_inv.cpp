#include <iostream>
#include <cmath>

using namespace std;
#define COSPI_4 sqrt(2)/2

void geom_inv(float* X,float l1,float l2,float d,float& q1,float&q2)
{
	// declarations des deux points de controle moteur
	float _O1[2];
	_O1[0] = 0;
	_O1[1] = 0;

	float _O5[2];
	_O5[0] = d;
	_O5[1] = 0;

	float O2[2];
	float O3[2];

	float lt = 0.01;
	float rayon1 = sqrt( pow(l2 + lt*COSPI_4,2) + pow(lt*COSPI_4,2) );
	//Initialisation variables calcul 02
	float _R1 = sqrt( pow((X[0]-_O1[0]),2) + pow((X[1]-_O1[1]),2) ); // Distance 01-X
	// Vecteur colinéaire a R1
	float _ua1[2]; 
	_ua1[0] = (X[0]-_O1[0])/_R1;
	_ua1[1]= (X[1]-_O1[1])/_R1;
	// Vecteur orthogonal a ua1
	float _ub1[2];
	_ub1[0] =  _ua1[1];
	_ub1[1] = -_ua1[0];
	//Point milieu de R1
	float _c1[2];
	_c1[0]= (X[0]+_O1[0])/2;
	_c1[1]= (X[1]+_O1[1])/2;
	//Variable intermédiraires
	float _a1,_b11,_b12;
	float _OG1[2],_OG2[2],_O2[2],_O12[2];

	// Initialisation variable calcul O4
	float _R5 = sqrt( pow((X[0]-_O5[0]),2) + pow((X[1]-_O5[1]),2) ); // Distance O5-X
	//Vecteur collinéaire R5
	float _ua5[2];
	_ua5[0] = (X[0]-_O5[0])/_R5;
	_ua5[1]= (X[1]-_O5[1])/_R5;
	//Vecteur orthogonal
	float _ub5[2];
	_ub5[0] =  _ua5[1];
	_ub5[1] = -_ua5[0];
	//Point milieu 
	float _c5[2];
	_c5[0] = (X[0]+_O5[0])/2;
	_c5[1] = (X[1]+_O5[1])/2;
	//Variables intermédiraires
	float _a5,_b51,_b52;
	float _OD1[2],_OD2[2],_OD[2],_O5D[2];

	//Calcul 02
	if(_R1 > l1+rayon1)
	{
    cout <<"Pas possible O2 \n";
    return;
	}
	else
	{
		_a1 = (l1*l1 - l2*l2)/(2*_R1);
		_b11 = sqrt( (l1*l1 + rayon1*rayon1)/2 -(l1*l1-rayon1*rayon1)*(l1*l1-rayon1*rayon1)/(4*_R1*_R1) -_R1*_R1/4);
		_b12 = -sqrt((l1*l1+rayon1*rayon1)/2 -(l1*l1-rayon1*rayon1)*(l1*l1-rayon1*rayon1)/(4*_R1*_R1) -_R1*_R1/4);
		_OG1[0] = _c1[0] + _a1*_ua1[0] + _b11*_ub1[0]; // premiere solution
		_OG1[1] = _c1[1] + _a1*_ua1[1] + _b11*_ub1[1];
		_OG2[0] = _c1[0] + _a1*_ua1[0] + _b12*_ub1[0]; // deuxieme solution
		_OG2[1] = _c1[1] + _a1*_ua1[1] + _b12*_ub1[1];
		if(_OG1[0] < _OG2[0])
		{ // prendre solution la plus a gauche
    		_O2[0] = _OG1[0];
    		_O2[1] = _OG1[1];
    	}
		else
		{
    		_O2[0] = _OG2[0];
    		_O2[1] = _OG2[1];
    	}
	}
	O12[0] = _O2[0]-O1[0];
	O12[1] = _O2[1]-O1[1];
	q1 = acos(_O12[0]/l1);

	//Initialisation O3
	float _R2 = sqrt( pow((X[0]-_O2[0]),2) + pow((X[1]-_O2[1]),2) ); // Distance 02-X
	// Vecteur colinéaire a R1
	float _ua2[2]; 
	_ua2[0] = (X[0]-_O1[0])/_R3;
	_ua2[1]= (X[1]-_O1[1])/_R3;
	// Vecteur orthogonal a ua1
	float _ub2[2];
	_ub2[0] =  _ua2[1];
	_ub2[1] = -_ua2[0];
	//Point milieu de R1
	float _c2[2];
	_c2[0]= (X[0]+_O2[0])/2;
	_c2[1]= (X[1]+_O2[1])/2;
	//Variable intermédiraires
	float _a2,_b21,_b22;
	float _OG3[2],_OG4[2],_O3[2];


	//Calcul O3
	if(_R2 > l2+lt)
	{
    cout <<"Pas possible O3 \n";
    return;
	}
	else
	{
		_a2 = (l2*l2 - lt*lt)/(2*_R2);
		_b11 = sqrt( (l1*l1 + rayon1*rayon1)/2 -(l1*l1-rayon1*rayon1)*(l1*l1-rayon1*rayon1)/(4*_R1*_R1) -_R1*_R1/4);
		_b12 = -sqrt((l1*l1+rayon1*rayon1)/2 -(l1*l1-rayon1*rayon1)*(l1*l1-rayon1*rayon1)/(4*_R1*_R1) -_R1*_R1/4);
		_OG1[0] = _c1[0] + _a1*_ua1[0] + _b11*_ub1[0]; // premiere solution
		_OG1[1] = _c1[1] + _a1*_ua1[1] + _b11*_ub1[1];
		_OG2[0] = _c1[0] + _a1*_ua1[0] + _b12*_ub1[0]; // deuxieme solution
		_OG2[1] = _c1[1] + _a1*_ua1[1] + _b12*_ub1[1];
		if(_OG1[0] < _OG2[0])
		{ // prendre solution la plus a gauche
    		_O2[0] = _OG1[0];
    		_O2[1] = _OG1[1];
    	}
		else
		{
    		_O2[0] = _OG2[0];
    		_O2[1] = _OG2[1];
    	}
	}
	O12[0] = _O2[0]-O1[0];
	O12[1] = _O2[1]-O1[1];
	q1 = acos(_O12[0]/l1);

	//Initialisation O3
	float _R3 = sqrt( pow((X[0]-_O2[0]),2) + pow((X[1]-_O2[1]),2) ); // Distance 01-X
	// Vecteur colinéaire a R1
	float _ua2[2]; 
	_ua2[0] = (X[0]-_O1[0])/_R3;
	_ua2[1]= (X[1]-_O1[1])/_R3;
	// Vecteur orthogonal a ua1
	float _ub2[2];
	_ub2[0] =  _ua2[1];
	_ub2[1] = -_ua2[0];
	//Point milieu de R1
	float _c2[2];
	_c2[0]= (X[0]+_O2[0])/2;
	_c2[1]= (X[1]+_O2[1])/2;
	//Variable intermédiraires
	float _a2,_b21,_b22;
	float _OG3[2],_OG4[2],_O3[2];




	//Calcul 04
	if(_R5 > l1+l2)
	{
    cout <<"Pas possible O5 \n";
    return;
	}
	else
	{
		_a5 = (l1*l1 - l2*l2)/(2*_R5);
		_b51 = sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R5*_R5) -_R5*_R5/4);
		_b52 = -sqrt((l1*l1+l2*l2)/2 -(l1*l1-l2*l2)*(l1*l1-l2*l2)/(4*_R5*_R5) -_R5*_R5/4);
		_OD1[0] = _c5[0] + _a5*_ua5[0] + _b51*_ub5[0]; // premiere solution
		_OD1[1] = _c5[1] + _a5*_ua5[1] + _b51*_ub5[1];
		_OD2[0] = _c5[0] + _a5*_ua5[0] + _b52*_ub5[0]; // deuxieme solution
		_OD2[1] = _c5[1] + _a5*_ua5[1] + _b12*_ub1[1];
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
	
	_O5D[0] = _OD[0]-_O5[0];
	_O5D[1] = _OD[1]-_O5[1];
	q1 = acos(_O1G[0]/_norm1);
	q2 = acos(_O5D[0]/_norm2);

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