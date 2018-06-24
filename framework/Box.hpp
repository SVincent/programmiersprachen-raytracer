#ifndef BOX
#define BOX

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:
    //constructors
    Box();
    Box(glm::vec3 const& min, glm::vec3 const& max);

    //functions
    double area();
	double volume();

    //getter
    glm::vec3 getMinimum();
    float getMaximum();

private:
    //member variables
	glm::vec3 minimum_;
	glm::vec3 maximum_;
};

#endif