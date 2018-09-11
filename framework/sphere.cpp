#include "sphere.hpp"
#include "shape.hpp"
#include <glm/gtx/intersect.hpp>
#include <cmath>

using namespace std;

//constructors
Sphere::Sphere() :
    Shape(),
	center_({0.0,0.0,0.0}),
	radius_{1.0f}
    {};

Sphere::Sphere(glm::vec3 const& cen, float rad) : 
    Shape(),
	center_{cen},
	radius_{rad}
    {};

//Task 5.3
Sphere::Sphere(glm::vec3 const& cen, float rad, string name, shared_ptr<Material> material) : 
    Shape(name, material),
	center_{cen},
	radius_{rad}
    {};

//destructors
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

std::ostream& Sphere::print(std::ostream& os) const {
	Shape::print(os);
	os << "Center: " << "x: " << center_.x << " y: " << center_.y << " z: " <<center_.z << endl;
	os << "Radius: " << radius_ << endl;
 	return os;
};

bool Sphere::intersectBool(Ray const& ray) {
    glm::vec3 direction = glm::normalize(ray.direction);
    float distance = 0.0f;
    return glm::intersectRaySphere(ray.origin,direction,center_,radius_*radius_,distance);
};

bool Sphere::intersectBoolTwo(const Ray& ray, float &t) const{
    const glm::vec3 o = ray.origin;
    const glm::vec3 d = ray.direction;
    const glm::vec3 oc = o - center_;
    const float b = 2 * glm::dot(oc, d);
    const float c = glm::dot(oc, oc) - radius_*radius_;
    float disc = b*b - 4 * c;
    if (disc < 1e-4) return false;
    disc = sqrt(disc);
    const float t0 = -b - disc;
    const float t1 = -b + disc;
    t = (t0 < t1) ? t0 : t1;
    return true;
}
// Line-Sphere intersection as described on wikipedia
Hit Sphere::intersect(Ray const& ray){
    //cout << "intersecting sphere " << this->getName() << std::endl;
    Hit returnHit; 
    Ray newRay = newRay.transformRay(inv_transformationMatrix_,ray);
    newRay.direction = glm::normalize(newRay.direction);
    glm::vec3 rDirection = newRay.direction;
    glm::vec3 rOrigin = newRay.origin;

    glm::vec3 ocVec = rOrigin - center_;
    float docScalar = (rDirection.x* ocVec.x) + (rDirection.y* ocVec.y) + (rDirection.z* ocVec.z);
    float tempValue = (docScalar*docScalar)-((glm::length(rOrigin - center_))*(glm::length(rOrigin - center_))) + (radius_ * radius_);

    float rootValue = std::min(sqrt(tempValue), -sqrt(tempValue));
    float fullCalc = -1 * (docScalar) + rootValue;

    if (tempValue > 0){
        if (fullCalc > 0){

            glm::vec3 position = rOrigin + rDirection;
            glm::vec3 normalized = glm::normalize(position - center_);
            glm::vec3 transformedPos{transformationMatrix_ * glm::vec4{position,1}};

            glm::vec4 normalizedTransf{glm::transpose(inv_transformationMatrix_)*glm::vec4{normalized,0}};
     
            returnHit.hit_= true;
            returnHit.shape_ = this;
            returnHit.intersectionPoint_=transformedPos;
            returnHit.distance_= fullCalc;
            returnHit.normalizedVec_=glm::vec3{normalizedTransf.x, normalizedTransf.y, normalizedTransf.z};
            
        }
    }
    return returnHit;
}

 glm::vec3 Sphere::getNormalized(const glm::vec3 pi) const{
     return (pi-center_)/radius_;
 }

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() const {
    return radius_;
};
