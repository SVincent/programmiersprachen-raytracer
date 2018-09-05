#include "ray.hpp"

Ray Ray::transformRay(glm::mat4 inv_transfMat, Ray const& ray){
    Ray transformedRay;
    glm::vec3 transformedOrigin (inv_transfMat * glm::vec4(ray.origin,1));
    glm::vec3 transformedDirection (inv_transfMat * glm::vec4(ray.direction,0));

    transformedRay.origin = transformedOrigin;
    transformedRay.direction = transformedDirection;
    return transformedRay;
}