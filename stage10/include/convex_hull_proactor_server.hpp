#ifndef CONVEX_HULL_PROACTOR_SERVER_HPP
#define CONVEX_HULL_PROACTOR_SERVER_HPP

// Stage 10: Implementation of Stage 9 with Producer-Consumer pattern
// Added features:
// - Area monitoring thread that waits for area >= 100 units  
// - POSIX condition variables for producer-consumer synchronization
// - Automatic notifications when area crosses 100 unit threshold

void runConvexHullProactorServer();

#endif
