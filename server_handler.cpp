#include "server_handler.hpp"

void server::OnNewClientConnected(server::Server* s, uint16_t fd){
	std::cout << "New Connection" << std::endl;
	char* requestBytes = new char[8192]; //Max request size
	int count = readBytes(fd, requestBytes, 8192);
	//trace print request to terminal
	for(int i = 0; i < count; i++){
		std::cout << requestBytes[i];
	}
	server::Request* req = new server::Request(requestBytes, count);
	server::Response* res = new server::Response(req);
	int responseSize = res->getBytesCount();
	char* responseText = res->toBytes();
	//trace print response to terminal
	for(int i = 0; i < responseSize; i++){
		std::cout << responseText[i];
	}
	count = sendBytes(fd, responseText, responseSize);
	s->disconnect(); //End connection and wait for next request
}

int server::sendBytes(uint16_t fd, char *msg, int count){
	//cout << "Called SendBytes" << endl;
	int bytesSent = send(fd, msg, count, 0);
	if(bytesSent < 0){
		std::cout << "send() has failed\n";
	}
	return bytesSent;
}

int server::readBytes(uint16_t fd, char* buffer, unsigned int count){
	//cout << "Called ReadBytes" << endl;
    int bytesRead = read(fd, buffer, count);
	if(bytesRead < 0){
		std::cout << "read() has failed\n";
	}
    return bytesRead;
}
