#ifndef CONVEX_HULL_REACTOR_SERVER_HPP
#define CONVEX_HULL_REACTOR_SERVER_HPP

#include "convex_hull_interactive.hpp"
#include "../reactor/reactor.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <map>
#include <mutex>

#define PORT 9034
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

class ConvexHullReactorServer {
private:
    void* reactor;
    int server_fd;
    struct sockaddr_in address;
    ConvexHullInteractive convexHull;
    std::mutex server_mutex;
    
    // Map to store partial messages for each client
    static std::map<int, std::string> client_buffers;
    static ConvexHullReactorServer* instance;
    
    bool setupServer();
    
    // Static callback functions for the reactor
    static void* acceptConnection(int server_fd);
    static void* handleClient(int client_fd);
    
public:
    ConvexHullReactorServer();
    ~ConvexHullReactorServer();

    void start();
    void stop();
    
    // Helper method to process client command (thread-safe)
    std::string processClientCommand(const std::string& command);
};

#endif
