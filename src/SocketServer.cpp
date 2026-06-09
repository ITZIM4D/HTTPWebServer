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
    //int clientSocket = accept(serverSocket_, nullptr, nullptr);
    
    pollfd fds{serverSocket_, POLL_IN};

    // Poll every 1 second for a connection 
    while(poll(&fds, 1, 1000) < 1) {
        std::cout << "Waiting for connection... " << std::endl;
    }

    std::cout << "Connection found!";

    //char rBuffer[1024] = {0};
    //recv(clientSocket, rBuffer, sizeof(rBuffer), 0);

    //std::cout << "Message from client:\n" << rBuffer << std::endl;
    //
    //TODO: Make this parse the requested file for a get request and send it back
    //char arr[200]="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";
    //int send_res=send(clientSocket,arr,sizeof(arr),0);
}

void SocketServer::stop() {
    // Close server and clean up 
    close(serverSocket_);
    threadPool_.stop();
}
