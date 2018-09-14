#ifndef SDF_READER_HPP
#define SDF_READER_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include "scene.hpp"
#include "material.hpp"
#include "shape.hpp"
#include "Box.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include <glm/vec3.hpp>

using namespace std;

struct sdfReader{

    // read sdf file 
    //Scene readSdf(string const& fileInput);
    Scene readSdf(string const& fileInput);

    shared_ptr<Material> searchMatMap(string const& matName);
    shared_ptr<Shape> searchShapeMap(string const& shapeName);

    //member variables
    map<string,shared_ptr<Material>> matMap_;
    map<string,shared_ptr<Shape>> shapeMap_;
    string fileOutputName_;
};

bool operator<(shared_ptr<Material> const& lhs, shared_ptr<Material> const& rhs);

#endif