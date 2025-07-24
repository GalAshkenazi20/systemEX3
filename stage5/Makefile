CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -fPIC
REACTOR_DIR = reactor
OBJDIR = obj

STATIC_LIB = libreactor.a
SHARED_LIB = libreactor.so

REACTOR_SOURCES = $(REACTOR_DIR)/reactor.cpp
REACTOR_OBJECTS = $(REACTOR_SOURCES:%.cpp=$(OBJDIR)/%.o)

TEST_SOURCES = test_reactor.cpp
TEST_OBJECTS = $(TEST_SOURCES:%.cpp=$(OBJDIR)/%.o)
TEST_TARGET = test_reactor

DEMO_SOURCES = simple_demo.cpp
DEMO_OBJECTS = $(DEMO_SOURCES:%.cpp=$(OBJDIR)/%.o)
DEMO_TARGET = simple_demo

all: $(STATIC_LIB) $(SHARED_LIB) $(TEST_TARGET) $(DEMO_TARGET)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(OBJDIR)/$(REACTOR_DIR)

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(REACTOR_DIR) -c $< -o $@

$(STATIC_LIB): $(REACTOR_OBJECTS)
	ar rcs $@ $^

$(SHARED_LIB): $(REACTOR_OBJECTS)
	$(CXX) -shared -o $@ $^

$(TEST_TARGET): $(TEST_OBJECTS) $(STATIC_LIB)
	$(CXX) $(CXXFLAGS) $^ -L. -lreactor -o $@

$(DEMO_TARGET): $(DEMO_OBJECTS) $(STATIC_LIB)
	$(CXX) $(CXXFLAGS) $^ -L. -lreactor -o $@

clean:
	rm -rf $(OBJDIR) $(STATIC_LIB) $(SHARED_LIB) $(TEST_TARGET) $(DEMO_TARGET)

install: $(STATIC_LIB) $(SHARED_LIB)
	cp $(STATIC_LIB) /usr/local/lib/
	cp $(SHARED_LIB) /usr/local/lib/
	cp $(REACTOR_DIR)/reactor.hpp /usr/local/include/
	ldconfig

uninstall:
	rm -f /usr/local/lib/$(STATIC_LIB)
	rm -f /usr/local/lib/$(SHARED_LIB)
	rm -f /usr/local/include/reactor.hpp
	ldconfig

.PHONY: all clean install uninstall
