#include "../include/convex_hull_interactive.hpp"

ConvexHullInteractive::ConvexHullInteractive() {
    points.clear();
    hull.clear();
}

ConvexHullInteractive::~ConvexHullInteractive() {
    points.clear();
    hull.clear();
}

double ConvexHullInteractive::cross(const Point& O, const Point& A, const Point& B) const {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void ConvexHullInteractive::computeConvexHull() {
    hull.clear();
    
    if (points.empty()) {
        return;
    }
    
    if (points.size() == 1) {
        hull.push_back(points[0]);
        return;
    }
    
    std::vector<Point> sortedPoints = points;
    std::sort(sortedPoints.begin(), sortedPoints.end());

    std::deque<Point> lower;
    for (const Point& p : sortedPoints) {
        while (lower.size() >= 2) {
            auto it = lower.end();
            --it;
            Point last = *it;
            --it;
            Point secondLast = *it;
            
            if (cross(secondLast, last, p) <= 0) {
                lower.pop_back();
            } else {
                break;
            }
        }
        lower.push_back(p);
    }

    std::deque<Point> upper;
    for (auto it = sortedPoints.rbegin(); it != sortedPoints.rend(); ++it) {
        const Point& p = *it;
        while (upper.size() >= 2) {
            auto uit = upper.end();
            --uit;
            Point last = *uit;
            --uit;
            Point secondLast = *uit;
            
            if (cross(secondLast, last, p) <= 0) {
                upper.pop_back();
            } else {
                break;
            }
        }
        upper.push_back(p);
    }
    
    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();
    
    hull.insert(hull.end(), lower.begin(), lower.end());
    hull.insert(hull.end(), upper.begin(), upper.end());
}

void ConvexHullInteractive::newGraph(int n, const std::vector<Point>& newPoints) {
    points.clear();
    hull.clear();
    points = newPoints;
}

void ConvexHullInteractive::newPoint(double x, double y) {
    points.emplace_back(x, y);
}

void ConvexHullInteractive::removePoint(double x, double y) {
    Point toRemove(x, y);
    points.erase(std::remove_if(points.begin(), points.end(),
        [&toRemove](const Point& p) { return p == toRemove; }), points.end());
}

std::string ConvexHullInteractive::calculateConvexHull() {
    computeConvexHull();
    
    std::stringstream result;
    for (const Point& p : hull) {
        result << p.x << " " << p.y << "\n";
    }
    return result.str();
}

std::string ConvexHullInteractive::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    
    if (cmd == "Newgraph") {
        int n;
        iss >> n;
        
        std::vector<Point> newPoints;
        newPoints.reserve(n);
        
        for (int i = 0; i < n; i++) {
            double x, y;
            iss >> x >> y;
            newPoints.emplace_back(x, y);
        }
        
        newGraph(n, newPoints);
        return "Graph created with " + std::to_string(n) + " points\n";
    }
    else if (cmd == "CH") {
        return calculateConvexHull();
    }
    else if (cmd == "Newpoint") {
        double x, y;
        iss >> x >> y;
        newPoint(x, y);
        return "Point (" + std::to_string(x) + ", " + std::to_string(y) + ") added\n";
    }
    else if (cmd == "Removepoint") {
        double x, y;
        iss >> x >> y;
        removePoint(x, y);
        return "Point (" + std::to_string(x) + ", " + std::to_string(y) + ") removed\n";
    }
    else {
        return "Unknown command\n";
    }
}

void ConvexHullInteractive::clear() {
    points.clear();
    hull.clear();
}
