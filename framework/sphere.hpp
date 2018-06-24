#ifndef SPHERE
#define SPHERE

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
    //constructors
    Sphere();
    Sphere(glm::vec3 const& center, float radius);

    //functions
    double area();
	double volume();

    //getter
    glm::vec3 getCenter();
    float getRadius();

private:
    //member variables
	glm::vec3 center_;
	float radius_;
};

#endif