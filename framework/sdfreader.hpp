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

using namespace std;

struct sdfReader{
    // Constructor
    sdfReader();

    // read sdf file 
    static Scene readSdf(string const& fileInput);

    static shared_ptr<Material> searchMatVec(string const& matName);
    static shared_ptr<Material> searchMatSet(string const& matName);
    static shared_ptr<Material> searchMatMap(string const& matName);

    static vector<shared_ptr<Material>> matVec_;
    static set<shared_ptr<Material>> matSet_;
    static map<string,shared_ptr<Material>> matMap_;
};

#endif