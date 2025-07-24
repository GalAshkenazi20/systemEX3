#include "../include/convex_hull_reactor_server.hpp"
#include <iostream>
#include <sstream>

std::map<int, std::string> ConvexHullReactorServer::client_buffers;
ConvexHullReactorServer* ConvexHullReactorServer::instance = nullptr;

ConvexHullReactorServer::ConvexHullReactorServer() : reactor(nullptr), server_fd(-1) {
    memset(&address, 0, sizeof(address));
    instance = this;
}

ConvexHullReactorServer::~ConvexHullReactorServer() {
    stop();
    instance = nullptr;
}

bool ConvexHullReactorServer::setupServer() {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return false;
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return false;
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return false;
    }
 
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_fd);
        return false;
    }
    
    std::cout << "Server listening on port " << PORT << std::endl;
    return true;
}

void* ConvexHullReactorServer::acceptConnection(int server_fd) {
    if (!instance) return nullptr;
    
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept failed");
        return nullptr;
    }
    
    std::cout << "New client connected: fd " << client_fd << std::endl;
    
    client_buffers[client_fd] = "";
    
    if (addFdToReactor(instance->reactor, client_fd, handleClient) < 0) {
        std::cerr << "Failed to add client fd to reactor" << std::endl;
        close(client_fd);
        client_buffers.erase(client_fd);
        return nullptr;
    }
    
    return nullptr;
}

void* ConvexHullReactorServer::handleClient(int client_fd) {
    if (!instance) return nullptr;
    
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    
    if (bytes_read <= 0) {
        std::cout << "Client disconnected from fd " << client_fd << std::endl;
        removeFdFromReactor(instance->reactor, client_fd);
        close(client_fd);
        client_buffers.erase(client_fd);
        return nullptr;
    }
    
    client_buffers[client_fd] += std::string(buffer, bytes_read);
    
    std::string& clientBuffer = client_buffers[client_fd];
    size_t pos;
    while ((pos = clientBuffer.find('\n')) != std::string::npos) {
        std::string command = clientBuffer.substr(0, pos);
        clientBuffer.erase(0, pos + 1);
        
        if (!command.empty() && command.back() == '\r') {
            command.pop_back();
        }
        
        if (!command.empty()) {
            std::cout << "Received from fd " << client_fd << ": " << command << std::endl;
            
            std::string response = instance->processClientCommand(command);
            
            send(client_fd, response.c_str(), response.length(), 0);
        }
    }
    
    return nullptr;
}

std::string ConvexHullReactorServer::processClientCommand(const std::string& command) {
    std::lock_guard<std::mutex> lock(server_mutex);
    return convexHull.processCommand(command);
}

void ConvexHullReactorServer::start() {
    if (!setupServer()) {
        return;
    }
    
    reactor = startReactor();
    if (!reactor) {
        std::cerr << "Failed to start reactor" << std::endl;
        close(server_fd);
        return;
    }
    
    if (addFdToReactor(reactor, server_fd, acceptConnection) < 0) {
        std::cerr << "Failed to add server fd to reactor" << std::endl;
        close(server_fd);
        stopReactor(reactor);
        return;
    }
    
    std::cout << "Convex Hull Reactor Server started on port " << PORT << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;
    
    runReactor(reactor);
}

void ConvexHullReactorServer::stop() {
    if (reactor) {
        stopReactor(reactor);
        reactor = nullptr;
    }
    
    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }
    
    client_buffers.clear();
}
