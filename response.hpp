#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <arpa/inet.h>
#include "request.hpp"

namespace server{
	
	enum frame_type{
		DATA = 0,
		HEADERS = 1,
		PRIORITY = 2,
		RST_STREAM = 3,
		SETTINGS = 4,
		PUSH_PROMISE = 5,
		PING = 6,
		GOAWAY = 7,
		WINDOW_UPDATE = 8,
		CONTINUATION = 9
	};
	class Response{
	public:
		Response();
		Response(Request* req);
		Response(const Response& orig);
		char* toBytes();
		int getBytesCount();
		void handleGet();
		void handleOther();
		void buildHeader();
		void buildHeader2();
		char* buildFrame(int type, int flags);
        virtual ~Response();
	private:
		Request* _req;
		int _status;
		std::string _responseBody;
		std::string _responseHeader;

		/*static std::map<int, std::string> codes = {
			{}
		}*/
	};
}
#endif
