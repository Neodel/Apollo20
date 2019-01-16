#include "ServerGUI.h"
#include "Point.h"
#include "Controller.h"
#include "geom.h"

std::vector<Point> interpolationTrajectory(std::vector<Point> vPoints);
void follow(Controller * controller,ServerGUI * serverGUI, std::vector<Point> points);
std::vector<Point> readPathFile(const char * nameFile);

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
	char buffer[100] = {0};
	
	read( _newSocket , buffer, 1024); // get the message in buffer
	printf("%s\n",buffer ); // print result 
	
	Cmd cmd;
	std::vector<Point> pts;
	Point p,p1;
	int xFlag;
	std::string bufferX ;
    std::string bufferY ;
	
	switch(buffer[0]){
		case 'i' : 
			std::cout<<"init"<<std::endl;
		    p.x = ORG_X;
		    p.y = ORG_Y;
			_controller->set(geomInv(p));
			
			this->readMsg();
			
			break;
			
		case 's' :

			pts.clear();
			cmd.q1 = _controller->getPos1();
			cmd.q5 = _controller->getPos2();
			p1 = geomDirect(cmd);
			pts.push_back(p1);
			
			for(int i = 2;i<100;i++) buffer[i-2] = buffer[i];
			
			xFlag=0;
			bufferX = "";
			bufferY = "";
			for (auto c : buffer) {
			    if(c == ','){
			        xFlag=1;
			    }
			    else if( xFlag == 0){
			        bufferX += c;
			    }
			    else if( xFlag == 1){
			        bufferY += c;
			    }
			}
			
			p.x = stof(bufferX); // revesed (12_01_19)
			p.y = stof(bufferY);
			
			std::cout<<"send "<<p.x<<" "<<p.y<<std::endl;
		
			pts.push_back(p);	
			
			//pts= interpolationTrajectory(pts);
			
			follow(_controller,this,pts);


			this->readMsg();
			break;
		case 'r' :
			pts.clear();
			pts = readPathFile("data.txt");
			std::cout<<"run"<<std::endl;
			
			pts = interpolationTrajectory(pts);
			
			follow(_controller,this,pts);
			
			this->readMsg();
			break;
		case 'e':
			break;
		default:
			std::cout<< "not readable : " << buffer << std::endl;
			this->readMsg();
		
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



