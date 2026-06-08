/**
 * @file SocketServer.h
 * 
 * @brief Basic server for tcp socket connections
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <iostream>
#include <cerrno>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>


/**
 * @class SocketServer
 *
 * @brief
 */
class SocketServer {
    public:
        /**
         * @brief Creates the initial server socket and starts listening on a port
         */
        SocketServer();

    private:
        int serverSocket;           /// File descriptor respresenting the servers socket  
        sockaddr_in serverAddress; 

};

#endif
