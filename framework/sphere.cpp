#include "sphere.hpp"
#include "shape.hpp"
#include <cmath>

using namespace std;

//constructors

Sphere::Sphere() :
    Shape(),
	center_({0.0,0.0,0.0}),
	radius_{0.0f}
    {};

Sphere::Sphere(glm::vec3 const& cen, float rad) : 
    Shape(),
	center_{cen},
	radius_{rad}
    {};

//Task 5.3
Sphere::Sphere(glm::vec3 const& cen, float rad, std::string name, Color const& color) : 
    Shape(name,color),
    //name_{name},
    //color_{color},
	center_{cen},
	radius_{rad}
    {};

//functions
double Sphere::area() { //override causes error: virt-specifiers in 'area' not allowed outside a class definition
    return 4*M_PI*radius_*radius_;
};

double Sphere::volume() { //override causes error: virt-specifiers in 'volume' not allowed outside a class definition
    return (4.0/3.0)*M_PI*(radius_*radius_*radius_);
};

//Task 5.5
std::ostream& Sphere::print(std::ostream& os) const {
	Shape::print(os);
	os << "Center: " << "x: " << center_.x << " y: " << center_.y << " z: " <<center_.z << endl;
	os << "Radius: " << radius_ << endl;
 	return os;
}

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() {
    return radius_;
};
