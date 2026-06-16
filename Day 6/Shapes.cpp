#include "Shape.h"
#include <iostream>
#include <cmath>

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}

    double area() override {
        return M_PI * radius * radius;
    }
    double perimeter() override {
        return 2 * M_PI * radius;
    }
    void describe() override {
        std::cout << "Circle - area: " << area() << ", perimeter: " << perimeter() << std::endl;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}

    double area() override {
        return width * height;
    }
    double perimeter() override {
        return 2 * (width + height);
    }
    void describe() override {
        std::cout << "Rectangle - area: " << area() << ", perimeter: " << perimeter() << std::endl;
    }
};

class Triangle : public Shape {
    double base, height, side1, side2;
public:
    Triangle(double b, double h, double s1, double s2)
        : base(b), height(h), side1(s1), side2(s2) {}

    double area() override {
        return 0.5 * base * height;
    }
    double perimeter() override {
        return base + side1 + side2;
    }
    void describe() override {
        std::cout << "Triangle - area: " << area() << ", perimeter: " << perimeter() << std::endl;
    }
};