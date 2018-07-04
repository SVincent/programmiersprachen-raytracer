#include "material.hpp";

using namespace std;

//constructors
Material::Material() : 
    name_("default material"),
    reflexivity_(1.0f),
    ambientcoefficient_(0.5f,0.5f,0.5f),
    diffusecoefficient_(0.5f,0.5f,0.5f),
    specularcoefficient_(0.5f,0.5f,0.5f)
    {};

Material::Material(string name, float m) :
    name_(name),
    reflexivity_(m),
    ambientcoefficient_(0.5f,0.5f,0.5f),
    diffusecoefficient_(0.5f,0.5f,0.5f),
    specularcoefficient_(0.5f,0.5f,0.5f)
    {};

Material::Material(string name, float m, Color ka, Color kd, Color ks) :
    name_(name),
    reflexivity_(m),
    ambientcoefficient_(ka),
    diffusecoefficient_(kd),
    specularcoefficient_(ks)
    {};

//methods

std::ostream& Material::print(std::ostream& os) const {
	os << "Name: " << name_ << endl;
    os << "reflexivity: " << reflexivity_ << endl;
    os << "ambient coefficient: " << ambientcoefficient_ <<  endl;
    os << "ambient coefficient: " << diffusecoefficient_ <<  endl;
    os << "ambient coefficient: " << specularcoefficient_ <<  endl;
	return os;
};

std::ostream& operator<<(std::ostream& os, Material const& m) {
    return (m.print(os));
};