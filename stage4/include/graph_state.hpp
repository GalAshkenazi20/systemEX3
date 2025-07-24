#ifndef GRAPH_STATE_HPP
#define GRAPH_STATE_HPP

#include "point.hpp"
#include <vector>
#include <deque>
#include <mutex>

class GraphState {
private:
    std::vector<Point> points;
    std::deque<Point> hull;
    mutable std::mutex mtx;

    double cross(const Point& O, const Point& A, const Point& B) const;

    void computeConvexHull();
    
public:
    GraphState();
    ~GraphState();

    void newGraph(const std::vector<Point>& newPoints);
    

    void addPoint(const Point& point);

    void removePoint(const Point& point);
  
    std::deque<Point> getConvexHull();

    std::vector<Point> getPoints() const;

    void clear();
};

#endif
