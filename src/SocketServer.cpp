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
    serverRunning_ = true;
    // Start up the threadpool
    threadPool_.start();
    
    listen(serverSocket_, 5);

    pollfd fds{serverSocket_, POLL_IN};
    int pollValue;

    while (serverRunning_) {
        // Poll for connection every tenth of a secoond
        while ((pollValue = poll(&fds, 1, 100)) == 0) {
            ;            
        }

        // If poll returns an error
        if (pollValue == -1) {
            std::cerr << "Polling Error (errno: " << errno << ")" << std::endl;
            return;

        }

        std::cout << "Socket connected #" << sockets_.size() << std::endl;
        sockets_.emplace_back(std::make_unique<Socket>(
            Socket{accept(serverSocket_, nullptr, nullptr)} 
        ));

        recv(sockets_[0]->sockFD, sockets_[0]->rBuffer, sizeof(sockets_[0]->rBuffer), 0);
        std::cout << sockets_[0]->rBuffer << std::endl;
    }

        //TODO: Make this parse the requested file for a get request and send it back
        //char arr[200]="HTTP/1.1 200 OK\nContent-Type:text/html\nContent-Length: 16\n\n<h1>testing</h1>";
        //int send_res=send(clientSocket,arr,sizeof(arr),0);
}

void SocketServer::stop() {
    // Close server and clean up 
    serverRunning_ = false;
    close(serverSocket_);
    threadPool_.stop();
}
