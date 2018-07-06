#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "color.hpp"
#include "ray.hpp"
#include "material.hpp"
#include <memory>

class Shape {
public:
    //constructors
    Shape();
    Shape(std::string name, Color const& color);
    //Task 6.4
    Shape(std::string name, std::shared_ptr<Material> material);

    //destructors
    //Task 5.8
    virtual ~Shape();

    //functions
    virtual double area() = 0;
	virtual double volume() = 0;
    //Task 5.4
    virtual std::ostream& print(std::ostream& os) const;

    //Task 6.3
    virtual bool intersect(Ray const& ray, float& t) = 0;

    //getter
    std::string getName();
    Color getColor() const;

protected:
    //member variables
    std::string name_;
    Color color_;
    std::shared_ptr<Material> material_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif