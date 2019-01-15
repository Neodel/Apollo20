#ifndef SERVER_GUI
#define SERVER_GUI

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#include "Controller.h"
#include "Point.h"

#define PORT 15555 

//#define DEBUG_SERVERGUI

class ServerGUI
{

public:
	ServerGUI(Controller * controller);
	
	bool sendArti();
	
	bool sendPos(Point p);

	bool init();
	
	bool readMsg();
	
	bool writeMsg( const char* msg );

private:
	int _serverFd;
	struct sockaddr_in _address;
	int _opt;
	int _addrlen;
	int _newSocket;
	std::string _msg;
	
	Controller * _controller;
	
	
};



#endif
