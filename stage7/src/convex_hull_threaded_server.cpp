#include "convex_hull_threaded_server.hpp"
#include <iostream>
#include <unistd.h>
#include <thread>
#include <netinet/in.h>
#include <cstring>

ConvexHullThreadedServer::ConvexHullThreadedServer() : server_fd(-1) {}

ConvexHullThreadedServer::~ConvexHullThreadedServer() {
    if (server_fd != -1) close(server_fd);
}

void ConvexHullThreadedServer::start(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) throw std::runtime_error("Failed to create socket");

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
        throw std::runtime_error("Bind failed");

    listen(server_fd, 10);
    std::cout << "Server listening on port " << port << std::endl;

    while (true) {
        socklen_t len = sizeof(address);
        int client_fd = accept(server_fd, (struct sockaddr*)&address, &len);
        if (client_fd >= 0) {
            std::thread(&ConvexHullThreadedServer::handleClient, this, client_fd).detach();
        }
    }
}

void ConvexHullThreadedServer::handleClient(int client_fd) {
    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes = read(client_fd, buffer, sizeof(buffer) - 1);
        if (bytes <= 0) break;

        std::string response;
        {
            std::lock_guard<std::mutex> lock(mutex);
            response = interactive.processCommand(buffer);
        }
        send(client_fd, response.c_str(), response.length(), 0);
    }
    close(client_fd);
    std::cout << "Client disconnected." << std::endl;
}
