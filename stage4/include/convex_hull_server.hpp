#ifndef CONVEX_HULL_SERVER_HPP
#define CONVEX_HULL_SERVER_HPP

#include "convex_hull_interactive.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <mutex>

#define PORT 9034
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

class ConvexHullServer {
private:
    int server_fd;
    struct sockaddr_in address;
    ConvexHullInteractive convexHull;
    std::mutex server_mutex;
    
    void handleClient(int client_socket);

    bool setupServer();
    
public:
    ConvexHullServer();
    ~ConvexHullServer();

    void start();
    
    void stop();
};

#endif
