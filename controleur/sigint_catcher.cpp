#include "sigint_catcher.hpp"


SigIntCatcher::SigIntCatcher()
{
	_handler.sa_handler = callBackInterrupt;
	sigemptyset(&_handler.sa_mask);
	_handler.sa_flags = 0;
	
	sigaction(SIGINT, &_handler, NULL);
	
}

void SigIntCatcher::callBackInterrupt(int s)
{
	printf("Caught signal %d\n",s);
	
	/* PROGRAMMER LE HANDLER DU CTRL+C ICI */
	
	exit(1); 
}

// Main to test
#ifdef DEBUG_SIGINTCATCHER

int main(int argc,char** argv)
{
	SigIntCatcher sigIntCatcher;
	
	while(1);

	return 0;    
}

#endif