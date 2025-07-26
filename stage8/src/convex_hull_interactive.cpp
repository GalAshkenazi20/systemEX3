#include "convex_hull_interactive.hpp"
#include <algorithm>
#include <sstream>

void ConvexHullInteractive::newGraph(int, const std::vector<Point>& newPoints) {
    points = newPoints;
}

void ConvexHullInteractive::newPoint(double x, double y) {
    points.emplace_back(x, y);
}

void ConvexHullInteractive::removePoint(double x, double y) {
    Point target(x, y);
    points.erase(std::remove(points.begin(), points.end(), target), points.end());
}

double ConvexHullInteractive::cross(const Point& O, const Point& A, const Point& B) const {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void ConvexHullInteractive::computeConvexHull() {
    hull.clear();
    if (points.size() <= 1) {
        hull.assign(points.begin(), points.end());
        return;
    }
    std::vector<Point> sorted = points;
    std::sort(sorted.begin(), sorted.end());
    std::deque<Point> lower, upper;
    for (const Point& p : sorted) {
        while (lower.size() >= 2 && cross(lower[lower.size()-2], lower.back(), p) <= 0)
            lower.pop_back();
        lower.push_back(p);
    }
    for (auto it = sorted.rbegin(); it != sorted.rend(); ++it) {
        while (upper.size() >= 2 && cross(upper[upper.size()-2], upper.back(), *it) <= 0)
            upper.pop_back();
        upper.push_back(*it);
    }
    lower.pop_back(); upper.pop_back();
    hull.insert(hull.end(), lower.begin(), lower.end());
    hull.insert(hull.end(), upper.begin(), upper.end());
}

std::string ConvexHullInteractive::calculateConvexHull() {
    computeConvexHull();
    std::ostringstream out;
    for (const Point& p : hull) {
        out << p.x << " " << p.y << "\n";
    }
    return out.str();
}

std::string ConvexHullInteractive::processCommand(const std::string& command) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    if (cmd == "Newgraph") {
        int n;
        iss >> n;
        std::vector<Point> pts;
        for (int i = 0; i < n; ++i) {
            double x, y;
            char comma;
            iss >> x >> comma >> y;  // קריאה עם פסיק מפריד
            pts.emplace_back(x, y);
        }
        newGraph(n, pts);
        return "Graph created\n";
    } else if (cmd == "Newpoint") {
        double x, y;
        char comma;
        iss >> x >> comma >> y;
        newPoint(x, y);
        return "Point added\n";
    } else if (cmd == "Removepoint") {
        double x, y;
        char comma;
        iss >> x >> comma >> y;
        removePoint(x, y);
        return "Point removed\n";
    } else if (cmd == "CH") {
        return calculateConvexHull();
    } else {
        return "Unknown command\n";
    }
}
