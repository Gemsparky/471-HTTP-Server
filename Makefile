http_server: http_server.cpp server_handler.cpp server.cpp response.cpp request.cpp
	g++ -o http_server http_server.cpp server_handler.cpp server.cpp response.cpp request.cpp -Wall -g
