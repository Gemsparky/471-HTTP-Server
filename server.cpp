#include "server.hpp"

server::Server::Server(int port)
{
    setup(port);
}

server::Server::Server(const Server& orig)
{
}

server::Server::~Server()
{
	std::cout << "[SERVER] [DESTRUCTOR] Destroying Server...\n";
	close(_listenFd);
}

void server::Server::setup(int port){
	//std::cout << "Called setup(data, port)\n";
	//std::cout << htons(port);
	_listenFd = socket(AF_INET, SOCK_STREAM, 0);
	_servAddr.sin_family = AF_INET;
	_servAddr.sin_addr.s_addr = INADDR_ANY;
	_servAddr.sin_port = htons(port);
}

void server::Server::initializeSocket(){
	std::cout << "[SERVER] initializing socket\n";
	//std::cout << "Called initializeSocket\n";
	int optValue = 1;
	int retTest = -1;
	retTest = setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue));
	printf("[SERVER] setsockopt() ret %d\n", retTest);
	if (retTest < 0) {
        perror("[SERVER] [ERROR] setsockopt() failed");
		shutdown();
    }
}

// Bind the socket to address/port
void server::Server::bindSocket(){
	std::cout << "Called bindSocket\n";
	int res = bind(_listenFd, (struct sockaddr*) &_servAddr, sizeof(_servAddr));
}

// Listen to incoming connections
void server::Server::startListen(){
	//std::cout << "Called startListen\n";
	int res = listen(_listenFd, 1); //Maybe ask about backlog size
}

// Close the listening socket
void server::Server::shutdown(){
	//std::cout << "Called shutdown on server\n";
	int res = close(_listenFd);
}

void server::Server::handleNewConnection(){
  	std::cout << "[SERVER] [CONNECTION] Waiting for a new connection\n";
	//std::cout << "Called handleNewConnection\n";
	socklen_t clientSize = htons(sizeof(_clientAddr));
	_connFd = accept(_listenFd, (struct sockaddr*) &_clientAddr, &clientSize);
	//std::cout << "Called accept\n";
	newConnectionCallback(this, _connFd);
}

void server::Server::loop(){
	//std::cout << "Called loop\n";
	while(true){
		handleNewConnection();
	}
}

void server::Server::init(){
    initializeSocket();
    bindSocket();
    startListen();
}

void server::Server::onConnect(void(*ncc)(Server*, uint16_t)){
    newConnectionCallback = ncc;
}

/*int server::Server::sendBytes(uint16_t fd, char *msg, int count){
	//cout << "Called SendBytes" << endl;
	int bytesSent = send(fd, msg, count, 0);
	if(bytesSent < 0){
		std::cout << "send() has failed\n";
	}
	return bytesSent;
}

int server::Server::readBytes(uint16_t fd, char* buffer,
		unsigned int count){
	//cout << "Called ReadBytes" << endl;
    int bytesRead = read(fd, buffer, count);
	if(bytesRead < 0){
		std::cout << "read() has failed\n";
	}
    return bytesRead;
}*/
