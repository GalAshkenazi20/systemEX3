#include "reactor/reactor.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* global_reactor = nullptr;

// Signal handler for graceful shutdown
void signalHandler(int signum) {
    std::cout << "\nShutting down reactor..." << std::endl;
    if (global_reactor) {
        stopReactor(global_reactor);
    }
    exit(signum);
}

// Callback function for handling client connections
void* handleClient(int client_fd) {
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    
    if (bytes_read <= 0) {
        std::cout << "Client disconnected from fd " << client_fd << std::endl;
        removeFdFromReactor(global_reactor, client_fd);
        close(client_fd);
        return nullptr;
    }
    
    std::cout << "Received from fd " << client_fd << ": " << buffer << std::endl;
    
    // Echo the message back
    std::string response = "Echo: " + std::string(buffer);
    send(client_fd, response.c_str(), response.length(), 0);
    
    return nullptr;
}

// Callback function for accepting new connections
void* acceptConnection(int server_fd) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if (client_fd < 0) {
        perror("accept failed");
        return nullptr;
    }
    
    std::cout << "New client connected: fd " << client_fd << std::endl;
    
    // Add the new client to the reactor
    if (addFdToReactor(global_reactor, client_fd, handleClient) < 0) {
        std::cerr << "Failed to add client fd to reactor" << std::endl;
        close(client_fd);
        return nullptr;
    }
    
    return nullptr;
}

int createServerSocket() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket failed");
        return -1;
    }
    
    // Set socket options
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        return -1;
    }
    
    // Configure address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return -1;
    }
    
    // Start listening
    if (listen(server_fd, 5) < 0) {
        perror("listen failed");
        close(server_fd);
        return -1;
    }
    
    return server_fd;
}

int main() {
    // Set up signal handler
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    std::cout << "Starting reactor test server..." << std::endl;
    
    // Create reactor
    global_reactor = startReactor();
    if (!global_reactor) {
        std::cerr << "Failed to start reactor" << std::endl;
        return 1;
    }
    
    // Create server socket
    int server_fd = createServerSocket();
    if (server_fd < 0) {
        stopReactor(global_reactor);
        return 1;
    }
    
    std::cout << "Server listening on port " << PORT << std::endl;
    
    // Add server socket to reactor
    if (addFdToReactor(global_reactor, server_fd, acceptConnection) < 0) {
        std::cerr << "Failed to add server fd to reactor" << std::endl;
        close(server_fd);
        stopReactor(global_reactor);
        return 1;
    }
    
    std::cout << "Reactor started. Press Ctrl+C to stop." << std::endl;
    
    // Run the reactor
    runReactor(global_reactor);
    
    // Cleanup
    close(server_fd);
    stopReactor(global_reactor);
    
    return 0;
}
