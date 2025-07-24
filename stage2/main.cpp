#include "include/convex_hull_deque.hpp"
#include "include/convex_hull_list.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>

void runProfiling(const std::string& testName) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Running profiling test: " << testName << std::endl;
    std::cout << "========================================" << std::endl;
  
    ConvexHullDeque dequeImpl;
    ConvexHullList listImpl;

    std::cout << "Enter number of points followed by the points (x y):" << std::endl;
    
    if (!dequeImpl.readPointsFromStdin()) {
        std::cerr << "Error reading input" << std::endl;
        return;
    }

    listImpl.setPoints(dequeImpl.getPoints());
    
    std::cout << "\nRunning algorithms...\n" << std::endl;

    auto startDeque = std::chrono::high_resolution_clock::now();
    dequeImpl.calculateConvexHull();
    auto endDeque = std::chrono::high_resolution_clock::now();
    auto dequeTime = std::chrono::duration<double>(endDeque - startDeque);

    auto startList = std::chrono::high_resolution_clock::now();
    listImpl.calculateConvexHull();
    auto endList = std::chrono::high_resolution_clock::now();
    auto listTime = std::chrono::duration<double>(endList - startList);
    

    double dequeArea = dequeImpl.calculateArea();
    double listArea = listImpl.calculateArea();

    std::cout << "\n=== PROFILING RESULTS ===" << std::endl;
    std::cout << std::fixed << std::setprecision(6);
    
    std::cout << "\nDeque Implementation:" << std::endl;
    std::cout << "  Execution time: " << dequeTime.count() * 1000 << " ms" << std::endl;
    std::cout << "  Hull points: " << dequeImpl.getHull().size() << std::endl;
    std::cout << "  Area: " << dequeArea << std::endl;
    
    std::cout << "\nList Implementation:" << std::endl;
    std::cout << "  Execution time: " << listTime.count() * 1000 << " ms" << std::endl;
    std::cout << "  Hull points: " << listImpl.getHull().size() << std::endl;
    std::cout << "  Area: " << listArea << std::endl;
    

    std::cout << "\n=== COMPARISON ===" << std::endl;
    if (dequeTime < listTime) {
        double improvement = ((listTime.count() - dequeTime.count()) / listTime.count()) * 100;
        std::cout << "✓ Deque is FASTER by " << improvement << "%" << std::endl;
        std::cout << "  Deque is " << (listTime.count() / dequeTime.count()) << "x faster" << std::endl;
    } else if (listTime < dequeTime) {
        double improvement = ((dequeTime.count() - listTime.count()) / dequeTime.count()) * 100;
        std::cout << "✓ List is FASTER by " << improvement << "%" << std::endl;
        std::cout << "  List is " << (dequeTime.count() / listTime.count()) << "x faster" << std::endl;
    } else {
        std::cout << "Both implementations have similar performance" << std::endl;
    }

    if (std::abs(dequeArea - listArea) < 1e-9) {
        std::cout << "✓ Both implementations produce the same result" << std::endl;
    } else {
        std::cout << "⚠ Warning: Different results between implementations!" << std::endl;
    }
    
    std::cout << "\n=== ANALYSIS ===" << std::endl;
    std::cout << "Deque advantages:" << std::endl;
    std::cout << "  - O(1) insertion/deletion at both ends" << std::endl;
    std::cout << "  - Better cache locality than list" << std::endl;
    std::cout << "  - Random access to elements" << std::endl;
    
    std::cout << "\nList advantages:" << std::endl;
    std::cout << "  - O(1) insertion/deletion anywhere" << std::endl;
    std::cout << "  - No memory reallocation" << std::endl;
    std::cout << "  - Better for frequent insertions in middle" << std::endl;
    
    std::cout << "\nFor Convex Hull algorithm:" << std::endl;
    std::cout << "The algorithm mainly uses push_back() and pop_back() operations." << std::endl;
    std::cout << "Both deque and list provide O(1) for these operations." << std::endl;
    std::cout << "Performance difference likely comes from:" << std::endl;
    std::cout << "  - Memory locality (deque typically better)" << std::endl;
    std::cout << "  - Cache efficiency" << std::endl;
    std::cout << "  - Compiler optimizations" << std::endl;
}

int main() {
    std::cout << "=== Convex Hull Algorithm Profiling ===" << std::endl;
    std::cout << "Comparing std::deque vs std::list implementations" << std::endl;
    
    runProfiling("Performance Comparison");
    
    return 0;
}
