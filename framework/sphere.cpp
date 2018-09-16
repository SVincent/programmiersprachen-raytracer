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

/*
// Line-Sphere intersection as described on wikipedia
Hit Sphere::intersect(Ray const& ray){
    Hit returnHit; 
    Ray newRay{ray.origin, glm::normalize(ray.direction)};
    newRay = transformRay(inv_transformationMatrix_,newRay);

    glm::vec3 ocVec = newRay.direction - center_;

    float docScalar = (newRay.direction.x* ocVec.x) + (newRay.direction.y* ocVec.y) + (newRay.direction.z* ocVec.z);
    float tempValue = (docScalar*docScalar)-((glm::length(newRay.origin - center_))*(glm::length(newRay.origin - center_))) + (radius_ * radius_);

    float rootValue = std::min(sqrt(tempValue), -sqrt(tempValue));
    
    float fullCalc = -1 * (docScalar) + rootValue;

    if (tempValue > 0){
        if (fullCalc > 0){

            glm::vec3 position = newRay.origin + newRay.direction;
            glm::vec3 normalized = glm::normalize(position - center_);
            glm::vec3 transformedPos{transformationMatrix_ * glm::vec4{position,1}};

            glm::vec4 normalizedTransf{glm::transpose(inv_transformationMatrix_)*glm::vec4{normalized,0}};
     
            returnHit.hit_= true;
            returnHit.shape_ = this;
            returnHit.intersectionPoint_=transformedPos;
            returnHit.distance_= fullCalc;
            returnHit.normalVec_=glm::vec3{normalizedTransf.x, normalizedTransf.y, normalizedTransf.z};
            
        }
    }
    return returnHit;
}*/

//intersect-method based on https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
Hit Sphere::intersect(Ray const& ray) {
  Hit sphere_hit;

  Ray newRay{ray.origin, glm::normalize(ray.direction)};
  newRay = transformRay(inv_transformationMatrix_, newRay);

  float t0; //distance to nearest intersection
  float t1; //distance to furthes intersection

  glm::vec3 L = center_ - newRay.origin;

  float tca = glm::dot(L, newRay.direction);

  float d2 = glm::dot(L, L) - tca * tca;

  if(d2 > (radius_ * radius_)) {
    return sphere_hit;
  }

  float thc = sqrt((radius_ * radius_) - d2);

  t0 = tca - thc;
  t1 = tca + thc;
  /*
    if (std::isnan(tca)) {
      cout << "ray origin: x: " << ray.origin.x << " y: " << ray.origin.y << " z: " << ray.origin.z << endl;
  }/*
  if (std::isnan(tca)) {
      cout << "tca NaN spilling" << endl;
  }
    if (std::isnan(thc)) {
      cout << "thc NaN spilling" << endl;
  }*/
  if(t0 > t1) {
    std::swap(t0, t1);
  }

  if(t0 < 0) {
    t0 = t1;

    if(t0 < 0) {
      return sphere_hit;
    }
  }

  sphere_hit.hit_ = true;
  sphere_hit.distance_ = t0;
  sphere_hit.shape_ = this;
  sphere_hit.intersectionPoint_ = newRay.origin + newRay.direction * sphere_hit.distance_;
  sphere_hit.normalVec_ = glm::normalize(sphere_hit.intersectionPoint_ - center_);
  sphere_hit.intersectionPoint_ = glm::vec3(inv_transformationMatrix_ * glm::vec4(sphere_hit.intersectionPoint_, 1));
  sphere_hit.normalVec_ = glm::vec3(glm::mat3(glm::transpose(inv_transformationMatrix_)) * sphere_hit.normalVec_);    

  return sphere_hit;
}

//getter
glm::vec3 Sphere::getCenter() const {
    return center_;
};

float Sphere::getRadius() const {
    return radius_;
};
