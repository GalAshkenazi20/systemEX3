#!/bin/bash

echo "=== Testing Stage 10 - Producer Consumer Pattern ==="
echo "Testing area monitoring with 100+ units threshold"
echo

# Create a large square that should have area > 100
echo "Testing large area (should trigger >= 100 message):"
echo "Newgraph 4 0,0 15,0 15,15 0,15" | nc -w 1 localhost 9034
sleep 2
echo "CH" | nc -w 1 localhost 9034
sleep 2

echo
echo "Testing small area (should trigger < 100 message):"
echo "Newgraph 4 0,0 1,0 1,1 0,1" | nc -w 1 localhost 9034  
sleep 2
echo "CH" | nc -w 1 localhost 9034
sleep 2

echo
echo "Testing large area again (should trigger >= 100 message again):"
echo "Newgraph 4 0,0 20,0 20,20 0,20" | nc -w 1 localhost 9034
sleep 2
echo "CH" | nc -w 1 localhost 9034

echo
echo "Test completed!"
