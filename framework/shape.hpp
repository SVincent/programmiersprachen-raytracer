#ifndef SHAPE
#define SHAPE

#include <string>
#include "color.hpp"

class Shape {
public:
    //constructors
    Shape();
    Shape(std::string name, Color const& color);

    //functions
    virtual double area() = 0;
	virtual double volume() = 0;
    //Task 5.4
    virtual std::ostream& print(std::ostream& os) const;

    //getter
    std::string getName();
    Color getColor() const;

protected:
    //member variables
    std::string name_;
    Color color_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif