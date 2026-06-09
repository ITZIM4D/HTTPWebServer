/**
 * @file SocketServer.h
 * 
 * @brief Basic server for tcp socket connections
 */

#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <iostream>
#include <cerrno>
#include <fstream>

#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ThreadPool.h"

/**
 * @struct Socket
 *
 * @brief A socket structure that just contains the socket file descriptor and send/receive buffers
 */
struct Socket {
    int sockFD; /// File descriptor for the socket
    char rBuffer[1024];
    char sBuffer[1024];
};

/**
 * @class SocketServer
 *
 * @brief
 */
class SocketServer {
    public:
        /**
         * @brief Creates the initial server socket and starts listening on a port
         *
         * @param[in] port The port that the server will be running on
         */
        SocketServer(int port); 

        /**
         * @brief Starts the socket server listening on the port it is assigned
         */
        void run();

        /**
         * @brief Closes the socket server
         */
        void stop();

    private:
        int serverSocket_;           /// File descriptor respresenting the servers socket  
        sockaddr_in serverAddress_; 
        ThreadPool threadPool_;
        std::vector<std::unique_ptr<Socket>> sockets_;
        
        /**
         * @brief Serves a file based on a GET request for the specified file
         *
         * @param[in] socket The client socket that is requesting the file
         * @param[in] path The path of the file being requested
         */
        void serveFile(Socket socket, std::string path);
};

#endif
