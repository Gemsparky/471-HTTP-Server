#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>

namespace server{

	/*struct Header{
	}

	struct Body{
	}*/
	
	class Request{
	public:
		Request(const char* msg); //Since we are only building the server, we only need the constructor for bytes -> request object
		Request(const Request& original);
		virtual ~Request();
		std::string getMethod();
		std::string getURI();
		std::string getVersion();

	private:
		std::string _method;
		std::string _uri;
		std::string _version;
	}
}
