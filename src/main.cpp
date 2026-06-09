#include <iostream>

#include "SocketServer.h"

int main () {    
    SocketServer server(8080);    
    server.run();

    server.stop();

    return 0;
}


