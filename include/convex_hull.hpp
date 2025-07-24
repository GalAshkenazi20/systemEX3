#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

struct Point {
    double x, y;
    
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
    
    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
    
    bool operator==(const Point& other) const {
        return std::abs(x - other.x) < 1e-9 && std::abs(y - other.y) < 1e-9;
    }
};

class ConvexHull {
private:
    std::vector<Point> points;
    std::vector<Point> hull;
    
    // חישוב המכפלה הוקטורית
    double cross(const Point& O, const Point& A, const Point& B) const;
    
    // אלגוריתם Andrew's monotone chain
    std::vector<Point> computeHull(std::vector<Point> points) const;

public:
    ConvexHull();
    ~ConvexHull();
    
    // קריאת נקודות מקובץ
    bool readPointsFromFile(const std::string& filename);
    
    // קריאת נקודות מ-stdin (עבור שלב 1)
    bool readPointsFromStdin();
    
    // חישוב המעטפת הקמורה
    void calculateConvexHull();
    
    // שמירת התוצאות לקובץ
    bool writeResultToFile(const std::string& filename) const;
    
    // הדפסת התוצאות ל-stdout (עבור שלב 1)
    void printResultToStdout() const;
    
    // חישוב שטח המעטפת הקמורה
    double calculateArea() const;
    
    // הדפסת התוצאות
    void printResult() const;
    
    // קבלת המעטפת הקמורה
    const std::vector<Point>& getHull() const;
};

#endif // CONVEX_HULL_HPP
