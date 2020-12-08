#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

//Server class
class Server{
    public:
        Server(void* data);
        Server(void* data, int port);
        Server(const Server& orig);
        virtual ~Server();
        
        void shutdown();
        void init();
        //void loop();

        //callback setters
        //void onConnect(void (*ncc)(Server* server, uint16_t fd, void* data));

    private:

        void *_data;

        //socket file descriptors for the server
        int _listenFd;
        int _connFd;

        //client connection data
        struct sockaddr_storage _clientAddr;
        
        //server socket details
        struct sockaddr_in _servAddr;
        
        //void (*newConnectionCallback) (Server* server, uint16_t fd, void*);

        //function prototypes for the server
        void setup(void* data, int port);
        void initializeSocket();
        void bindSocket();
        void startListen();
        void handleNewConnection();
};

void Server::setup(void* data, int port)
{
    _data = data;
	
	//initialize the server port as the port argument
	_servAddr.sin_port = port;
	//create the connection socket for server side
	_connFd = socket(AF_INET,SOCK_STREAM,0);
}


// Bind the socket to address/port
void Server::bindSocket()
{
	//bind the address to connection socket name
	bind(_connFd, (struct sockaddr *)&_servAddr, sizeof(_servAddr));
}

// Listen to incoming connections
void Server::startListen()
{
	//listen at the connection socket
	listen(_connFd, 1);
}

// Close the listening socket
void ::Server::shutdown()
{
	//close the socket
	close(_connFd);
}

 
void Server::handleNewConnection()
{
  	std::cout << "[SERVER] [CONNECTION] Waiting for a new connection\n";

	//if socket cant connect, connection fails
	if ((_listenFd = accept(_connFd, (struct sockaddr *)&_clientAddr,(socklen_t*)&_clientAddr))<0){
		std::cout<<"[SERVER] [CONNECTION] Connection failed\n";
	}
	//otherwise call newConnectionCallback on this server
	else{
		newConnectionCallback(this,_connFd, _data);
	}
}

void Server::init()
{
    initializeSocket();
    bindSocket();
    startListen();
}