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



//object to store data received from socket and how many bytes were received
struct DataBytes{
    int bytes;
    char *data;
};

//Server class
class Server{
    public:
        Server(void* data);
        Server(void* data, int port);
        Server(const Server& orig);
        virtual ~Server();
        
        void shutdown();
        void init();
        void loop();

        //callback setters
        void onConnect(void (*ncc)(Server* server, uint16_t fd, void* data));

    private:

        void* _data;

        //socket file descriptors
        int _listenFd;
        int _connFd;

        //client connection data
        struct sockaddr_storage _clientAddr;
        
        //server socket details
        struct sockaddr_in _servAddr;
        
        void (*newConnectionCallback) (Server* server, uint16_t fd, void*);

        //function prototypes
        void setup(void* data, int port);
        void initializeSocket();
        void bindSocket();
        void startListen();
        void handleNewConnection();
};

//A function that reads from the socket, and return both the data and the number of bytes read
DataBytes ReadBytes(uint16_t someSocket){
    //create DataBytes object to return at the end
    DataBytes result;
    //store bytes and data received from reading the socket in DataBytes object attributes respectively
    result.bytes = read(someSocket, result.data, 4096, 0);

    if (results.bytes < 0){
        cerr<<"Error in receiving HTTP request"<<endl;
        return DataBytes temp = {0, ""};
    }
    else (results.bytes > 0){
        return result;
    }
}

//A function that takes data and a number x and writes x bytes of data to the socket/sends it
int WriteBytes(uint16_t someSocket, char *data, int x) {
    int bytesSent;
    bytesSent = send(someSocket, data, x, 0);
    return bytesSent;
}

