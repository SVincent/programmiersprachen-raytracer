#include "light.hpp"

light::light():
    name_ {"light_default"},
    color_ {1.0, 1.0, 1.0},
    position_ {0.0, 0.0, 0.0}
    {};

light::light(std::string lightName, glm::vec3 lightPosition):
    name_ {lightName},
    color_ {1.0, 1.0, 1.0},
    position_ {lightPosition}
    {};


