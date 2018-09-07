#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include "light.hpp"
#include <vector>
#include <string>
#include <memory>

using namespace std;

struct Scene{

    // Members
    map<string,shared_ptr<Material>> materials_;
    map<string, shared_ptr<Shape>> shapes_;
    map<string,shared_ptr<Light>> lights_;
};

#endif