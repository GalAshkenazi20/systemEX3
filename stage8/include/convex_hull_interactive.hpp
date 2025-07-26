#ifndef CONVEX_HULL_INTERACTIVE_HPP
#define CONVEX_HULL_INTERACTIVE_HPP

#include "point.hpp"
#include <vector>
#include <deque>
#include <string>

class ConvexHullInteractive {
private:
    std::vector<Point> points;
    std::deque<Point> hull;

    double cross(const Point& O, const Point& A, const Point& B) const;
    void computeConvexHull();

public:
    void newGraph(int n, const std::vector<Point>& newPoints);
    void newPoint(double x, double y);
    void removePoint(double x, double y);
    std::string calculateConvexHull();
    std::string processCommand(const std::string& command);
};

#endif
