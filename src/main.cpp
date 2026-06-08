#include <iostream>

#include "ThreadPool.h"
#include "SocketServer.h"

int main () {
    ThreadPool threadPool;
    threadPool.start(); 
    
    SocketServer server;    

    threadPool.stop();
    return 0;
}


