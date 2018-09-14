#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
    //constructors
    Sphere();
    Sphere(glm::vec3 const& center, float radius);
    Sphere(glm::vec3 const& center, float radius, std::string name, std::shared_ptr<Material> material);

    //destructors
    ~Sphere();

    //functions
    double area() override;
	double volume() override;
    std::ostream& print(std::ostream& os) const override;

    Hit intersect(Ray const& ray) override;
 
    //getter
    glm::vec3 getCenter() const;
    float getRadius() const;

    //member variables
	glm::vec3 center_;
	float radius_;
};

#endif