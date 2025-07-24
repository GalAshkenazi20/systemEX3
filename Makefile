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

# הרצה עם קובץ ברירת מחדל
run: $(TARGET)
	./$(TARGET)

# הרצה עם קובץ מותאם אישית
run-custom: $(TARGET)
	./$(TARGET) $(INPUT) $(OUTPUT)

# יצירת תיקיות הדרושות
setup:
	mkdir -p $(OBJDIR) input output

# יעדים פיקטיביים
.PHONY: all clean run run-custom setup
