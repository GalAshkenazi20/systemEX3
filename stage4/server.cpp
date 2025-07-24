#include "include/convex_hull_server.hpp"
#include <iostream>
#include <signal.h>

ConvexHullServer* server = nullptr;

void signalHandler(int signum) {
    std::cout << "\nShutting down server..." << std::endl;
    if (server) {
        server->stop();
    }
    exit(signum);
}

int main() {
    // Set up signal handler for graceful shutdown
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    try {
        server = new ConvexHullServer();
        server->start();
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
        return 1;
    }
    
    if (server) {
        delete server;
    }
    
    return 0;
}
