#include "sphere.hpp"
#include "shape.hpp"
#include <cmath>

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

//functions
double Sphere::area() { //override causes error: virt-specifiers in 'area' not allowed outside a class definition
    return 4*M_PI*radius_*radius_;
};

double Sphere::volume() { //override causes error: virt-specifiers in 'volume' not allowed outside a class definition
    return (4.0/3.0)*M_PI*(radius_*radius_*radius_);
};

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() {
    return radius_;
};
