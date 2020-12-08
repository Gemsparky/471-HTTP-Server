#include "server_handler.hpp"

void server::OnNewClientConnected(server::Server* s, uint16_t fd,
		void* data){
	cout << "New Connection" << endl;
	char* requestBytes = new char[1024];
	//call the thing here
	server::Request* req = new server::Request(requestBytes, 1024);
	server::Response* res = new server::Response(req);
	int responseSize =
}
