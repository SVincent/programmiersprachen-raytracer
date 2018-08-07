#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "ray.hpp"
#include "material.hpp"
#include <memory>

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

    //getter
    std::string getName();
    std::shared_ptr<Material> getMaterial();

protected:
    //member variables
    std::string name_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif