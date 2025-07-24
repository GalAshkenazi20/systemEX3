#ifndef CONVEX_HULL_LIST_HPP
#define CONVEX_HULL_LIST_HPP

#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "point.hpp"


class ConvexHullList {
private:
    std::vector<Point> points;  
    std::list<Point> hull;      
    

    double cross(const Point& O, const Point& A, const Point& B) const;
    
    std::list<Point> computeHull(std::vector<Point> points) const;

public:
    ConvexHullList();
    ~ConvexHullList();
    

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
