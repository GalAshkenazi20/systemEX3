CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -O2
INCLUDES = -Iinclude

SRCDIR = src
INCDIR = include
MAINDIR = main
OBJDIR = obj

SERVER_SOURCES = $(SRCDIR)/convex_hull_interactive.cpp \
                 $(SRCDIR)/convex_hull_threaded_server.cpp \
                 server.cpp

CLIENT_SOURCES = client.cpp

SERVER_OBJECTS = $(SERVER_SOURCES:%.cpp=$(OBJDIR)/%.o)
CLIENT_OBJECTS = $(CLIENT_SOURCES:%.cpp=$(OBJDIR)/%.o)

SERVER_EXEC = convex_hull_server
CLIENT_EXEC = convex_hull_client

all: $(SERVER_EXEC) $(CLIENT_EXEC)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)/$(SRCDIR)

# Compile source files to object files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Build server executable
$(SERVER_EXEC): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Build client executable
$(CLIENT_EXEC): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(SERVER_EXEC) $(CLIENT_EXEC)

.PHONY: all clean
