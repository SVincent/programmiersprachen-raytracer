#include "material.hpp"
#include <string>

using namespace std;

//constructors
Material::Material() :
    name_{"default material"},
    reflexivity_{1.0f},
    ambientcoefficient_{Color{0.5f,0.5f,0.5f}},
    diffusecoefficient_{Color{0.5f,0.5f,0.5f}},
    specularcoefficient_{Color{0.5f,0.5f,0.5f}} 
    {};

Material::Material(string name) :
    name_{name}
    {};

Material::Material(string name, float m) :
    name_{name},
    reflexivity_{m},
    ambientcoefficient_{Color{0.5f,0.5f,0.5f}},
    diffusecoefficient_{Color{0.5f,0.5f,0.5f}},
    specularcoefficient_{Color{0.5f,0.5f,0.5f}}
    {};

Material::Material(string name, float m, Color ka, Color kd, Color ks) :
    name_(name),
    reflexivity_(m),
    ambientcoefficient_(ka),
    diffusecoefficient_(kd),
    specularcoefficient_(ks)
    {};

//methods

std::string Material::getMaterialName(){
    return name_;
};

Color Material::getColor(){
    return Color(ambientcoefficient_);
};

Color Material::getDiffusec(){
    return Color(diffusecoefficient_);
};

Color Material::getSpecularc(){
    return Color(specularcoefficient_);
};



std::ostream& Material::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "reflexivity: " << reflexivity_ << endl;
    os << "ambient coefficient: " << ambientcoefficient_ <<  endl;
    os << "diffuse coefficient: " << diffusecoefficient_ <<  endl;
    os << "specular coefficient: " << specularcoefficient_ <<  endl;
	return os;
};

std::ostream& operator<<(std::ostream& os, Material const& m) {
    return (m.print(os));
};