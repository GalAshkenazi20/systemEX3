#include "../include/convex_hull_server.hpp"
#include <iostream>

ConvexHullServer::ConvexHullServer() : server_fd(-1) {
    memset(&address, 0, sizeof(address));
}

ConvexHullServer::~ConvexHullServer() {
    stop();
}

bool ConvexHullServer::setupServer() {
    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return false;
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return false;
    }
    
    // Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket to address
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return false;
    }
    
    // Start listening
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("listen");
        close(server_fd);
        return false;
    }
    
    std::cout << "Server listening on port " << PORT << std::endl;
    return true;
}

void ConvexHullServer::handleClient(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    
    while (true) {
        // Clear buffer
        memset(buffer, 0, BUFFER_SIZE);
        
        // Read from client
        int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) {
            std::cout << "Client disconnected" << std::endl;
            break;
        }
        
        std::string command(buffer);
        std::cout << "Received command: " << command << std::endl;
        
        // Process command (thread-safe)
        std::string response;
        {
            std::lock_guard<std::mutex> lock(server_mutex);
            response = convexHull.processCommand(command);
        }
        
        // Send response back to client
        send(client_socket, response.c_str(), response.length(), 0);
    }
    
    close(client_socket);
}

void ConvexHullServer::start() {
    if (!setupServer()) {
        return;
    }
    
    std::cout << "Convex Hull Server started on port " << PORT << std::endl;
    
    while (true) {
        int addrlen = sizeof(address);
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (client_socket < 0) {
            perror("accept");
            continue;
        }
        
        std::cout << "New client connected" << std::endl;
        
        // Handle client in a new thread
        std::thread client_thread(&ConvexHullServer::handleClient, this, client_socket);
        client_thread.detach();
    }
}

void ConvexHullServer::stop() {
    if (server_fd != -1) {
        close(server_fd);
        server_fd = -1;
    }
}
