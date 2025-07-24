CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = convex_hull_profiling
SRCDIR = src
INCDIR = include
OBJDIR = obj

SOURCES = $(wildcard $(SRCDIR)/*.cpp) main.cpp
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

run-with-file: $(TARGET)
	./$(TARGET) < test_input.txt

run-large-test: $(TARGET)
	echo "1000" > large_test.txt
	python3 -c "import random; [print(random.uniform(-100, 100), random.uniform(-100, 100)) for _ in range(1000)]" >> large_test.txt
	./$(TARGET) < large_test.txt
	rm large_test.txt

setup:
	mkdir -p $(OBJDIR) input output

debug: CXXFLAGS += -DDEBUG -g3
debug: $(TARGET)

release: CXXFLAGS = -std=c++17 -O3 -DNDEBUG -march=native
release: clean $(TARGET)

profile: CXXFLAGS += -pg
profile: clean $(TARGET)

.PHONY: all clean run run-with-file run-large-test setup debug release profile
