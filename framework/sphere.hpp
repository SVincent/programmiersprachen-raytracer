#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
    //constructors
    Sphere();
    Sphere(glm::vec3 const& center, float radius);
    //Task 5.3
    Sphere(glm::vec3 const& center, float radius, std::string name, Color const& color);

    //destructors
    //Task 5.8
    ~Sphere();

    //functions
    double area() override;
	double volume() override;
    //Task 5.5
    std::ostream& print(std::ostream& os) const override;
    //Task 5.6
    bool intersect(Ray const& ray, float& t) override;

    //getter
    glm::vec3 getCenter() const;
    float getRadius();

private:
    //member variables
	glm::vec3 center_;
	float radius_;
};

#endif