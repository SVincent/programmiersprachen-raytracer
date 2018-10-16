#include "Box.hpp"
#include <cmath>
#include <glm/gtx/intersect.hpp>

using namespace std;

//constructors
Box::Box() :
    Shape("default", make_shared<Material>(Material())),
	minimum_({0.0,0.0,0.0}),
	maximum_({0.0,0.0,0.0})
    {};

Box::Box(glm::vec3 const& min, glm::vec3 const& max) : 
    Shape("default", make_shared<Material>(Material())),
	minimum_{min},
	maximum_{max}
    {};

Box::Box(glm::vec3 const& min, glm::vec3 const& max, string name, shared_ptr<Material> material) : 
    Shape(name, material),
	minimum_{min},
	maximum_{max}
    {};

//destructors
Box::~Box() {
    cout << "destructor class Box\n";
};

//functions
double Box::area()  {
    double lenght = maximum_.x - minimum_.x;
    double width = maximum_.y - minimum_.y;
    double height = maximum_.z - minimum_.z;

    return 2*(lenght*height+lenght*width+height*width);
};

double Box::volume()  {
    /* functionally equivalent to the following
    double lenght = maximum_.x - minimum_.x;
    double width = maximum_.y - minimum_.y;
    double height = maximum_.z - minimum_.z; 
    return length*width*height; */

    return (maximum_.x - minimum_.x)*(maximum_.y - minimum_.y)*(maximum_.z - minimum_.z);
};

std::ostream& Box::print(std::ostream& os) const {
	Shape::print(os);
	os << "Minimum: " << "x: " << minimum_.x << " y: " << minimum_.y << " z: " << minimum_.z << endl;
	os << "Maximum: " << "x: " << maximum_.x << " y: " << maximum_.y << " z: " << maximum_.z << endl;
	return os;
};


Hit Box::intersect(Ray const& ray) {
    Ray newRay = transformRay(inv_transformationMatrix_,ray);
    glm::vec3 inv_direction {1.0/newRay.direction.x,1.0/newRay.direction.y,1.0/newRay.direction.z};

    float t1 = (maximum_.x - newRay.origin.x) * inv_direction.x;
    float t2 = (minimum_.x - newRay.origin.x) * inv_direction.x;
    float t3 = (maximum_.y - newRay.origin.y) * inv_direction.y;
    float t4 = (minimum_.y - newRay.origin.y) * inv_direction.y;
    float t5 = (maximum_.z - newRay.origin.z) * inv_direction.z;
    float t6 = (minimum_.z - newRay.origin.z) * inv_direction.z;

    //Range on x-Ebene for possible intersection
    float tmax = std::max(t1,t2);
    float tmin = std::min(t1,t2);
    //Range on y-Ebene for possible intersection after looking at x-plane
    tmax = std::min(std::max(t3,t4),tmax);
    tmin = std::max(std::min(t3,t4),tmin);
    //Range on z-Ebene for possible intersection after looking at x and y
    tmax = std::min(std::max(t5,t6),tmax);
    tmin = std::max(std::min(t5,t6),tmin);

    Hit b_hit;

    if (tmax > std::max(0.0f, tmin)) {
        b_hit.distance_ = sqrt(tmin * tmin *
                             (newRay.direction.x * newRay.direction.x +
                              newRay.direction.y * newRay.direction.y +
                              newRay.direction.z * newRay.direction.z)
                            );

        b_hit.intersectionPoint_ = glm::vec3{
            tmin * newRay.direction.x,
            tmin * newRay.direction.y,
            tmin * newRay.direction.z
        };

        //glm::vec3 normal{std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
        glm::vec3 normal{0.0f,0.0f,0.0f};
        float bias = 0.0009f;
        //getting the normal vec on the side of the intersection
        if (abs(b_hit.intersectionPoint_.x - maximum_.x) < bias) {
            normal = glm::vec3{1.0, 0.0, 0.0};
        } else if (abs(b_hit.intersectionPoint_.x - minimum_.x) < bias) {
            normal = glm::vec3{-1.0, 0.0, 0.0};
        } else if (abs(b_hit.intersectionPoint_.y - maximum_.y) < bias) {
            normal = glm::vec3{0.0, 1.0, 0.0};
        } else if (abs(b_hit.intersectionPoint_.y - minimum_.y) < bias) {
            normal = glm::vec3{0.0, -1.0, 0.0};
        } else if (abs(b_hit.intersectionPoint_.z - maximum_.z) < bias) {
            normal = glm::vec3{0.0, 0.0, 1.0};
        } else if (abs(b_hit.intersectionPoint_.z - minimum_.z) < bias) {
            normal = glm::vec3{0.0, 0.0, -1.0};
        }

        b_hit.normalVec_ = normal;
        b_hit.shape_ = this;
        b_hit.hit_ = true;
    }

    return b_hit;
} 
/*
Hit Box::intersect(Ray const& newRay) {
    Hit returnHit;
    
    if (minimum_.x > maximum_.x) {std::swap (minimum_.x,maximum_.x);};
    if (minimum_.y > maximum_.y) {std::swap (minimum_.y,maximum_.y);};
    if (minimum_.z < maximum_.z) {std::swap (minimum_.z,maximum_.z);};
    

    glm::vec3 vertices[8];
    vertices[0] = glm::vec3{minimum_.x, minimum_.y, minimum_.z};
    vertices[1] = glm::vec3{minimum_.x, minimum_.y, maximum_.z};
    vertices[2] = glm::vec3{minimum_.x, maximum_.y, minimum_.z};
    vertices[3] = glm::vec3{minimum_.x, maximum_.y, maximum_.z};
    vertices[4] = glm::vec3{maximum_.x, minimum_.y, minimum_.z};
    vertices[5] = glm::vec3{maximum_.x, minimum_.y, maximum_.z};
    vertices[6] = glm::vec3{maximum_.x, maximum_.y, minimum_.z};
    vertices[7] = glm::vec3{maximum_.x, maximum_.y, maximum_.z};

    Hit hits[6];
    hits[0] = planeHit(newRay, vertices[0], vertices[1], vertices[2], vertices[3]); //ZY-plane, minimum
    hits[1] = planeHit(newRay, vertices[4], vertices[5], vertices[6], vertices[7]); //ZY-plane, maximum
    hits[2] = planeHit(newRay, vertices[0], vertices[1], vertices[4], vertices[5]); //XZ-plane, minimum
    hits[3] = planeHit(newRay, vertices[2], vertices[3], vertices[6], vertices[7]); //XZ-plane, maximum
    hits[4] = planeHit(newRay, vertices[0], vertices[2], vertices[4], vertices[6]); //XY-plane, minimum
    hits[5] = planeHit(newRay, vertices[1], vertices[3], vertices[5], vertices[7]); //XY-plane, maximum

    Hit closest; 

    for (auto& hit : hits) {
        if (hit.hit_ && hit.distance_ > 0.01 && hit.distance_ < closest.distance_) {
            closest = hit;
        } 
    }

    if (closest.hit_) {
        closest.shape_ = this;
        return closest;
    }
};

Hit Box::planeHit(Ray const& newRay, glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, glm::vec3 vertex4) const{
    Hit hit;
    glm::vec3 norm{ glm::normalize(glm::cross(vertex4-vertex1, vertex2-vertex1))};
    float denominator = glm::dot(norm, newRay.direction);
    if (denominator != 0) {
        float distance = (-(norm.x*(newRay.origin.x - vertex1.x)) - (norm.y*(newRay.origin.y - vertex1.y)) - (norm.z*(newRay.origin.z - vertex1.z))) / denominator;
        if (distance > 0.01) {
            glm::vec3 object_position = newRay.origin + (distance * newRay.direction);
            
            //

            hit.intersectionPoint_ = object_position;
            
            if (glm::dot(vertex4-vertex1, vertex1 - hit.intersectionPoint_) <= 0 && glm::dot(vertex1-vertex2, vertex2-hit.intersectionPoint_) <= 0 && glm::dot(vertex2 - vertex3, vertex3 - hit.intersectionPoint_) <= 0 && glm::dot(vertex3-vertex4, vertex4-hit.intersectionPoint_) <= 0) {
                hit.intersectionPoint_ = object_position;
                hit.hit_ = true;
                hit.normalVec_ = glm::vec3{object_position.x,object_position.y,object_position.z};
                hit.distance_ = distance;
            }
        }

    }
    if (hit.hit_) {
        return hit;
    }
};*/

//getter
glm::vec3 Box::getMinimum() const {
    return minimum_;
};

glm::vec3 Box::getMaximum() const {
    return maximum_;
};
