#ifndef SCENE_HPP
#define SCENE_HPP

#include "material.hpp"
#include "shape.hpp"
#include "color.hpp"
#include "light.hpp"
#include "camera.hpp"
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
    vector<shared_ptr<Light>> lights_;
    Color ambientLightCol_;
    camera mainCam_;
};

#endif