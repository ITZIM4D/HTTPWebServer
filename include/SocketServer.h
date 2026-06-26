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
struct SocketData {
    std::array<char, 4096> rBuffer;
    std::array<char, 4096> sBuffer;
};

/**
 * @class SocketServer
 *
 * @brief
 */
class SocketServer {
    public:

        static const size_t BUFFER_SIZE = 4096;
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
         * @brief parses a request and sends a response to the socket
         *
         * @param[in] socketData The data of the requesting socket
         *
         */
        void parseHTTP(SocketData socketData);

        /**
         * @brief serves a requested file to a user
         *
         * @param[in] path The html file to be served
         * @param[out] htmlFile String of the file at the path
         * @param[out] contentLength The length of the html file
         */
        void serveFile(std::string path, std::array<char, BUFFER_SIZE>& htmlFile, int& contentLength);

        /**
         * @brief Adds an endpoint to the endpoint map
         *
         * @param[in] endpoint Endpoint that maps to a path
         * @param[in] path Path mapped to by the endpoint
         */
        void addEndpoint(std::string endpoint, std::string path);

    private:
        int serverSocket_;           /// File descriptor respresenting the servers socket  
        sockaddr_in serverAddress_;
        ThreadPool threadPool_;
        std::unordered_map<int, SocketData> sockets_;
        std::vector<pollfd> fds;
        std::stack<pollfd> toAdd; /// pollfds to add to fd
        std::stack<pollfd> toRemove; /// pollfds to remove from fd
        bool serverRunning_ = false; 
        std::unordered_map<std::string, std::string> endpoints_;
};

#endif
