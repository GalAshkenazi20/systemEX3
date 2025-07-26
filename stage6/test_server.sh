#!/bin/bash

echo "Testing Stage 6 - Reactor-based Convex Hull Server"
echo "================================================="

# Test the server with commands
echo "Newgraph 4 0,0 1,0 0,1 1,1" | nc localhost 9034 &
sleep 1
echo "CH" | nc localhost 9034 &
sleep 1
echo "Newpoint 0.5,0.5" | nc localhost 9034 &
sleep 1
echo "CH" | nc localhost 9034 &
sleep 1

echo "Test completed!"
