#ifndef SERVER_HPP
#define SERVER_HPP


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>

namespace server{

    class Server{
    public:
        Server(int port);
        Server(const Server& orig);
        virtual ~Server();
        
        void shutdown();
        void init();
        void loop();

        //callback setters
        void onConnect(void (*ncc)(Server* server, uint16_t fd));

    private:
        int _listenFd;
        int _connFd;
        struct sockaddr_storage _clientAddr;
        struct sockaddr_in _servAddr;
        void (*newConnectionCallback) (Server* server, uint16_t fd);
        void setup(int port);
        void initializeSocket();
        void bindSocket();
        void startListen();
        void handleNewConnection();
    };
}
#endif
