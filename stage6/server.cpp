#include "include/convex_hull_reactor_server.hpp"
#include <iostream>
#include <signal.h>

ConvexHullReactorServer* server = nullptr;

void signalHandler(int signum) {
    std::cout << "\nShutting down reactor server..." << std::endl;
    if (server) {
        server->stop();
    }
    exit(signum);
}

int main() {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    try {
        server = new ConvexHullReactorServer();
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
