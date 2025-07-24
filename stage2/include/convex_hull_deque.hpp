#ifndef CONVEX_HULL_DEQUE_HPP
#define CONVEX_HULL_DEQUE_HPP

#include <deque>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "point.hpp"  

class ConvexHullDeque {
private:
    std::vector<Point> points;  
    std::deque<Point> hull;     
    

    double cross(const Point& O, const Point& A, const Point& B) const;
    

    std::deque<Point> computeHull(std::vector<Point> points) const;

public:
    ConvexHullDeque();
    ~ConvexHullDeque();

    bool readPointsFromFile(const std::string& filename);
    
    bool readPointsFromStdin();
    
    void setPoints(const std::vector<Point>& inputPoints);

    void calculateConvexHull();

    bool writeResultToFile(const std::string& filename) const;

    void printResultToStdout() const;

    double calculateArea() const;

    void printResult() const;
    
    std::vector<Point> getHull() const;

    std::vector<Point> getPoints() const;
    
    std::chrono::duration<double> getLastExecutionTime() const;
    void resetTimer();
    
private:
    mutable std::chrono::duration<double> lastExecutionTime;
};

#endif 
