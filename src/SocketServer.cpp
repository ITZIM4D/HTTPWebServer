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

    fds.push_back(pollfd{serverSocket_, POLL_IN, 0});

    while (serverRunning_) {
        // Poll for input on any open socket
        int ready = poll(fds.data(), fds.size(), -1);

        // If poll returns an error
        if (ready < 0) {
            std::cerr << "Polling Error (errno: " << errno << ")" << std::endl;
            continue;
        }

        // For each open socket
        for (auto& fd : fds) {
            if (fd.revents & POLLIN) {
                if (fd.fd == serverSocket_) {
                    // Accept a client connection and add it to sockets map
                    int clientSocket = accept(serverSocket_, nullptr, nullptr);
                    sockets_.emplace(std::make_pair(clientSocket, SocketData{}));
                    toAdd.push(pollfd{clientSocket, POLLIN, 0}); 
                } else {
                    auto it = sockets_.find(fd.fd);
                    if (it == sockets_.end()) {return;}
                    SocketData& socketData = it->second;
                    size_t msg = recv(fd.fd, socketData.rBuffer, 4096, 0);
                    if (msg == 0) {toRemove.push(fd);continue;}
                    
                    // Parse the HTTP request
                    threadPool_.enqueue([this](auto str){parseHTTP(str);},std::string{socketData.rBuffer});
                    std::fill_n(socketData.rBuffer, 4096, 0); 
                }
            }
        }

        // Add and remove any sockets
        while (!toAdd.empty()) {
            fds.push_back(toAdd.top());
            toAdd.pop();
        } 
        while (!toRemove.empty()) {
            auto it = std::find_if(fds.begin(), fds.end(), 
                [&](const pollfd& p) {
                    return p.fd == toRemove.top().fd;
                }
            );
            fds.erase(it);
            toRemove.pop();
        }
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

void SocketServer::parseHTTP(std::string request) {
    std::cout << request << std::endl;  
}
