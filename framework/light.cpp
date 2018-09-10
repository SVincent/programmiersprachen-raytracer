#include "light.hpp"

Light::Light():
    name_ {"light_default"},
    color_ {1.0, 1.0, 1.0},
    position_ {0.0, 0.0, 0.0},
    brightness_ {10}
    {};

Light::Light(std::string lightName, glm::vec3 lightPosition):
    name_ {lightName},
    color_ {1.0, 1.0, 1.0},
    position_ {lightPosition},
    brightness_ {10}
    {};

Light::Light(std::string lightName, glm::vec3 lightPosition, Color lightColor):
    name_ {lightName},
    color_ {lightColor},
    position_ {lightPosition},
    brightness_ {10}
    {};

Light::Light(std::string lightName, glm::vec3 lightPosition, Color lightColor, float brightness):
    name_ {lightName},
    color_ {lightColor},
    position_ {lightPosition},
    brightness_ {brightness}
    {};
