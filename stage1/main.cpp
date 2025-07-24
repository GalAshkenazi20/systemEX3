#include "../include/convex_hull.hpp"
#include <iostream>

int main() {
    ConvexHull convexHull;

    if (!convexHull.readPointsFromStdin()) {
        return 1;
    }

    convexHull.calculateConvexHull();

    double area = convexHull.calculateArea();

    std::cout << area << std::endl;

    return 0;
}
