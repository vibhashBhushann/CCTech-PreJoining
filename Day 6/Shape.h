#pragma once
#include <string>

class Shape {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual void describe() = 0;  
    virtual ~Shape() {}            
};