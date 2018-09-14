#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <string>
#include "ray.hpp"

struct camera {
    //constructors
    camera();
    camera(glm::vec3 origin, glm::vec3 direction, glm::vec3 upVec, float fov);

    //methods
    Ray shootRay(glm::vec3 direction) const;
    Ray shootRay(float x_, float y_, glm::vec3 direction);

    //members 
    //Beobachtungspunkt e = origin
    //Blickrichtung n = direction
    //Up-Vektor up = upVec
    glm::vec3 origin_;
    glm::vec3 direction_;
    glm::vec3 upVec_;
    glm::vec3 u_;
    glm::vec3 v_;
    
    int xres_;
    int yres_;

    float distance_;
    float fov_;

    std::string name_;
};
#endif 
