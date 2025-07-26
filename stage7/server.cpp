#include "convex_hull_threaded_server.hpp"
#include <csignal>
#include <memory>

std::unique_ptr<ConvexHullThreadedServer> server;

void shutdown(int) {
    std::exit(0);
}

int main() {
    signal(SIGINT, shutdown);
    signal(SIGTERM, shutdown);

    server = std::make_unique<ConvexHullThreadedServer>();
    server->start(9034);
    return 0;
}