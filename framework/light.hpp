#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <string>
#include <glm/vec3.hpp>
#include "color.hpp"

struct Light{
    //constructors
    Light();
    Light(std::string lightName, glm::vec3 lightPosition);
    Light(std::string lightName, glm::vec3 lightPosition, Color lightColor);
    Light(std::string lightName, glm::vec3 lightPosition, Color lightColor, float brightness);

    //members
    std::string name_;
    Color color_;
    glm::vec3 position_;
    float brightness_;
};

#endif