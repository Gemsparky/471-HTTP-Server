#include "request.hpp"

server::Request::Request(){}

server::Request::Request(const char* msg, int size){
	//convert char array to string
	std::string str(msg, size);
	//break header into lines
	//vector<char*> lines = new vector<char*>;
	std::vector<std::string> lines/* = new vector<std::string>*/;
	std::istringstream input(str);
	std::string line;
	while(std::getline(input, line)){
		line.erase(std::remove(line.begin(), line.end(), '\r'),
				line.end());
		lines.push_back(line);
	}
	/*const char* current = msg;
	while(current){
		const char* next = strchr(current, '\r');
		int currentLen;
		if(next){
			currentLen = next - current;
		}else{
			//figure something out
			currentLen = size - current;
			//currentLen = 0;
			//break;
		}
	}*/
	//decode into the fields
	//std::string requestLine = lines[0];
	//TODO: Make sure carriage return is discarded if present
	std::vector<std::string> words;
	std::istringstream requestLine(lines[0]);
	std::string word;
	while(std::getline(requestLine, word, ' ')){
		words.push_back(word);
	}
	_method = words[0];
	if(words.size() > 1){
		_uri = words[1];
	}
	if(words.size() > 2){
		_version = words[2];
	}
}

server::Request::~Request(){}

std::string server::Request::getMethod(){
	return _method;
}

std::string server::Request::getURI(){
	return _uri;
}

std::string server::Request::getVersion(){
	return _version;
}
