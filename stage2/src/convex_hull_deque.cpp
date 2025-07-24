#include "../include/convex_hull_deque.hpp"

ConvexHullDeque::ConvexHullDeque() : lastExecutionTime(0) {
    points.clear();
    hull.clear();
}

ConvexHullDeque::~ConvexHullDeque() {
    points.clear();
    hull.clear();
}

double ConvexHullDeque::cross(const Point& O, const Point& A, const Point& B) const {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}
bool ConvexHullDeque::readPointsFromFile(const std::string& filename) {
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

bool ConvexHullDeque::readPointsFromStdin() {
    int n;
    std::cin >> n;
    
    if (n <= 0) {
        std::cerr << "Error: Invalid number of points" << std::endl;
        return false;
    }
    
    points.clear();
    points.reserve(n);
    
    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x >> y;
        points.emplace_back(x, y);
    }
    
    return true;
}

void ConvexHullDeque::setPoints(const std::vector<Point>& inputPoints) {
    points = inputPoints;
}

std::deque<Point> ConvexHullDeque::computeHull(std::vector<Point> points) const {
    auto start = std::chrono::high_resolution_clock::now();
    
    int n = points.size();
    if (n <= 1) {
        auto end = std::chrono::high_resolution_clock::now();
        lastExecutionTime = end - start;
        std::deque<Point> result(points.begin(), points.end());
        return result;
    }
    
    std::sort(points.begin(), points.end());

    std::deque<Point> lower;
    for (int i = 0; i < n; i++) {
        while (lower.size() >= 2) {
            auto it = lower.end();
            --it;
            Point last = *it;
            --it;
            Point secondLast = *it;
            
            if (cross(secondLast, last, points[i]) <= 0) {
                lower.pop_back();  
            } else {
                break;
            }
        }
        lower.push_back(points[i]);  
    }
    

    std::deque<Point> upper;
    for (int i = n - 1; i >= 0; i--) {
        while (upper.size() >= 2) {
            auto it = upper.end();
            --it;
            Point last = *it;
            --it;
            Point secondLast = *it;
            
            if (cross(secondLast, last, points[i]) <= 0) {
                upper.pop_back();  
            } else {
                break;
            }
        }
        upper.push_back(points[i]);  
    }
    
    if (!lower.empty()) lower.pop_back();
    if (!upper.empty()) upper.pop_back();

    lower.insert(lower.end(), upper.begin(), upper.end());
    
    auto end = std::chrono::high_resolution_clock::now();
    lastExecutionTime = end - start;
    
    return lower;
}

void ConvexHullDeque::calculateConvexHull() {
    if (points.empty()) {
        return;
    }
    
    hull = computeHull(points);
}

bool ConvexHullDeque::writeResultToFile(const std::string& filename) const {
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

void ConvexHullDeque::printResultToStdout() const {
    std::cout << hull.size() << std::endl;
    
    for (const auto& point : hull) {
        std::cout << point.x << " " << point.y << std::endl;
    }
}

double ConvexHullDeque::calculateArea() const {
    if (hull.size() < 3) {
        return 0.0;
    }
    
    double area = 0.0;
    int n = hull.size();
    
    // חישוב שטח באמצעות נוסחת Shoelace
    auto it = hull.begin();
    for (int i = 0; i < n; i++) {
        auto current = it;
        ++it;
        if (it == hull.end()) it = hull.begin();
        
        area += current->x * it->y;
        area -= it->x * current->y;
    }
    
    return std::abs(area) / 2.0;
}

void ConvexHullDeque::printResult() const {
    std::cout << "\n=== Convex Hull Result (Deque Implementation) ===" << std::endl;
    std::cout << "Number of points in hull: " << hull.size() << std::endl;
    std::cout << "Execution time: " << lastExecutionTime.count() * 1000 << " ms" << std::endl;
    std::cout << "Points:" << std::endl;
    
    int i = 1;
    for (const auto& point : hull) {
        std::cout << "Point " << i++ << ": (" 
                  << point.x << ", " << point.y << ")" << std::endl;
    }
}

std::vector<Point> ConvexHullDeque::getHull() const {
    return std::vector<Point>(hull.begin(), hull.end());
}

std::vector<Point> ConvexHullDeque::getPoints() const {
    return points;
}

std::chrono::duration<double> ConvexHullDeque::getLastExecutionTime() const {
    return lastExecutionTime;
}

void ConvexHullDeque::resetTimer() {
    lastExecutionTime = std::chrono::duration<double>(0);
}
