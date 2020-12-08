#include "response.hpp"
#include "request.hpp"
#include <iostream>

main(int argc, char** argv){
	const char requestText[] = "GET /index.html HTTP/1.1\r\nHost: testhost\r\nAccept: text/html\r\n";
	int len = 61;
	server::Request * req = new server::Request(requestText, 61);
	server::Response * res = new server::Response(req);
	char * responseText = res->toBytes();
	int responseLen = res->getBytesCount();
	for(int i = 0; i < responseLen; i++){
		std::cout << responseText[i];
	}
}
