#include "sdfreader.hpp"
#include "scene.hpp"
#include "material.hpp"

using namespace std;

Scene sdfReader::readSdf(string const& fileInput)
{
    Scene outputScene{};

    //vector<shared_ptr<Material>> matVec;
    //set<shared_ptr<Material>> matSet;
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
                    outputScene.materials_.insert(outputScene.materials_.end(),material);

                    //matVec.push_back(material);
                    //matSet.insert(material);
                    matMap_[materialName] = material;
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

                        box = make_shared<Box>(minVec,maxVec,boxName,boxMaterial);
                        outputScene.shapes_.insert(outputScene.shapes_.end(),box);
                        shapeMap_[boxName] = box;
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
                        outputScene.shapes_.insert(outputScene.shapes_.end(),sphere);
                        shapeMap_[sphereName] = sphere;
                        cout << "Added sphere: " << sphereName << " to the scene." << endl;
                    }
                }
                if (!currentWord.compare("light")){
                    cout << "initializing new light." << endl;
                    shared_ptr<Light> light;

                    string lightName;
                    float brightness;
                    Color lightColor;
                    float x_value_position;
                    float y_value_position;
                    float z_value_position;

                    strStream >> lightName;

                    strStream >> x_value_position;
                    strStream >> y_value_position;
                    strStream >> z_value_position;

                    glm::vec3 positionVec ={x_value_position,y_value_position,z_value_position};

                    strStream >> lightColor.r;
                    strStream >> lightColor.g;
                    strStream >> lightColor.b;

                    strStream >> brightness;

                    light = make_shared<Light>(lightName, positionVec, lightColor, brightness);
                    outputScene.lights_.insert(outputScene.lights_.end(), light);
                    cout << "Added light: " << lightName << " to the scene." << endl;
                }
                if (!currentWord.compare("camera")){
                    cout << "initializing new camera." << endl;
                    camera cam;

                    string cameraName;
                    float fov;
                    glm::vec3 eye;
                    glm::vec3 dir;
                    glm::vec3 up;

                    strStream >> cameraName;

                    strStream >> fov;

                    strStream >> eye.x;
                    strStream >> eye.y;
                    strStream >> eye.z;

                    strStream >> dir.x;
                    strStream >> dir.y;
                    strStream >> dir.z;

                    strStream >> up.x;
                    strStream >> up.y;
                    strStream >> up.z;                

                    cam.name_ = cameraName;
                    cam.fov_ = fov;
                    cam.origin_= eye;
                    cam.direction_=glm::normalize(dir);
                    cam.upVec_ = glm::normalize(up);

                    outputScene.mainCam_=cam;
                    cout << "Added camera: " << cameraName << " to the scene." << endl;
                }
                if (!currentWord.compare("ambient")){
                    cout << "initializing new ambient color." << endl;
                    Color ambientCol;

                    strStream >> ambientCol.r;
                    strStream >> ambientCol.g;
                    strStream >> ambientCol.b;

                    outputScene.ambientLightCol_= ambientCol;
                }
            }

            if(!currentWord.compare("render")){

                cout << "Initializing renderer" << endl;
                string cameraName;
                string fileName;
                unsigned int x_res;
                unsigned int y_res;

                strStream >> cameraName;
                strStream >> x_res;
                strStream >> y_res;

                outputScene.mainCam_.xres_=x_res;
                outputScene.mainCam_.yres_=y_res;

                strStream >> fileName;
                fileOutputName_ = fileName;
            }

            if (!currentWord.compare("transform")){
                cout << "transformation input" << endl;
                
                string shapeName;
                string transformMethod;
                glm::vec3 parameter;

                strStream >> shapeName;
                strStream >> transformMethod;

                strStream >> parameter.x;
                strStream >> parameter.y;
                strStream >> parameter.z;

                auto shape = searchShapeMap(shapeName);
                if (shape != nullptr){
                    if(transformMethod == "translate"){
                        shape->translate(parameter);
                    }
                    else if (transformMethod == "rotate"){
                        float angle;
                        strStream >> angle;
                        shape->rotate(angle, parameter);
                        cout << "rotating about " << angle << endl;
                    }
                    else if (transformMethod == "scale"){
                        shape->scale(parameter);
                    }
                    else {
                        cout << "No valid transformation method entered." << endl;
                    }
                }
            }
        currentLine = "";
        currentWord = "";
        }
        
    }
    return outputScene;
};

shared_ptr<Material> sdfReader::searchMatMap(string const& matName) {
    map<string,shared_ptr<Material>>::iterator it;
    it = matMap_.find(matName);
    return it->second;
};

shared_ptr<Shape> sdfReader::searchShapeMap(string const& shapeName) {
    map<string,shared_ptr<Shape>>::iterator it;
    it = shapeMap_.find(shapeName);
    return it->second;
};


bool operator<(shared_ptr<Material> const& lhs, shared_ptr<Material> const& rhs) {
    return (lhs->getMaterialName() < rhs->getMaterialName());
};