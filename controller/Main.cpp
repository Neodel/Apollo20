#include "Controller.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Point.h"
#include "geom.h"
#include "ServerGUI.h"

#define THRESHOLD  0.005


#include <cmath>

using namespace std;

#define SAMPLING_RATIO 1000

bool achieved(Point p, float q1, float q5);
std::vector<Point> readPathFile(const char * nameFile);
std::vector<Point> interpolationTrajectory(std::vector<Point> vPoints);
void follow(Controller * controleur,ServerGUI * serverGUI ,std::vector<Point> points);


#if (! defined(DEBUG_CONTROLEUR)) && (! defined(DEBUG_CODEUR))

	int main(void){

	    Controller controller;
	   
	    
	    ServerGUI serverGUI(&controller);
	    serverGUI.init();
	    serverGUI.readMsg();
	   
			

	}
	
#endif

void follow(Controller * controller,ServerGUI * serverGUI, std::vector<Point> points){
	Cmd cmd, actu;
	Point p_target, p_actu;
	
	int iter = 0 ;
	float error = 0;
		
	
    for (auto p : points) { 
	   cmd = geomInv(p);
	   
	   p_target = geomDirect(cmd);
	   controller->write(cmd);
	   p_target = geomDirect(cmd);
	   
	   std::cout<< p.x <<" "<<p.y<<std::endl;
	   bool ok;
	   std::cout<<"cmd: " << cmd.q1 << " | " << cmd.q5 <<std::endl;
	   do{
	 		actu.q1 = controller->getPos1();
	   		actu.q5 = controller->getPos2();
	   		p_actu = geomDirect(actu);
	   		
	   		controller->loop();
	   		usleep(10000);
	   	    serverGUI->sendArti();
	   	    serverGUI->sendPos(p_actu);
	   	    
	   		// ok = controleur.achieved(); // depreciated
	   		ok = achieved(p,controller->getPos1(),controller->getPos2());
	   		
	   		iter ++;
	   		error += Point::norm(p_target,p_actu);
	   }while(!ok);  
	   
	}
	controller->endTravel();
	std::cout<< "final mean error --- " << error/iter<< std::endl;
}

bool achieved(Point p, float q1, float q5){
	Cmd cmd;
	cmd.q1 = q1;
	cmd.q5 = q5;
	
	Point p_actu = geomDirect(cmd);
	
	//std::cout<< p.x << " " << p.y << " | "<< p_actu.x <<" "<< p_actu.y<<std::endl;
	
	return (Point::norm(p,p_actu)<THRESHOLD);
	
}


std::vector<Point> readPathFile(const char * nameFile)
{
	std::vector<Point> vpOutput;

	std::ifstream f(nameFile, std::ifstream::in);

	if(f)
	{
		std::string sBuffer;

		while(f >> sBuffer){
			std::stringstream iss(sBuffer);

			Point p;
			iss >> p.x;
			iss.ignore(1,'\n');
			iss >> p.y;
			vpOutput.push_back(p);	
		}

	}
	else
		std::cout << "Error : unable to open " << nameFile << std::endl;

	/* for debugging if necessary :
	std::cout << "size="<<vpOutput.size()<<std::endl;
	for (auto&& p: vpOutput)
		std::cout << "x="<<p.x<<" y="<<p.y<<std::endl;
	*/
	return vpOutput;

}



std::vector<Point> interpolationTrajectory(std::vector<Point> vPoints)
{
	

	std::vector<Point> vPointsInterpol;
	
	// ajout du premier point
	if (vPoints.size() > 0)
			vPointsInterpol.push_back(vPoints[0]);
	else 
	{
		std::cout << "(WARNING) Empty list of points" << std::endl;
		return vPointsInterpol;
	}
	
	// pour chaque point de la carte
	for(size_t iPt(1) ; iPt < vPoints.size() ; ++iPt) // entre n et n-1 : début = 1
	{
		double xlast = vPoints[iPt-1].x;
		double ylast = vPoints[iPt-1].y;
		double xcurr = vPoints[iPt].x;
		double ycurr = vPoints[iPt].y;
	
		int nb_point = int(sqrt( (xcurr-xlast)*(xcurr-xlast) +  (ycurr-ylast)*(ycurr-ylast) ) * 500); 

		double increment_x = (xcurr-xlast)/nb_point;
		double increment_y = (ycurr-ylast)/nb_point;

		for(int i=0; i< nb_point; i++) 
		{
			Point add;
			add.x = vPointsInterpol.back().x + increment_x;
			add.y = vPointsInterpol.back().y + increment_y;
			vPointsInterpol.push_back(add);
		}
	
		vPointsInterpol.push_back(vPoints[iPt]);
	}
	
	
	return vPointsInterpol;
}
