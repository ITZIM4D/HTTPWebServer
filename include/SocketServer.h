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

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ThreadPool.h"

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

        /**
         * @brief Parses the path and serves the file to the socket 
         *
         * @param[in] path The path of the file to be served
         * @param[out] sBuffer The sending buffer that the file will be sent in
         * @param[in] sBufferSize Size of the sending buffer
         */
        void serveFile(std::string path, char sBuffer[], size_t sBufferSize);
};

#endif
