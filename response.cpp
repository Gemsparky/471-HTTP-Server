#include "response.hpp"

server::Response::Response(){}

server::Response::Response(Request* req){
	_req = req;
	if(req->getMethod().compare("GET") == 0){
		handleGet();
	}else{
		//Send "501 Not Implemented"
		handleOther();
	}
}

server::Response::~Response(){}

void server::Response::handleGet(){
	//Read file contents into string
	std::string filename = _req->getURI();
	filename.erase(std::remove(filename.begin(), filename.end(), '/'),
			filename.end());
	std::ifstream inFile(filename);
	std::string responseBody;
	if(inFile){
		std::ostringstream strstream;
		strstream << inFile.rdbuf();
		responseBody = strstream.str();
		_responseBody = responseBody;
		_status = 200;
	}else{
		//If file is not found
		_status = 404;
		_responseBody = "<h1>404 Not Found</h1>";
	}
	//build header
	buildHeader();
}

void server::Response::handleOther(){
	_responseBody = "<h1>501 Not Implemented</h1>";
}

char* server::Response::toBytes(){
	std::string combined = _responseHeader + _responseBody;
	int len = combined.length();
	char* data = new char[len];
	memcpy(data, combined.data(), len);
	return data;
}

int server::Response::getBytesCount(){
	std::string combined = _responseHeader + _responseBody;
	return combined.length();
}

void server::Response::buildHeader(){
	std::string header = "HTTP/1.1 " + std::to_string(_status);
	switch(_status){
		case 200:
			header += " OK\r\n";
			break;
		case 404:
			header += " Not Found\r\n";
			break;
		case 101: //Turns out Firefox does not always use this
			header += " Switching Protocols\r\n";
			header += "Connection: Upgrade\r\n";
			header += "Upgrade: h2c\r\n";
			break;
		case 501:
			header += " Not Implemented\r\n";
		default:
			//throw error
			;
	}
	header += "Server: 471-HTTP-Server\r\n";
	header += "Content-Type: text/html\r\n";
	header += "Content-Length: " +
			std::to_string(_responseBody.length());
	header += "\r\n\r\n"; //Include a blank line
	_responseHeader = header;
}

//Build a Header frame for HTTP\2
void server::Response::buildHeader2(){
	std::string header = ":status: " + std::to_string(_status);
	header += "\r\n:version: HTTP/2.0";
	header += "\r\nserver: 471-HTTP-Server";
	header += "\r\ncontent-type: text/html";
	header += "\r\ncontent-length: " + std::to_string(_responseBody.length());
	header += "\r\n\r\n";
	_responseHeader = header;
}

//Build an HTTP\2 frame header and convert frame to bytes
char* server::Response::buildFrame(int type, int flags){
	int length;
	int stream = 1;
	std::string payload;
	switch(type){
		case DATA:
			length = _responseBody.length();
			payload = _responseBody;
			break;
		case HEADERS:
			length = _responseHeader.length();
			payload = _responseHeader;
			break;
		default:
			;
	}
	char* frame = new char[length + 9];
	uint32_t bigEndian32 = htonl(length);
	memcpy(frame, &bigEndian32, 24);
	uint16_t bigEndian16 = htons(type);
	memcpy(frame + 24, &bigEndian16, 8);
	bigEndian16 = htons(flags);
	memcpy(frame + 32, &bigEndian16, 8);
	bigEndian32 = htonl(stream);
	memcpy(frame + 41, &bigEndian32, 31);
	memcpy(frame + 72, payload.data(), length);
	return frame;	
}
