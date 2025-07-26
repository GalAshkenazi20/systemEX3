#include "convex_hull_proactor_server.hpp"
#include "convex_hull_interactive.hpp"
#include "proactor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <sys/socket.h>
#include <cstring>

#define PORT 9034
#define BUFFER_SIZE 1024

static ConvexHullInteractive convexHull;
static std::mutex hullMutex;

void* handleClient(int client_fd) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) break;

        std::string command(buffer);
        std::string response;
        {
            std::lock_guard<std::mutex> lock(hullMutex);
            response = convexHull.processCommand(command);
        }
        send(client_fd, response.c_str(), response.length(), 0);
    }
    close(client_fd);
    std::cout << "Client disconnected." << std::endl;
    return nullptr;
}

void runConvexHullProactorServer() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 10);

    std::cout << "Proactor server listening on port " << PORT << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd >= 0) {
            startProactor(client_fd, handleClient);
        }
    }
}
