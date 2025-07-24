CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -g
INCLUDES = -Iinclude -Ireactor

REACTOR_SOURCES = reactor/reactor.cpp
SERVER_SOURCES = src/convex_hull_interactive.cpp src/convex_hull_reactor_server.cpp
CLIENT_SOURCES = 

REACTOR_OBJECTS = $(REACTOR_SOURCES:.cpp=.o)
SERVER_OBJECTS = $(SERVER_SOURCES:.cpp=.o)

SERVER_TARGET = server
CLIENT_TARGET = client

.PHONY: all clean server client

all: $(SERVER_TARGET) $(CLIENT_TARGET)

$(SERVER_TARGET): $(SERVER_OBJECTS) $(REACTOR_OBJECTS) server.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^
 
$(CLIENT_TARGET): client.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

server.o: server.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

client.o: client.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

server: $(SERVER_TARGET)

client: $(CLIENT_TARGET)

clean:
	rm -f $(SERVER_OBJECTS) $(REACTOR_OBJECTS) server.o client.o $(SERVER_TARGET) $(CLIENT_TARGET)

src/convex_hull_interactive.o: src/convex_hull_interactive.cpp include/convex_hull_interactive.hpp include/point.hpp
src/convex_hull_reactor_server.o: src/convex_hull_reactor_server.cpp include/convex_hull_reactor_server.hpp include/convex_hull_interactive.hpp
reactor/reactor.o: reactor/reactor.cpp reactor/reactor.hpp
server.o: server.cpp include/convex_hull_reactor_server.hpp
client.o: client.cpp
