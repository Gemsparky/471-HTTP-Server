#include "request.hpp"

server::Request::Request(){}

server::Request::Request(const char* msg, int size){
	//convert char array to C++ string (because it's easier)
	std::string str(msg, size);
	//break header into lines
	std::vector<std::string> lines;
	std::istringstream input(str);
	std::string line;
	while(std::getline(input, line)){
		line.erase(std::remove(line.begin(), line.end(), '\r'),
				line.end()); //Remove carriage returns
		lines.push_back(line);
	}
	//divide first line into needed data
	std::vector<std::string> words;
	if(!lines.empty()){
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
