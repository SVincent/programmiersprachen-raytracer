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

    friend Ray transformRay(glm::mat4 const& inv_transfMat, Ray const& ray){
        Ray transformedRay;
        glm::vec3 transformedOrigin (inv_transfMat * glm::vec4(ray.origin,1));
        glm::vec3 transformedDirection (inv_transfMat * glm::vec4(ray.direction,0));

        transformedRay.origin = transformedOrigin;
        transformedRay.direction = transformedDirection;
        return transformedRay;
    }

    glm::vec3 origin;
    glm::vec3 direction;
};

#endif