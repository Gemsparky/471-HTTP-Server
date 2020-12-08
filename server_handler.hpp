#ifndef SERVER_HANDLER_HPP
#define SERVER_HANDLER_HPP

#include <iostream>
#include "request.hpp"
#include "response.hpp"
#include "server.hpp"

namespace server{
	void OnNewClientConnected(net::Server* server, uint16_t fd, void* data);
	int sendBytes(uint16_t fd, char *messageBuffer, int count);
	int readBytes(uint16_t fd, char* buffer, unsigned int n);
}
