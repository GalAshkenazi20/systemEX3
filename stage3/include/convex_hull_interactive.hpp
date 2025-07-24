#ifndef CONVEX_HULL_INTERACTIVE_HPP
#define CONVEX_HULL_INTERACTIVE_HPP

#include "point.hpp"
#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

class ConvexHullInteractive {
private:
    std::vector<Point> points;
    std::deque<Point> hull;

    double cross(const Point& O, const Point& A, const Point& B) const;

    void computeConvexHull();
    
public:
    ConvexHullInteractive();
    ~ConvexHullInteractive();

    void newGraph(int n);
    
    void newPoint(double x, double y);

    void removePoint(double x, double y);

    void calculateConvexHull();

    void processCommands();

    const std::vector<Point>& getPoints() const { return points; }
    
      const std::deque<Point>& getHull() const { return hull; }
};

#endif
