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
    Ray newRay = transformRay(inv_transformationMatrix_,ray);
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
            returnHit.normalVec_=glm::vec3{normalizedTransf.x, normalizedTransf.y, normalizedTransf.z};
            
        }
    }
    return returnHit;
}*/

Hit Sphere::intersect(Ray const& inray)
{
  Hit sphere_hit;

  Ray ray
  {
    inray.origin,

    glm::normalize(inray.direction)

  };


  ray = transformRay(inv_transformationMatrix_, ray);


  float t0;
  float t1;

  glm::vec3 L = center_ - ray.origin;

  float tca = glm::dot(L, ray.direction);

  float d2 = glm::dot(L, L) - tca * tca;

  if(d2 > (radius_ * radius_))
  {
    return sphere_hit;
  }

  float thc = sqrt((radius_ * radius_) - d2);

  t0 = tca - thc;

  t1 = tca + thc;

  if(t0 > t1)
  {
    std::swap(t0, t1);
  }

  if(t0 < 0)
  {
    t0 = t1;

    if(t0 < 0)
    {
      return sphere_hit;
    }
  }

  sphere_hit.hit_ = true;
  sphere_hit.distance_ = t0;
  sphere_hit.shape_ = this;
  sphere_hit.intersectionPoint_ = ray.origin + ray.direction * sphere_hit.distance_;
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
