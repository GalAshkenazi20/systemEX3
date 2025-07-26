#include "convex_hull_proactor_server.hpp"
#include "convex_hull_interactive.hpp"
#include "area_monitor.hpp"
#include "proactor.hpp"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>
#include <sys/socket.h>
#include <cstring>
#include <vector>
#include <pthread.h>
#include <signal.h>

#define PORT 9034
#define BUFFER_SIZE 1024

// Global shared state (like in stage 7)
static ConvexHullInteractive convexHull;
static std::mutex hullMutex;
static std::vector<pthread_t> client_threads;

// Signal handler for graceful shutdown (Stage 10)
void signalHandler(int signum) {
    std::cout << "\nShutting down server and area monitor..." << std::endl;
    AreaMonitor::stopMonitoring();
    exit(signum);
}

// Client handler function (adapted from stage 7's handleClient)
void* handleProactorClient(int client_fd) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) break;

        std::string command(buffer);
        std::string response;
        {
            // Same mutex protection as stage 7
            std::lock_guard<std::mutex> lock(hullMutex);
            response = convexHull.processCommand(command);
        }
        send(client_fd, response.c_str(), response.length(), 0);
    }
    close(client_fd);
    std::cout << "Proactor client disconnected." << std::endl;
    return nullptr;
}

void runConvexHullProactorServer() {
    // Setup signal handlers (Stage 10)
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    // Start area monitoring thread (Stage 10)
    AreaMonitor::startMonitoring();
    
    // Server setup (same as stage 7)
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return;
    }
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    
    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        close(server_fd);
        return;
    }
    
    if (listen(server_fd, 10) < 0) {
        std::cerr << "Listen failed" << std::endl;
        close(server_fd);
        return;
    }

    std::cout << "Stage 10: Proactor server with Area Monitor listening on port " << PORT << std::endl;
    std::cout << "Using Proactor pattern + Producer-Consumer for area monitoring" << std::endl;
    std::cout << "Monitor will notify when area >= 100 or < 100 units" << std::endl;

    while (true) {
        int client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd >= 0) {
            std::cout << "New client connected, starting proactor thread..." << std::endl;
            
            // KEY DIFFERENCE: Use Proactor library instead of std::thread
            // Stage 7 used: std::thread(&ConvexHullThreadedServer::handleClient, this, client_fd).detach();
            // Stage 9 uses: startProactor from the library we built in stage 8
            pthread_t thread_id = startProactor(client_fd, handleProactorClient);
            client_threads.push_back(thread_id);
        }
    }
    
    close(server_fd);
    AreaMonitor::stopMonitoring();
}
