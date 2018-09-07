#include "light.hpp"

Light::Light():
    name_ {"light_default"},
    color_ {1.0, 1.0, 1.0},
    position_ {0.0, 0.0, 0.0}
    {};

Light::Light(std::string lightName, glm::vec3 lightPosition):
    name_ {lightName},
    color_ {1.0, 1.0, 1.0},
    position_ {lightPosition}
    {};

Light::Light(std::string lightName, Color color, glm::vec3 lightPosition):
    name_ {lightName},
    color_ {color},
    position_ {lightPosition}
    {};

