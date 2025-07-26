#include "../include/convex_hull.hpp"

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

bool ConvexHull::readPointsFromStdin() {
    int n;
    std::cin >> n;  // קריאה ישירה ללא הודעה
    
    if (n <= 0) {
        std::cerr << "Error: Invalid number of points" << std::endl;
        return false;
    }
    
    points.clear();
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        double x, y;
        char comma;
        std::cin >> x >> comma >> y;  // קריאה עם פסיק מפריד
        points.emplace_back(x, y);
    }
    
    return true;
}

std::vector<Point> ConvexHull::computeHull(std::vector<Point> points) const {
    int n = points.size();
    if (n <= 1) return points;
    

    std::sort(points.begin(), points.end());
    
    std::vector<Point> lower;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2 && 
               cross(lower[lower.size()-2], lower[lower.size()-1], points[i]) <= 0) {
            lower.pop_back();
        }
        lower.push_back(points[i]);
    }
    
    std::vector<Point> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2 && 
               cross(upper[upper.size()-2], upper[upper.size()-1], points[i]) <= 0) {
            upper.pop_back();
        }
        upper.push_back(points[i]);
    }

    lower.pop_back();
    upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    
    return lower;
}

void ConvexHull::calculateConvexHull() {
    if (points.empty()) {
        return;
    }
    
    hull = computeHull(points);
}

bool ConvexHull::writeResultToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot create output file " << filename << std::endl;
        return false;
    }
    
    file << hull.size() << std::endl;
    
    for (const auto& point : hull) {
        file << point.x << " " << point.y << std::endl;
    }
    
    file.close();
    
    std::cout << "Results written to " << filename << std::endl;
    return true;
}

void ConvexHull::printResultToStdout() const {
    // הדפסת התוצאות בפורמט הנדרש לשלב 1
    std::cout << hull.size() << std::endl;
    
    for (const auto& point : hull) {
        std::cout << point.x << " " << point.y << std::endl;
    }
}

double ConvexHull::calculateArea() const {
    if (hull.size() < 3) {
        return 0.0; // אין שטח למעטפת עם פחות מ-3 נקודות
    }
    
    double area = 0.0;
    int n = hull.size();
    
    // חישוב שטח באמצעות נוסחת Shoelace
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += hull[i].x * hull[j].y;
        area -= hull[j].x * hull[i].y;
    }
    
    return std::abs(area) / 2.0;
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
