#include "sdfreader.hpp"
#include "scene.hpp"
#include "material.hpp"

using namespace std;

Scene sdfReader::readSdf(string const& fileInput)
{
    Scene outputScene{};

    vector<shared_ptr<Material>> matVec;
    set<shared_ptr<Material>> matSet;
    map<string,shared_ptr<Material>> matMap;

    string currentLine;
    string currentWord;

    fstream input;
    input.open(fileInput);

    if (!(input.is_open())){
        cout << "Error locating input file" << endl;
    }

    else {
        cout << "Located input file." << endl;
        while(getline(input, currentLine)){
            stringstream strStream;
            strStream << currentLine;
            strStream >> currentWord;
            if (!currentWord.compare("define")){
                strStream >>currentWord;
                if (!currentWord.compare("material")){
                    cout << "initializing new material." << endl;
                    shared_ptr<Material> material;

                    string materialName;
                    float reflexivity;
                    Color ambientcoefficient;
                    Color diffusecoefficient;
                    Color specularcoefficient;

                    strStream >> materialName;
                    strStream >> ambientcoefficient.r;
                    strStream >> ambientcoefficient.g;
                    strStream >> ambientcoefficient.b;

                    strStream >> diffusecoefficient.r;
                    strStream >> diffusecoefficient.g;
                    strStream >> diffusecoefficient.b;

                    strStream >> specularcoefficient.r;
                    strStream >> specularcoefficient.g;
                    strStream >> specularcoefficient.b;

                    strStream >> reflexivity;

                    material = make_shared<Material>(materialName,reflexivity, ambientcoefficient,diffusecoefficient,specularcoefficient);
                    outputScene.materials_.insert(outputScene.materials_.begin(),material);

                    //matVec.push_back(material);
                    //matSet.insert(material);
                    //matMap_[materialName] = material;
                    matMap_.insert(pair<string,shared_ptr<Material>>(materialName,material));
                    cout << "Added material: " << materialName << " to the scene." << endl;
                }
                if(!currentWord.compare("shape")){ 
                    cout << endl << "initializing new shape." << endl;
                    strStream >> currentWord;   
                    if (!currentWord.compare("box")){
                        cout << "initializing a new box." << endl;
                        shared_ptr<Box> box;

                        string boxName;

                        float x_value_min;
                        float y_value_min;
                        float z_value_min;

                        float x_value_max;
                        float y_value_max;
                        float z_value_max;

                        string materialName;

                        strStream >> boxName;

                        strStream >> x_value_min;
                        strStream >> y_value_min;
                        strStream >> z_value_min;
                        glm::vec3 minVec= {x_value_min,y_value_min, z_value_min};

                        strStream >> x_value_max;
                        strStream >> y_value_max;
                        strStream >> z_value_max;
                        glm::vec3 maxVec= {x_value_max,y_value_max, z_value_max};

                        strStream >> materialName;
                        shared_ptr<Material> boxMaterial = this->searchMatMap(materialName);
                       //boxMaterial->getMaterialName();

                        box = make_shared<Box>(minVec,maxVec,boxName,boxMaterial);
                        outputScene.shapes_.insert(outputScene.shapes_.begin(),box);
                        cout << "Added box: " << boxName << " to the scene." << endl;
                    }
                    if (!currentWord.compare("sphere")){
                        cout << "initializing a new sphere." << endl;
                        shared_ptr<Sphere> sphere;
                        
                        string sphereName;

                        float x_value_center;
                        float y_value_center;
                        float z_value_center;

                        float radius_value;
                        
                        string materialName;

                        strStream >> sphereName;
                        
                        strStream >> x_value_center;
                        strStream >> y_value_center;
                        strStream >> z_value_center;
                        glm::vec3 centerVec ={x_value_center,y_value_center,z_value_center};

                        strStream >> radius_value;

                        strStream >> materialName;
                        shared_ptr<Material> sphereMaterial = this->searchMatMap(materialName);

                        sphere = make_shared<Sphere>(centerVec, radius_value, sphereName, sphereMaterial);
                        outputScene.shapes_.insert(outputScene.shapes_.begin(),sphere);
                        cout << "Added sphere: " << sphereName << " to the scene." << endl;
                    }
                }
            }
        currentLine = "";
        currentWord = "";
        }
        
    }
    return outputScene;
};

/*
shared_ptr<Material> sdfReader::searchMatVec(string const& matName) {
    auto it = matVec_.begin();

    while (it != matVec_.end()) {
        if (it->getMaterialName() == matName) {
            return it;
        }
    } 
    return nullptr;
};

/*
shared_ptr<Material> sdfReader::searchMatSet(string const& matName) {
    set<shared_ptr<Material>>::iterator it;
    auto matSearch = make_shared<Material>(matName);
    it = matSet_.find(matSearch);
    return *it;
};
*/
shared_ptr<Material> sdfReader::searchMatMap(string const& matName) {
    map<string,shared_ptr<Material>>::iterator it;
    it = matMap_.find(matName);
    return it->second;
};

bool operator<(shared_ptr<Material> const& lhs, shared_ptr<Material> const& rhs) {
    return (lhs->getMaterialName() < rhs->getMaterialName());
};