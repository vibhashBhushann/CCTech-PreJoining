#include <iostream>
#include <memory>    
#include "Shape.h"
#include "Circle.cpp"  

int main() {
    std::unique_ptr<Shape> s = std::make_unique<Circle>(5.0);

    std::cout << "Area: "<< s->area()<< std::endl;
    std::cout << "Perimeter: "<< s->perimeter()<< std::endl;
    return 0;
}