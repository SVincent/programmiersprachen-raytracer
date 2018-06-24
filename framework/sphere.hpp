#ifndef SPHERE
#define SPHERE

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
    //constructors
    Sphere();
    Sphere(glm::vec3 const& center, float radius);
    //Task 5.3
    Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color);

    //functions
    double area() override;
	double volume() override;

    //getter
    glm::vec3 getCenter() const;
    float getRadius();

private:
    //member variables
	glm::vec3 center_;
	float radius_;
};

#endif