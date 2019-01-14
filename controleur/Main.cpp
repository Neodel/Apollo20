#include "Controleur.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "sigint_catcher.h"

#include "Point.h"
#include "geom_inv.h"

#include <cmath>

using namespace std;



std::vector<Point*> readFile(const char * nameFile);

#if (! defined(DEBUG_CONTROLEUR)) && (! defined(DEBUG_CODEUR))

	int main(void){
		
		SigIntCatcher sigIntCatcher;
	   
		std::vector<Point*> points = readFile("data.txt");

		Point org;
		org.x = 0.012;
		org.y = 0.082;
		
		Cmd cmd;
		// note use model infv of (12,82) (mm)
		cmd.q1 = 2.66917;
		cmd.q5 = 0.478780;
	    
	    
	    // modele inverse points -> points
	    
	    Controleur controleur;
	    
	    //controleur.set(geomInv(org));
	    controleur.set(cmd);
	    
	    std::cout << "init : " << controleur.getPos1() << " "<< controleur.getPos2() << std::endl;
	    
	    
	    //controleur.write(points);


	    for (auto p : points) { // segfault at the end ...
	    
		   cmd = geomInv(*p);
		   controleur.write(cmd);
		   bool ok;
		   std::cout<< cmd.q1 << " | " << cmd.q5 <<std::endl;
		   do{
		   		controleur.loop();
		   		usleep(100000);
		   		ok = controleur.achieved();
		   		std::cout<< cmd.q1 << " | " << cmd.q5;
		   		std::cout << " achieved: " << ok << std::endl;
		   }while(!ok);
		        
		}
		
		
		/*
		for (auto p : points) { // segfault at the end ...
		   controleur.write(p->x, p->y);
		   std::cout<< p->x << " | " << p->y <<std::endl;
		   do{
		   		controleur.loop();
		   		usleep(100000);
		   }while(!controleur.achieved());
		        
		}
		*/
		
		
	
	    
	    
	}
	
#endif


std::vector<Point*> readFile(const char * nameFile){
    
    std::ifstream input_file;
     
    input_file.open(nameFile);
    
    if (! input_file) 
        std::cout<<"fail to open file"<<std::endl;
        
    std::vector<Point*> points;
    
    std::string buffer ;
    
    std::string bufferX ;
    std::string bufferY ;
    int x = 0;
  
    while(!input_file.eof()){
		getline(input_file,buffer,'\n');
		
		x=0;
		bufferX = "";
		bufferY = "";
		for (auto c : buffer) {
		    if(c == ','){
		        x=1;
		    }
		    else if( x == 0){
		        bufferX += c;
		    }
		    else if( x == 1){
		        bufferY += c;
		    }
		}
		
		points.push_back(new Point);
		points.back()->x = stof(bufferX); // revesed (12_01_19)
		points.back()->y = stof(bufferY);

	}
	
	input_file.close();
	
	return points;
    
}