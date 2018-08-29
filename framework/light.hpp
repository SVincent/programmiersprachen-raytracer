#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

struct light{
    //constructors
    light();
    light(std::string lightName, glm::vec3 lightPosition);

    //members
    std::string name_;
    Color color_;
    glm::vec3 position_;
    // float brightness_;
};

#endif