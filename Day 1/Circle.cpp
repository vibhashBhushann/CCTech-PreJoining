#include "Shape.h"
#include <cmath>

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() override {
        return M_PI*radius*radius;
    }

    double perimeter() override {
        return 2*M_PI*radius;
    }

};