#include "SocketServer.h"

SocketServer::SocketServer(int port) {
    serverSocket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket_== -1) {
        std::cerr << "Error Creating Server Socket, Error: " << errno << std::endl;
        return;
    }

    serverAddress_.sin_family = AF_INET;
    serverAddress_.sin_port = htons(port);
    serverAddress_.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    bind(serverSocket_, (struct sockaddr*)&serverAddress_, sizeof(serverAddress_));
}

void SocketServer::run() {
    // Start up the threadpool
    threadPool_.start();

    listen(serverSocket_, 5);
    // Accept client connection
    int clientSocket = accept(serverSocket_, nullptr, nullptr);

    char rBuffer[1024] = {0};
    recv(clientSocket, rBuffer, sizeof(rBuffer), 0);

    char sBuffer[1024] = {0};
    serveFile("./html/index.html", sBuffer, 1024);

    send(clientSocket, sBuffer, sizeof(sBuffer), 0);
    std::cout << "Message from client " << rBuffer << std::endl;
}

void SocketServer::stop() {
    // Close server and clean up 
    close(serverSocket_);
    threadPool_.stop();
}

void SocketServer::serveFile(std::string path, char sBuffer[], size_t sBufferSize) {
    // Open file 
    std::ifstream file(path);
    char c;
    size_t curr = 0;

    if (!file.is_open()) {
        std::cerr << "Error opening file " << path << std::endl;
        return;
    } 
    
    while (file.get(c) && curr < sBufferSize) {
        sBuffer[curr++] = c;
    }

    file.close();
}
