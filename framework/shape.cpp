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
 
string Shape::getName() {
    return name_;
};

Color Shape::getColor() const {
    return color_;
};