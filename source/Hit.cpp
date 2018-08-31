#include "Hit.hpp"

Hit::Hit():
    hit_{false},
    shape_ {nullptr},
    intersectionPoint_{0.0, 0.0, 0.0}
    {};

Hit::Hit(bool hit, Shape* shape, glm::vec3 intersectionPoint):
    hit_{hit},
    shape_{shape},
    intersectionPoint_{intersectionPoint}
    {};
