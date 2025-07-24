#include "../include/convex_hull.h"

ConvexHull::ConvexHull() {
    points.clear();
    hull.clear();
}

ConvexHull::~ConvexHull() {
    points.clear();
    hull.clear();
}

double ConvexHull::cross(const Point& O, const Point& A, const Point& B) const {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

bool ConvexHull::readPointsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return false;
    }
    
    int n;
    file >> n;
    
    if (n <= 0) {
        std::cerr << "Error: Invalid number of points" << std::endl;
        return false;
    }
    
    points.clear();
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        double x, y;
        file >> x >> y;
        points.emplace_back(x, y);
    }
    
    file.close();
    
    std::cout << "Successfully read " << points.size() << " points from file." << std::endl;
    return true;
}

std::vector<Point> ConvexHull::computeHull(std::vector<Point> points) const {
    int n = points.size();
    if (n <= 1) return points;
    
    // מיון הנקודות לפי x ואז לפי y
    std::sort(points.begin(), points.end());
    
    // בניית החצי התחתון של המעטפת
    std::vector<Point> lower;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 && 
               cross(lower[lower.size()-2], lower[lower.size()-1], points[i]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(points[i]);
    }
    
    // בניית החצי העליון של המעטפת
    std::vector<Point> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 && 
               cross(upper[upper.size()-2], upper[upper.size()-1], points[i]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(points[i]);
    }
    
    // הסרת הנקודה האחרונה מכל חצי (כפילות)
    lower.pop_back();
    upper.pop_back();
    
    // איחוד החצאים
    lower.insert(lower.end(), upper.begin(), upper.end());
    
    return lower;
}

void ConvexHull::calculateConvexHull() {
    if (points.empty()) {
        std::cerr << "Error: No points to process" << std::endl;
        return;
    }
    
    hull = computeHull(points);
    
    std::cout << "Convex hull calculated with " << hull.size() << " points." << std::endl;
}

bool ConvexHull::writeResultToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create output file " << filename << std::endl;
        return false;
    }
    
    // כתיבת מספר הנקודות במעטפת
    file << hull.size() << std::endl;
    
    // כתיבת הנקודות
    for (const auto& point : hull) {
        file << point.x << " " << point.y << std::endl;
    }
    
    file.close();
    
    std::cout << "Results written to " << filename << std::endl;
    return true;
}

void ConvexHull::printResult() const {
    std::cout << "\n=== Convex Hull Result ===" << std::endl;
    std::cout << "Number of points in hull: " << hull.size() << std::endl;
    std::cout << "Points:" << std::endl;
    
    for (size_t i = 0; i < hull.size(); i++) {
        std::cout << "Point " << (i + 1) << ": (" 
                  << hull[i].x << ", " << hull[i].y << ")" << std::endl;
    }
}

const std::vector<Point>& ConvexHull::getHull() const {
    return hull;
}
