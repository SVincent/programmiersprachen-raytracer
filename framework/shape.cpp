#include "shape.hpp"
#include <string>

using namespace std;

//constructors
Shape::Shape() : 
    name_{"default"},
    material_{make_shared<Material>()} //todo: add default material
    {};

Shape::Shape(string name, shared_ptr<Material> material) :
    name_{name},
    material_{material}
    {}; 

//destructors
Shape::~Shape() {
    cout << "destructor class Shape\n";
};

//getter
string Shape::getName() {
    return name_;
};

shared_ptr<Material> Shape::getMaterial() {
    return material_;
};

//Task 5.4
std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "Material: \n " << *material_ << endl;
	return os;
};

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return (s.print(os));
};