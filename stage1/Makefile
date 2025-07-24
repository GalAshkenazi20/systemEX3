CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = convex_hull
SRCDIR = src
INCDIR = include
OBJDIR = obj

# קבצי המקור
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# יעד ראשי
all: $(TARGET)

# בניית התוכנית
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# בניית קבצי האובייקט
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# ניקוי
clean:
	rm -rf $(OBJDIR) $(TARGET)

# הרצה רגילה
run: $(TARGET)
	./$(TARGET)

# הרצה עם קלט מקובץ
run-with-file: $(TARGET)
	./$(TARGET) < input/step1_test.txt

# יצירת תיקיות הדרושות
setup:
	mkdir -p $(OBJDIR) input output

# יעדים פיקטיביים
.PHONY: all clean run run-with-file setup
