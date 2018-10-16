#include "Hit.hpp"
#include <cmath>

Hit::Hit():
    hit_{false},
    shape_ {nullptr},
    intersectionPoint_{glm::vec3{INFINITY}},
    distance_{std::numeric_limits<float>::infinity()},
    normalVec_{glm::vec3(0.0,0.0,0.0)}
    {};

Hit::Hit(bool hit, Shape* shape, glm::vec3 intersectionPoint):
    hit_{hit},
    shape_{shape},
    intersectionPoint_{intersectionPoint},
    distance_{std::numeric_limits<float>::infinity()},
    normalVec_{glm::vec3(1.0,1.0,1.0)}
    {};
