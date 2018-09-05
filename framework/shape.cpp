#include "shape.hpp"
#include <string>

using namespace std;

//constructors
Shape::Shape() : 
    name_{"default"},
    material_{make_shared<Material>()}, //todo: add default material,
    translateMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
    rotationMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
    scaleMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
    {};

Shape::Shape(string name, shared_ptr<Material> material) :
    name_{name},
    material_{material},
    translateMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
    rotationMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}},
    scaleMatrix_{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
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

Ray Shape::translate(glm::vec3 translationVec, Ray const& ray){
    //translateMatrix_ = {{1,0,0,translationVec.x},{0,1,0,translationVec.y},{0,0,1, translationVec.z},{0,0,0,1}};
    translateMatrix_[0][3] = translationVec.x;
    translateMatrix_[1][3] = translationVec.y;
    translateMatrix_[2][3] = translationVec.z;
    glm::vec3 newOrigin;
    newOrigin.x = ray.origin.x + translationVec.x;
    newOrigin.y = ray.origin.y + translationVec.y;
    newOrigin.z = ray.origin.z + translationVec.z;
    Ray translatedRay{};
    translatedRay.origin = newOrigin;
    return translatedRay;
}

//Ray rotate(glm::vec3 rotationVec, Ray const& ray);
//Ray scale(glm::vec3 scaleVec, Ray const& ray);

//Task 5.4
std::ostream& Shape::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "Material: \n " << *material_ << endl;
	return os;
};

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return (s.print(os));
};