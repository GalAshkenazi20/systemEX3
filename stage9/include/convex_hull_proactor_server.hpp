#ifndef CONVEX_HULL_PROACTOR_SERVER_HPP
#define CONVEX_HULL_PROACTOR_SERVER_HPP

// Stage 9: Implementation of Stage 7 (threaded server) using Stage 8 (Proactor library)
// Key difference from Stage 7: 
// - Stage 7: std::thread(...).detach() for each client
// - Stage 9: startProactor(...) using the library from Stage 8

void runConvexHullProactorServer();

#endif
