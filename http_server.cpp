#include <iostream>
#include <string>
#include <getopt.h>
#include "server_handler.hpp"

int main(int argc, char** argv) {
    int port = 9090;
    server::Server* s = new server::Server(port);
    s->onConnect(server::OnNewClientConnected);
    s->init();
    s->loop();
}
