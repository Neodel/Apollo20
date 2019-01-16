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



/**
 * @brief      Class for the Graphical User Interface Server.
 */
class ServerGUI
{

public:

	/**
   * @brief      Constructs the server object.
   *
   * @param[in]  controller    Controller adress
   */	
	ServerGUI(Controller * controller);
	
	/**
   * @brief      Send joints position to the Gui client
   *
   * @return     True if the message has been successfully sent, false otherwise.
   */
	bool sendArti();
	
	/**
   * @brief      Send cartesian position to the Gui client
	*
   * @return     True if the message has been successfully sent, false otherwise.
   */
	bool sendPos(Point p);

	/**
   * @brief      Initialize the connection between the Server (bbb) and the Client (pc).
   *
   * @return     True if the connection has been successfully done, false otherwise.
   */
	bool init();
	
	/**
   * @brief      Get the next trame from the client, and sent the corresponing order to the controller.
   *
   * @return     True if the trame has been successfully read, false otherwise (note : TODO).
   */
	bool readMsg();
	
	/**
   * @brief      Send a trame to the client.
   *
   * @param[in]  msg  The message to send.
   *
   * @return     True if the message has been successfully send, false otherwise.
   */
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
