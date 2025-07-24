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

    void newGraph(int n, const std::vector<Point>& newPoints);

    void newPoint(double x, double y);

    void removePoint(double x, double y);

    std::string calculateConvexHull();

    std::string processCommand(const std::string& command);

    const std::vector<Point>& getPoints() const { return points; }

    const std::deque<Point>& getHull() const { return hull; }

    void clear();
};

#endif
