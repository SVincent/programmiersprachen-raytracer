#include "sdfreader.hpp"
#include "scene.hpp"

using namespace std;

Scene sdfReader::readSdf(string const& fileInput)
{

    Scene outputScene;

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
        while(getline(input, currentLine)){
            stringstream strStream;
            strStream << currentLine;
            strStream >> currentWord;

            if (!currentWord.compare("define")){
                if (!currentWord.compare("material")){

                    shared_ptr<Material> material;

                    string name;
                    float reflexivity;
                    Color ambientcoefficient;
                    Color diffusecoefficient;
                    Color specularcoefficient;

                    strStream >> name;
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

                    material = make_shared<Material>(name,reflexivity, ambientcoefficient,diffusecoefficient,specularcoefficient);

                    outputScene.materials_.insert(pair<string,shared_ptr<Material>>(name,material));

                    matVec.push_back(material);
                    matSet.insert(material);
                    matMap.insert(pair<string,shared_ptr<Material>>(name,material));
                }
            }
        currentLine = "";
        currentWord = "";
        }
        
    }
    return outputScene;
};


shared_ptr<Material> sdfReader::searchMatVec(string const& matName) {
    /*auto it = matVec_.begin();

    while (it != matVec_.end()) {
        if (it->getMaterialName() == matName) {
            return it;
        }
    }*/
    return nullptr;
};


shared_ptr<Material> sdfReader::searchMatSet(string const& matName) {
    set<shared_ptr<Material>>::iterator it;
    auto matSearch = make_shared<Material>(matName);
    it = matSet_.find(matSearch);
    return *it;
};

shared_ptr<Material> sdfReader::searchMatMap(string const& matName) {
    map<string,shared_ptr<Material>>::iterator it;
    it = matMap_.find(matName);
    return it->second;
};

bool operator<(shared_ptr<Material> const& lhs, shared_ptr<Material> const& rhs) {
    return (lhs->getMaterialName() < rhs->getMaterialName());
};