#include "ServerGUI.h"
#include "Point.h"
#include "Controller.h"
#include "geom_inv.h"


ServerGUI::ServerGUI(Controller * controller)
{
	_opt = 1;
	_addrlen = sizeof(_address);
	_controller  = controller;
}



// initialize the Server. return false if it failed, true otherwise.
bool ServerGUI::init()
{
	// Creating socket file descriptor 
	if ((_serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
	{
		perror("socket failed"); 
		return false; 
	} 
	
	// Forcefully attaching socket to the port 
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, 
												&_opt, sizeof(_opt))) 
	{
		perror("setsockopt"); 
		exit(EXIT_FAILURE);
	}
	_address.sin_family = AF_INET; 
	_address.sin_addr.s_addr = INADDR_ANY; 
	_address.sin_port = htons( PORT ); 
	
	// Forcefully attaching socket to the port 
	if (bind(_serverFd, (struct sockaddr *)&_address, 
								sizeof(_address))<0) 
	{ 
		perror("bind failed"); 
		return false; 
	} 
	
	
	// Wait for connection from the client (pc with GUI)
	if (listen(_serverFd, 3) < 0) 
	{ 
		perror("listen"); 
		return false;
	} 
	if ((_newSocket = accept(_serverFd, (struct sockaddr *)&_address, 
					(socklen_t*)&_addrlen))<0) 
	{ 
		perror("accept"); 
		return false;
	}
	
	// Connection ok : server and client are now connected  
	
	return true;
}

bool ServerGUI::sendPos(Point p){
	_msg = "p:";
	_msg += std::to_string(p.x );
	_msg +="," ;
	_msg += std::to_string(p.y);
	return this->writeMsg(_msg.c_str());
}


bool ServerGUI::sendArti(){
	_msg = "a:";
	_msg += std::to_string(_controller->getPos1() );
	_msg +="," ;
	_msg += std::to_string(_controller->getPos2());
	return this->writeMsg(_msg.c_str());
}

//
bool ServerGUI::readMsg()
{
	char buffer[1024] = {0};
	
	read( _newSocket , buffer, 1024); // get the message in buffer
	printf("%s\n",buffer ); // print result 
	switch(buffer[0]){
		case 'i' : 
			std::cout<<"init"<<std::endl;
			// TODO init
			this->readMsg();
			break;
		case 's' :
			std::cout<<"send : "<<buffer<<std::endl;
			// TODO send
			this->readMsg();
			break;
		case 'r' :
			std::cout<<"run"<<std::endl;
			break;
		default:
			std::cout<< "not readable : " << buffer << std::endl;
		
	}
	
	return true;
}

//
bool ServerGUI::writeMsg( const char* msg )
{
	send(_newSocket , msg , strlen(msg) , 0 ); // send msg
	return true;
}


#ifdef DEBUG_SERVERGUI
int main(int argc, char const *argv[]) 
{ 
	ServerGUI srvGUI;
	
	srvGUI.init();


	srvGUI.readMsg();
	
	char *hello = "Hello from server";
	srvGUI.writeMsg( hello );
	
	
	return 0;
		
}
#endif



