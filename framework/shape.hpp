#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include "ray.hpp"
#include "material.hpp"
#include "Hit.hpp"
#include <memory>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

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
    virtual Hit intersect(Ray const& ray) = 0;

    void translate(glm::vec3 const& translation);
    void rotate(float angle, glm::vec3 const& rotationVec);
    void scale(glm::vec3 const& scales);
    
    //getter
    std::string getName();
    std::shared_ptr<Material> getMaterial();

    //setter
    void setMaterial(std::shared_ptr<Material> material);

protected:
    //member variables
    std::string name_;
    std::shared_ptr<Material> material_;

    glm::mat4 translateMatrix_;
    glm::mat4 rotationMatrix_;
    glm::mat4 scaleMatrix_;

    glm::mat4 transformationMatrix_;
    glm::mat4 inv_transformationMatrix_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif