#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <limits>
#include <glm/vec3.hpp>
#include <memory>

class Box: public Shape {
public:
    //constructors
    Box();
    Box(glm::vec3 const& min, glm::vec3 const& max);
    Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, std::shared_ptr<Material> material);

    //destructors
    ~Box();

    //functions
    double area() override;
	double volume() override;
    std::ostream& print(std::ostream& os) const override;
    Hit planeHit(Ray const& ray, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 vertex4) const;
    Hit intersect(Ray const& ray) override;

    //getter
    glm::vec3 getMinimum() const;
    glm::vec3 getMaximum() const;

private:
    //member variables
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif