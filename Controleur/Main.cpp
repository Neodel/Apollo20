#include "Controleur.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Point.h"

std::vector<Point*> readFile(const char * nameFile);

#if (! defined(DEBUG_CONTROLEUR)) && (! defined(DEBUG_CODEUR))

	int main(void){
	    
	   
		std::vector<Point*> points = readFile("data.txt");
	    
	    
	    // modele inverse points -> points
	    
	    Controleur controleur;
	    
	    //controleur.write(points);


	    for (auto p : points) {
		   controleur.write(p->x, p->y);
		   std::cout<< p->x << " | " << p->y <<std::endl;
		   do{
		   		controleur.loop();
		   		usleep(100000);
		   }while(!controleur.achieved());
		         
		}
		
	
	    
	    
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
		points.back()->x = stof(bufferX);
		points.back()->y = stof(bufferY);

	}
	
	input_file.close();
	
	return points;
    
}