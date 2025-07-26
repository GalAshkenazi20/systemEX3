CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -g
INCLUDES = -Iinclude -Iproactor

SRC = src/convex_hull_interactive.cpp \
      src/convex_hull_proactor_server.cpp \
      src/area_monitor.cpp \
      proactor/proactor.cpp \
      main.cpp

OBJ = $(SRC:.cpp=.o)

CLIENT_SRC = client.cpp
CLIENT_OBJ = $(CLIENT_SRC:.cpp=.o)

TARGET = server_proactor
CLIENT_TARGET = client_proactor

all: $(TARGET) $(CLIENT_TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

$(CLIENT_TARGET): $(CLIENT_OBJ)
	$(CXX) $(CXXFLAGS) $(CLIENT_OBJ) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(CLIENT_OBJ) $(TARGET) $(CLIENT_TARGET)

.PHONY: all clean
