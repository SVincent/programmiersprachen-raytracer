#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"

struct Material {

public:
    //constructors
    Material();
    Material(std::string name);
    Material(std::string name, float specular);
    Material(std::string name, float specular, Color ka, Color kd, Color ks);

    //methods
    std::ostream& print(std::ostream& os) const;

    std::string getMaterialName();
    Color getColor();
    Color getDiffusec();
    Color getSpecularc();

    //member variables
    std::string name_;
    float reflexivity_;
    Color ambientcoefficient_;
    Color diffusecoefficient_;
    Color specularcoefficient_;
};

std::ostream& operator<<(std::ostream& os, Material const& m);

#endif