#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Scene{

    // Constructors 
    //Scene();

    // Members
    vector<shared_ptr<Material>> materials_;
    vector<shared_ptr<Shape>> shapes_;
};

#endif