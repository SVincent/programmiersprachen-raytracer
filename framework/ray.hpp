#ifndef RAY_HPP
#define RAY_HPP

#include <glm/glm.hpp>

struct Ray {

    //constructors
    Ray():
        origin{0.0f,0.0f,0.0f},
        direction{0.0f, 0.0f, -1.0f}
        {};

    Ray(glm::vec3 rayOrigin):
        origin{rayOrigin},
        direction{0.0f, 0.0f, -1.0f}
        {};

    Ray(glm::vec3 rayOrigin, glm::vec3 rayDirection):
        origin{rayOrigin},
        direction{rayDirection}
        {};

    // members

    Ray transformRay(glm::mat4 inv_transfMat, Ray const& ray) const;
    Ray transformRay(glm::mat4 inv_transfMat);

    glm::vec3 origin;
    glm::vec3 direction;
};

#endif