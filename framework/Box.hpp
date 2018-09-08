#ifndef BOX_HPP
#define BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

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
    //bool intersect(Ray const& ray, float& t);
    Hit intersect(Ray ray) override;

    //getter
    glm::vec3 getMinimum() const;
    glm::vec3 getMaximum() const;

private:
    //member variables
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif