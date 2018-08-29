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
#include <glm/vec3.hpp>

using namespace std;

struct sdfReader{
    // Constructor
    //sdfReader();

    // read sdf file 
    Scene readSdf(string const& fileInput);

    //shared_ptr<Material> searchMatVec(string const& matName);
    //shared_ptr<Material> searchMatSet(string const& matName);
    shared_ptr<Material> searchMatMap(string const& matName);

    //member variables
    vector<shared_ptr<Material>> matVec_;
    set<shared_ptr<Material>> matSet_;
    map<string,shared_ptr<Material>> matMap_;
};

bool operator<(shared_ptr<Material> const& lhs, shared_ptr<Material> const& rhs);

#endif