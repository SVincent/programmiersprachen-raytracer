#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
//#include "shape.hpp"
#include <limits>

class Shape;

struct Hit{
    //constructors
    Hit();

    Hit(bool hit, Shape* shape, glm::vec3 intersectionPoint);

    //members
    bool hit_;
    Shape* shape_{nullptr};
    glm::vec3 intersectionPoint_;
    glm::vec3 normalVec_;
    float distance_;
};
#endif