#ifndef CONVEX_HULL_THREADED_SERVER_HPP
#define CONVEX_HULL_THREADED_SERVER_HPP

#include "convex_hull_interactive.hpp"
#include <mutex>
#include <string>

class ConvexHullThreadedServer {
private:
    int server_fd;
    std::mutex mutex;
    ConvexHullInteractive interactive;

public:
    ConvexHullThreadedServer();
    ~ConvexHullThreadedServer();

    void start(int port);
    void handleClient(int client_fd);
};

#endif
