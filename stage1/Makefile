CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = convex_hull
INCDIR = include

# קבצי המקור (ישירות בתיקיית השורש)
SOURCES = main.cpp convex_hull.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# יעד ראשי
all: $(TARGET)

# בניית התוכנית
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# בניית קבצי האובייקט
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# ניקוי
clean:
	rm -f *.o $(TARGET)

# הרצה רגילה
run: $(TARGET)
	./$(TARGET)

# יעדים פיקטיביים
.PHONY: all clean run
