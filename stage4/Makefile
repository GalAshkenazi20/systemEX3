CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -pthread
SRCDIR = src
INCDIR = include
OBJDIR = obj

# Source files
SERVER_SOURCES = $(SRCDIR)/convex_hull_interactive.cpp $(SRCDIR)/convex_hull_server.cpp server.cpp
SERVER_OBJECTS = $(SERVER_SOURCES:%.cpp=$(OBJDIR)/%.o)

CLIENT_SOURCES = client.cpp
CLIENT_OBJECTS = $(CLIENT_SOURCES:%.cpp=$(OBJDIR)/%.o)

# Targets
SERVER_TARGET = convex_hull_server
CLIENT_TARGET = convex_hull_client

# Default target
all: $(SERVER_TARGET) $(CLIENT_TARGET)

# Create object directory
$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(SRCDIR)

# Compile object files
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Link server executable
$(SERVER_TARGET): $(SERVER_OBJECTS)
	$(CXX) $(CXXFLAGS) $(SERVER_OBJECTS) -o $(SERVER_TARGET)

# Link client executable
$(CLIENT_TARGET): $(CLIENT_OBJECTS)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJECTS) -o $(CLIENT_TARGET)

# Clean target
clean:
	rm -rf $(OBJDIR) $(SERVER_TARGET) $(CLIENT_TARGET)

# Install target (optional)
install: $(SERVER_TARGET)
	cp $(SERVER_TARGET) /usr/local/bin/

# Uninstall target (optional)
uninstall:
	rm -f /usr/local/bin/$(SERVER_TARGET)

.PHONY: all clean install uninstall
