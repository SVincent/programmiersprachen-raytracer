#include "shape.hpp"
#include <string>
using namespace std;

//constructors
Shape::Shape() : 
    name_{"default"},
    color_{Color{0.0f,0.0f,0.0f}}
    {};
    
Shape::Shape(string name, Color const& color) :
    name_{name},
    color_{color}
    {};

//getter
string Shape::getName() {
    return name_;
};

Color Shape::getColor() const {
    return color_;
};

//Task 5.4
std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "Color: " << "red: " << color_.r << "green: " << color_.g << "blue: " << color_.b << endl;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return (s.print(os));
}