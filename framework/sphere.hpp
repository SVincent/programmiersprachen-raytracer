#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "shape.hpp"
#include "ray.hpp"
#include "Hit.hpp"
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
    //bool intersect(Ray const& ray, float& t) override;
    Hit intersect(Ray const& ray, float& t);
 
    //getter
    glm::vec3 getCenter() const;
    float getRadius();

private:
    //member variables
	glm::vec3 center_;
	float radius_;
};

#endif