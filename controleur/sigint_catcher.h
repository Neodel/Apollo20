#ifndef SIGINT_CATCHER_HPP
#define SIGINT_CATCHER_HPP


#include <iostream>
#include <signal.h>
#include <cstdlib>
#include <stdio.h>
#include "Controleur.h"


//#define DEBUG_SIGINTCATCHER

//struct sigaction sigIntHandler;



/********************************************** 
 * How to use it : just declare a SigIntCatcher object, and implement the callBackInterrupt() function
 * to handle ctrl+c as desired.
 **********************************************
 */



class SigIntCatcher
{
	private:
		struct sigaction _handler;
	
	
	public:
		SigIntCatcher();
		
		static void callBackInterrupt(int s);

};



#endif
