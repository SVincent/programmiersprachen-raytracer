#include "camera.hpp"
#include <iostream>
 
camera::camera():
    name_{"defaultCam"},
    origin_{0.0,0.0,0.0},
    direction_{0.0,0.0,-1.0},
    upVec_{0.0,0.0,0.0}
    {u_ = glm::normalize(glm::cross(direction_,upVec_));
     v_ = glm::normalize(glm::cross(u_, direction_));
     fov_ = 120.0;
    }

camera::camera(glm::vec3 origin, glm::vec3 direction, glm::vec3 upVec, float fov):
    origin_{origin},
    direction_{direction},
    upVec_{upVec},
    fov_{fov}
    {}

Ray camera::shootRay(glm::vec3 direction) const{
    Ray ray(origin_, direction);
    return ray;
}

Ray camera::shootRay(float x_, float y_, glm::vec3 direction){
    glm::mat4 camMatrix_ = {u_.x, v_.x, -direction_.x, origin_.x,
                            u_.y, v_.y, -direction_.y, origin_.y,
                            u_.z, v_.z, -direction_.z, origin_.z,
                            0.0, 0.0, 0.0, 1.0};
    Ray resultRay{glm::vec3{0.0, 0.0, 0.0}, glm::normalize(glm::vec3(x_,y_,-distance_))};
    glm::vec3 transformedOrigin (camMatrix_ * glm::vec4(resultRay.origin,1));
    glm::vec3 transformedDirection (camMatrix_ * glm::vec4(resultRay.direction,0));
    return Ray{glm::vec3{transformedOrigin.x, transformedOrigin.y, transformedOrigin.z},
               glm::vec3{transformedDirection.x, transformedDirection.y, transformedDirection.z}};
}
