#include "sphere.hpp"
#include "shape.hpp"
#include <glm/gtx/intersect.hpp>
//#include "ray.hpp"
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

//destructors
//Task 5.8
Sphere::~Sphere() {
    cout << "destructor class Sphere\n";
};

//functions
double Sphere::area() { 
    return 4*M_PI*radius_*radius_;
};

double Sphere::volume() { 
    return (4.0/3.0)*M_PI*(radius_*radius_*radius_);
};

//Task 5.5
std::ostream& Sphere::print(std::ostream& os) const {
	Shape::print(os);
	os << "Center: " << "x: " << center_.x << " y: " << center_.y << " z: " <<center_.z << endl;
	os << "Radius: " << radius_ << endl;
 	return os;
};

//Task 5.6
bool Sphere::intersect(Ray const& ray, float& t) {
    glm::vec3 direction = glm::normalize(ray.direction);
    float distance = 0.0f;
    return glm::intersectRaySphere(ray.origin,direction,center_,radius_*radius_,distance);
};

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() {
    return radius_;
};
