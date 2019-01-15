#ifndef SERVER_GUI
#define SERVER_GUI

#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define PORT 15555 

#define DEBUG_SERVERGUI

class ServerGUI
{

public:
	ServerGUI();

	bool init();
	
	bool readMsg();
	
	bool writeMsg( char* msg );

private:
	int _serverFd;
	struct sockaddr_in _address;
	int _opt;
	int _addrlen;
	int _newSocket;
	
	
};



#endif
