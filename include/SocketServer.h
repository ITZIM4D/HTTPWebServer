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
#include <algorithm>
#include <sstream>

#include <poll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "ThreadPool.h"
#include "HTTPMessage.h"

/**
 * @struct Socket
 *
 * @brief A socket structure that just contains the socket file descriptor and send/receive buffers
 */
struct SocketData {
    char rBuffer[4096];
    char sBuffer[4096];
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

        /**
         * @brief parses a request and formats it
         */
        void parseHTTP(std::string request);

    private:
        int serverSocket_;           /// File descriptor respresenting the servers socket  
        sockaddr_in serverAddress_;
        ThreadPool threadPool_;
        std::unordered_map<int, SocketData> sockets_;
        std::vector<pollfd> fds;
        std::stack<pollfd> toAdd; /// pollfds to add to fd
        std::stack<pollfd> toRemove; /// pollfds to remove from fd
        bool serverRunning_ = false; 
};

#endif
