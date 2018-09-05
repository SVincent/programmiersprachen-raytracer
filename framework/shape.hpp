#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "ray.hpp"
#include "material.hpp"
#include <memory>
#include <glm/vec3.hpp>

class Shape {
public:
    //constructors
    Shape();
    Shape(std::string name, std::shared_ptr<Material> material);

    //destructors
    virtual ~Shape();

    //functions
    virtual double area() = 0;
	virtual double volume() = 0;
    virtual std::ostream& print(std::ostream& os) const;
    virtual bool intersect(Ray const& ray, float& t) = 0;
    Ray translate(glm::vec3 translationVec, Ray const& ray );
    Ray rotate(glm::vec3 rotationVec, Ray const& ray);
    Ray scale(glm::vec3 scaleVec, Ray const& ray);

    //getter
    std::string getName();
    std::shared_ptr<Material> getMaterial();

protected:
    //member variables
    std::string name_;
    std::shared_ptr<Material> material_;
    float translateMatrix_[4][4];
    float rotationMatrix_[4][4];
    float scaleMatrix_[4][4];
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif