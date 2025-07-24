#include "../include/convex_hull.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "=== Convex Hull Calculator ===" << std::endl;
    
    std::string inputFile = "../input/points.txt";
    std::string outputFile = "../output/result.txt";
    
    // אם הועברו ארגומנטים מהשורת פקודה
    if (argc >= 2) {
        inputFile = argv[1];
    }
    if (argc >= 3) {
        outputFile = argv[2];
    }
    
    std::cout << "Input file: " << inputFile << std::endl;
    std::cout << "Output file: " << outputFile << std::endl;
    std::cout << "------------------------" << std::endl;
    
    // יצירת אובייקט ConvexHull
    ConvexHull convexHull;
    
    // קריאת הנקודות מהקובץ
    if (!convexHull.readPointsFromFile(inputFile)) {
        std::cerr << "Failed to read input file!" << std::endl;
        return 1;
    }
    
    // חישוב המעטפת הקמורה
    convexHull.calculateConvexHull();
    
    // הדפסת התוצאות
    convexHull.printResult();
    
    // שמירת התוצאות לקובץ
    if (!convexHull.writeResultToFile(outputFile)) {
        std::cerr << "Failed to write output file!" << std::endl;
        return 1;
    }
    
    std::cout << "\n=== Program completed successfully! ===" << std::endl;
    return 0;
}
