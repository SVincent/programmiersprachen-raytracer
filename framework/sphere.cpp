#include "sphere.hpp"
#include <cmath>

//constructors
Sphere::Sphere() :
    Shape(),
	center_({0.0,0.0,0.0}),
	radius_{0.0}
    {};

Sphere::Sphere(glm::vec3 const& cen, float rad): {
    Shape();
	center_{cen},
	radius_{rad}
    {};

//functions
double Sphere::area() {
    return 4*M_PI*radius_*radius_;
};

double Sphere::volume() {
    return 4/3*M_PI*radius_*radius_*radius_;
};

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() {
    return radius_;
};
