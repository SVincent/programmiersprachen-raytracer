#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "ray.hpp"
struct camera {
    //constructors
    camera();
    camera(glm::vec3 origin, glm::vec3 direction, glm::vec3 upVec);
    //members
    glm::vec3 origin;
    Ray shootRay(float x_s, float y_);
    //members 
    //Beobachtungspunkt e = origin
    //Blickrichtung n = direction
    //Up-Vektor up = upVec
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 upVec_;
    glm::vec3 u_;
    glm::vec3 v_;
    
    float distance_;
};
#endif 
