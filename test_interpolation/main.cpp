#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Point.h"
#include <cmath>

std::vector<Point> interpolation(Point un, Point deux) {
	// On veut interpoler de nouveux points environ tous les centimètres
	// On calcule donc en centimètre la distance entre deux points à laquelle on ajoute 1, on devra donc trouver "dist(cm)+1" points donc des points distants d'un peu moins 1cm
	int nb_point = int(sqrt( (deux.x-un.x)*(deux.x-un.x) + (deux.y-un.y)*(deux.y-un.y) ) * 100) + 1; 
	float increment_x = (deux.x-un.x)/nb_point;
	float increment_y = (deux.y-un.y)/nb_point;
	
	std::vector<Point> points;
	points.push_back(un);
	
	for(int i=0; i< nb_point; i++) {
		Point ajout;
		ajout.x = points.back().x + increment_x;
		ajout.y = points.back().y + increment_y;
		points.push_back(ajout);
	}
	
	return points;
}

int main(int argc, char* argv[]) {

	// test de l'interpolation
	un.x = 0.1;
	un.y = 0;

	Point deux;
	deux.x = 0;
	deux.y = 0.1;

	std::vector<Point> liste;
	liste = interpolation(un, deux); 
	
	for(int i = 0; i<liste.size(); i++) {
    	std::cout<<"Point numero : "<<i<<" x ="<<liste[i].x*100 <<" y ="<<liste[i].y*100<<"\n";
	}
   
}
