#include "shape.hpp"
using namespace std;

//constructors
Shape::Shape() : 
    name_{"default"},
    material_{make_shared<Material>()}, //todo: add default material
    translateMatrix_{glm::mat4(1.0)},
    rotationMatrix_{glm::mat4(1.0)},
    scaleMatrix_{glm::mat4(1.0)},
    transformationMatrix_{glm::mat4(1.0)},
    inv_transformationMatrix_{glm::mat4(1.0)}
    {};

Shape::Shape(string name, shared_ptr<Material> material) :
    name_{name},
    material_{material},
    translateMatrix_{glm::mat4(1.0)},
    rotationMatrix_{glm::mat4(1.0)},
    scaleMatrix_{glm::mat4(1.0)},
    transformationMatrix_{glm::mat4(1.0)},
    inv_transformationMatrix_{glm::mat4(1.0)}
    {}; 

//destructors
Shape::~Shape() {
    cout << "destructor class Shape\n";
};

//getter
string Shape::getName() {
    return name_;
};

shared_ptr<Material> Shape::getMaterial() {
    return material_;
};

void Shape::setMaterial(shared_ptr<Material> material){
    material_ = material;
};

void Shape::translate(glm::vec3 const& translation){
    glm::mat4 tempMatrix;
    tempMatrix [0] = glm::vec4{1.0, 0.0, 0.0, 0.0};
    tempMatrix [1] = glm::vec4{0.0, 1.0, 0.0, 0.0};
    tempMatrix [2] = glm::vec4{0.0, 0.0, 1.0, 0.0};
    tempMatrix [3] = glm::vec4{translation.x, translation.y, translation.z, 1.0};

    translateMatrix_ = tempMatrix;
    transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
    inv_transformationMatrix_ = glm::inverse(transformationMatrix_);
}

void Shape::rotate(float angle, glm::vec3 const& rotationVec){

    float angle_rad = (angle*3.1415926535897f)/180.0f;
    glm::mat4x4 R = glm::rotate(glm::mat4(1.0), angle_rad, rotationVec);
    rotationMatrix_ = R;
    transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
    inv_transformationMatrix_ = glm::inverse(transformationMatrix_);

    /*if (rotationAngles.x != 0){
        float angle = rotationAngles.x;
        glm::mat4 tempMatrix{1.0, 0.0, 0.0, 0.0,
                             0.0, cos(angle), -sin(angle), 0.0,
                             0.0, sin(angle), cos(angle), 0.0,
                             0.0, 0.0, 0.0, 1.0};
        rotationMatrix_ = tempMatrix;
        transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
        inv_transformationMatrix_ = glm::inverse(transformationMatrix_);
    }

    if (rotationAngles.y != 0){
        float angle = rotationAngles.y;
        glm::mat4 tempMatrix{cos(angle), 0.0, sin(angle), 0.0,
                             0.0, 1.0, 0.0, 0.0,
                             -sin(angle), 0.0, cos(angle), 0.0,
                             0.0, 0.0, 0.0, 1.0};
        rotationMatrix_ = tempMatrix;
        transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
        inv_transformationMatrix_ = glm::inverse(transformationMatrix_);
    }

    if (rotationAngles.z != 0){
        float angle = rotationAngles.z;
        glm::mat4 tempMatrix{cos(angle), -sin(angle), 0.0, 0.0,
                             sin(angle), cos(angle), 0.0, 0.0,
                             0.0, 0.0, 1.0, 0.0,
                             0.0, 0.0, 0.0, 1.0};
        rotationMatrix_ = tempMatrix;
        transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
        inv_transformationMatrix_ = glm::inverse(transformationMatrix_);
    }*/
}

void Shape::scale(glm::vec3 const& scales){
    glm::mat4x4 tempMatrix = glm::scale(glm::mat4(1.0),scales);
    /*
    tempMatrix [0] = glm::vec4{scales.x, 0.0, 0.0, 0.0};
    tempMatrix [1] = glm::vec4{0.0, scales.y, 0.0, 0.0};
    tempMatrix [2] = glm::vec4{0.0, 0.0, scales.z, 0.0};
    tempMatrix [3] = glm::vec4{0.0, 0.0, 0.0, 1.0};*/
    
    scaleMatrix_ = tempMatrix;
    transformationMatrix_ = translateMatrix_ * rotationMatrix_ * scaleMatrix_;
    inv_transformationMatrix_ = glm::inverse(transformationMatrix_);
}

//Task 5.4
std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "Material: \n " << *material_ << endl;
	return os;
};

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return (s.print(os));
};