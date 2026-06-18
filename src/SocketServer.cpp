#include "SocketServer.h"

SocketServer::SocketServer(int port) {
    // Initialize socket for server
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
    // Add Endpoints
    addEndpoint("/", "./html/index.html");
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
                    //TODO: mutex here so two things don't get the same socket? unless enqueue's mutex
                    //works for this too?

                    auto it = sockets_.find(fd.fd);
                    if (it == sockets_.end()) {return;}
                    SocketData& socketData = it->second;
                    size_t msg = recv(fd.fd, socketData.rBuffer, 4096, 0);
                    if (msg == 0) {toRemove.push(fd);continue;}
                    
                    std::cout << "Before " << socketData.sBuffer[0] << std::endl;

                    std::string test{"Hello"};
                    // Parse the HTTP request
                    threadPool_.enqueue([this](std::string& test){parseHTTP("");test = "goodbye";}, std::ref(test));
                    std::fill_n(socketData.rBuffer, 4096, 0); 

                    std::cout << test << std::endl;
                    std::cout << "After " << socketData.sBuffer[0] << std::endl;
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

HTTPMessage SocketServer::parseHTTP(std::string request) {
    /* Local Variables */
    HTTPMessage message;    
    std::istringstream iss(request);
    std::string method;     
    std::string requestTarget;
   
    // Determine method type
    iss >> method;
    
    if (method == "GET") {
        message.setRequestMethod(GET);

        // Serve the request target
        iss >> requestTarget;

        if (endpoints_.find(requestTarget) != endpoints_.end()) {
            std::string servedFile;
            serveFile(endpoints_.find(requestTarget)->second, servedFile);
            std::cout << "Served File:\n" << servedFile << std::endl;
        } else {
            std::cout << "Return error endpoint not found" << std::endl;
        }
        
    } else if (method == "HEAD") {
        message.setRequestMethod(HEAD);
    } else if (method == "PUT") {
        message.setRequestMethod(PUT);
    } else if (method == "CONNECT") {
        message.setRequestMethod(CONNECT);
    } else if (method == "OPTIONS") {
        message.setRequestMethod(OPTIONS);
    } else if (method == "TRACE") {
        message.setRequestMethod(TRACE);
    } else if (method == "POST") {
        message.setRequestMethod(POST);
    } else if (method == "PATCH") {
        message.setRequestMethod(PATCH);
    } else if (method == "DELETE") {
        message.setRequestMethod(DELETE);
    } else {
        message.setRequestMethod(NONE);
    }

    return message;
}

void SocketServer::serveFile(std::string path, std::string& htmlFile) {
    // Try to find file
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Error opening " << path << std::endl;
        return;
    }

    htmlFile.assign((std::istreambuf_iterator<char>(file)),
                    (std::istreambuf_iterator<char>()));
    file.close();
}

void SocketServer::addEndpoint(std::string endpoint, std::string path) {
    if (endpoints_.find(endpoint) == endpoints_.end()) {
        endpoints_.insert({endpoint, path});
    } else {
        std::cerr << "Cannot create endpoint " << endpoint << "(Endpoint already exists)" << std::endl;
    }
}
