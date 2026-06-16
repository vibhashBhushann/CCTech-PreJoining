#include "Shape.h"
#include "Shapes.cpp"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(4, 6));
    shapes.push_back(std::make_unique<Triangle>(6, 8, 5, 5));

    std::sort(shapes.begin(), shapes.end(),
        [](const std::unique_ptr<Shape>& a, const std::unique_ptr<Shape>& b) {
            return a->area() < b->area();
        });

    std::cout << "--- Sorted by area ---" << std::endl;
    for (auto& shape : shapes) {
        shape->describe();
    }

    auto it = std::find_if(shapes.begin(), shapes.end(),
        [](const std::unique_ptr<Shape>& s) {
            return s->area() > 100;
        });

    std::cout << "--- First shape with area > 100 ---" << std::endl;
    if (it != shapes.end()) {
        (*it)->describe();
    } else {
        std::cout << "None found" << std::endl;
    }

    return 0;
}