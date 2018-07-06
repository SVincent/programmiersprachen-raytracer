#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:
    //constructors
    Box();
    Box(glm::vec3 const& min, glm::vec3 const& max);
    //Task 5.3
    Box(glm::vec3 const& min, glm::vec3 const& max, std::string name, Color const& color);

    //destructors
    //Task 5.8
    ~Box();

    //functions
    double area() override;
	double volume() override;
    //Task 5.5
    std::ostream& print(std::ostream& os) const override;
    //Task 6.3
    bool intersect(Ray const& ray, float& t);

    //getter
    glm::vec3 getMinimum() const;
    glm::vec3 getMaximum() const;

private:
    //member variables
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif