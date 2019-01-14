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


#include <cmath>

using namespace std;



std::vector<Point> readPathFile(const char * nameFile);

#if (! defined(DEBUG_CONTROLEUR)) && (! defined(DEBUG_CODEUR))

	int main(void){
	   
		std::vector<Point> points = readPathFile("data.txt");

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
		   bool ok;
		   std::cout<<"cmd: " << cmd.q1 << " | " << cmd.q5 <<std::endl;
		   do{
		   		actu.q1 = controleur.getPos1();
		   		actu.q5 = controleur.getPos2();
		   		p_actu = geomDirect(actu);
		   		controleur.loop();
		   		usleep(100000);
		   		ok = controleur.achieved();
		   		//std::cout<< cmd.q1 << " | " << cmd.q5 << " | "<< p_target.x <<" "<< p_target.y << " | "<< p_actu.x <<" "<< p_actu.y;
		   		//std::cout << " | achieved: " << ok << std::endl;
		   		//std::cout<< p_target.x *1000<<" "<< p_target.y*1000 << " | "<< p_actu.x *1000<<" "<< p_actu.y*1000 <<" er = "<<(p_target.x-p_actu.x)*1000 << " "<< (p_target.y-p_actu.y)*1000 << std::endl;
		   		std::cout<<"actu: q1: "<< actu.q1 << " q5: " <<  actu.q5 << std::endl;
		   }while(!ok);      
		}	    
	}
	
#endif


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
