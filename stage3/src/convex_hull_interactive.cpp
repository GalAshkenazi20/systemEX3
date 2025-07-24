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
    
    // Build lower hull
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
    
    // Build upper hull
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
    
    // Remove last point of each half because it's repeated
    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();
    
    // Concatenate lower and upper hull
    hull.insert(hull.end(), lower.begin(), lower.end());
    hull.insert(hull.end(), upper.begin(), upper.end());
}

void ConvexHullInteractive::newGraph(int n) {
    points.clear();
    hull.clear();
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
}

void ConvexHullInteractive::newPoint(double x, double y) {
    points.emplace_back(x, y);
}

void ConvexHullInteractive::removePoint(double x, double y) {
    Point toRemove(x, y);
    points.erase(std::remove_if(points.begin(), points.end(),
        [&toRemove](const Point& p) { return p == toRemove; }), points.end());
}

void ConvexHullInteractive::calculateConvexHull() {
    computeConvexHull();
    
    // Output the convex hull points
    for (const Point& p : hull) {
        std::cout << p.x << " " << p.y << std::endl;
    }
}

void ConvexHullInteractive::processCommands() {
    std::string command;
    
    while (std::cin >> command) {
        if (command == "Newgraph") {
            int n;
            std::cin >> n;
            newGraph(n);
        }
        else if (command == "CH") {
            calculateConvexHull();
        }
        else if (command == "Newpoint") {
            double x, y;
            std::cin >> x >> y;
            newPoint(x, y);
        }
        else if (command == "Removepoint") {
            double x, y;
            std::cin >> x >> y;
            removePoint(x, y);
        }
    }
}
