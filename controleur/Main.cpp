#include "Controleur.h"
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
#include "geom_inv.h"
#include "geom_direct.h"

#define THRESHOLD  0.001


#include <cmath>

using namespace std;


bool achieved(Point p, float q1, float q5);
std::vector<Point> readPathFile(const char * nameFile);
std::vector<Point> interpolationTrajectory(std::vector<Point> vPoints);


#if (! defined(DEBUG_CONTROLEUR)) && (! defined(DEBUG_CODEUR))

	int main(void){
	   
		std::vector<Point> points = readPathFile("data.txt");
		
		points = interpolationTrajectory(points);
		//for (auto p : interpolPoints)
			//std::cout << p.x << "," << p.y << std::endl;
		

		Point org(0.012,0.082);
		Point p_target, p_actu;
		
		Cmd cmd, actu;
		
		// note use model infv of (12,82) (mm)
		// cmd.q1 = 2.66917;
		// cmd.q5 = 0.478780;
	    
	    
	    //modele inverse points -> points
	    
	    Controleur controleur;
	    
	    controleur.set(geomInv(org));
	    //controleur.set(cmd);
	    
	    std::cout << "Init : " << controleur.getPos1() << " "<< controleur.getPos2() << std::endl;
	    
	    //controleur.write(points);
	    for (auto p : points) 
			std::cout<<p.x<<" "<<p.y<<std::endl;

	    for (auto p : points) { 
		   cmd = geomInv(p);
		   
		   p_target = geomDirect(cmd);
		   controleur.write(cmd);
		   p_target = geomDirect(cmd);
		   
		   std::cout<< p.x <<" "<<p.y<<std::endl;
		   bool ok;
		   std::cout<<"cmd: " << cmd.q1 << " | " << cmd.q5 <<std::endl;
		   do{
		   		actu.q1 = controleur.getPos1();
		   		actu.q5 = controleur.getPos2();
		   		p_actu = geomDirect(actu);
		   		controleur.loop();
		   		usleep(10000);
		   		// ok = controleur.achieved(); // depreciated
		   		ok = achieved(p,controleur.getPos1(),controleur.getPos2());
		   		//std::cout<< cmd.q1 << " | " << cmd.q5 << " | "<< p_target.x <<" "<< p_target.y << " | "<< p_actu.x <<" "<< p_actu.y;
		   		//std::cout << " | achieved: " << ok << std::endl;
		   		//std::cout<< p_target.x *1000<<" "<< p_target.y*1000 << " | "<< p_actu.x *1000<<" "<< p_actu.y*1000 <<" er = "<<(p_target.x-p_actu.x)*1000 << " "<< (p_target.y-p_actu.y)*1000 << std::endl;
		   		//std::cout<<"actu: q1: "<< actu.q1 << " q5: " <<  actu.q5 << std::endl;
		   }while(!ok);      
		}	    
	}
	
#endif

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
	

		int nb_point = int(sqrt( (xcurr-xlast)*(xcurr-xlast) +  (ycurr-ylast)*(ycurr-ylast) ) * 1000); 
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
