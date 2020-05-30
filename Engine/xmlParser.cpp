#include <string>
#include <iostream>
#include <vector>
#include "xmlParser.h"
#include "tinyxml2.h"
#include "groupModel.h"
#include "parser.h"
#include "translation.h"
#include "scale.h"
#include "rotation.h"
#include "lights.h"
using namespace tinyxml2;
using namespace std;


void parseModels(XMLNode* models,GroupModel groupModel) {
    XMLElement* e = models->FirstChildElement("model");
    while(e != nullptr) {
        addModel(groupModel,parseModel(e->Attribute("file")));
        

        e = e->NextSiblingElement("model");
    }
}
void parseTranslation(XMLNode* translation,GroupModel groupModel) {
    XMLElement* e = (XMLElement*) translation;
    Translation tmp = newTranslation();
    tmp->time = e->FloatAttribute("time", 0);
    //printf("tempo %f\n", tmp->time);
    if (tmp->time == 0) {
        translationSetX(tmp, e->IntAttribute("X", 0));
        translationSetY(tmp, e->IntAttribute("Y", 0));
        translationSetZ(tmp, e->IntAttribute("Z", 0));
        setTranslation(groupModel, tmp);

    }
    else {
        for (XMLElement* g = e->FirstChildElement(); g != nullptr; g = g->NextSiblingElement()) {
            float tx, ty, tz;
            const char* type = g->Value();
            if (strcmp(type, "point") == 0) {
                tx = g->FloatAttribute("X", 0.0);
                ty = g->FloatAttribute("Y", 0.0);
                tz = g->FloatAttribute("Z", 0.0);
                Vertex v = newVertex(tx, ty, tz);
                tmp->pontos->push_back(v);

            }

        }
        translationSetX(tmp, e->IntAttribute("time", 0));
        setTranslation(groupModel, tmp);
    }



}


int parseLights(XMLNode* lights, std::vector<Light>* lightsVec) {
    XMLElement* light = lights->FirstChildElement("light");

    int currentLight = 0;
    while (light != NULL) {
        const char* type = light->Attribute("type");

        float pos[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // default is a point
        float amb[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // opengl default
        float diff[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; //opengl default
        float spec[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; // opengl default
        float spotDir[3] = { 0.0f, 0.0f, -1.0f }; // opengl default
        float spotExp = 0.0f; // opengl default, uniform light dist
        float spotCut = 180.0f; // opengl default, uniform light dist

        light->QueryAttribute("posX", pos);
        light->QueryAttribute("posY", pos + 1);
        light->QueryAttribute("posZ", pos + 2);
        // if directional, it's vector
        if (strcmp(type, "DIRECTIONAL") == 0)
            pos[3] = 0.0f;

        light->QueryAttribute("ambR", amb);
        light->QueryAttribute("ambG", amb + 1);
        light->QueryAttribute("ambB", amb + 2);

        light->QueryAttribute("diffR", diff);
        light->QueryAttribute("diffG", diff + 1);
        light->QueryAttribute("diffB", diff + 2);

        light->QueryAttribute("specR", spec);
        light->QueryAttribute("specG", spec + 1);
        light->QueryAttribute("specB", spec + 2);

        light->QueryAttribute("dX", spotDir);
        light->QueryAttribute("dY", spotDir + 1);
        light->QueryAttribute("dZ", spotDir + 2);

        light->QueryAttribute("exp", &spotExp);
        light->QueryAttribute("cut", &spotCut);

        GLenum i = GL_LIGHT0 + currentLight;
        Light l = newLight(i, pos, amb, diff, spec, spotDir, spotExp, spotCut);
        lightsVec->push_back(l);
        currentLight++;


        light = light->NextSiblingElement("light");
    }

    if (currentLight < 9)
        return 0;
    else
        return 1;


}


void parseScale(XMLNode* scale,GroupModel groupModel) {
    XMLElement* e = (XMLElement*) scale;
    Scale tmp = newScale();
    scaleSetX(tmp,e->FloatAttribute("X",0.0F));
    scaleSetY(tmp,e->FloatAttribute("Y",0.0F));
    scaleSetZ(tmp,e->FloatAttribute("Z",0.0F));
    setScale(groupModel,tmp);
}

void parseRotation(XMLNode* rotate,GroupModel groupModel) {
    XMLElement* e = (XMLElement*) rotate;
    Rotation rotation = newRotation();
    rotationSetX(rotation,e->FloatAttribute("X",0.0F));
    rotationSetY(rotation,e->FloatAttribute("Y",0.0F));
    rotationSetZ(rotation,e->FloatAttribute("Z",0.0F));
    rotationSetAngle(rotation,e->FloatAttribute("time",0.0F));
    setRotation(groupModel,rotation);
}


void parseGroups(XMLNode* group,GroupModel groupModel) {
    for(XMLNode* g = group->FirstChild(); g != nullptr ; g = g->NextSibling()) {
        const char* type = g->Value();
        if(strcmp(type,"models") == 0) {
            parseModels(g,groupModel);
        } else if(strcmp(type,"translate") == 0) {
            parseTranslation(g,groupModel);
        } else if(strcmp(type,"scale") == 0) {
            parseScale(g, groupModel);
        }else if(strcmp(type,"rotate") == 0) {
            parseRotation(g,groupModel);
        } else  if(strcmp(type,"group") == 0) {
            GroupModel tmp = newGroupModel();
            addGroup(groupModel,tmp);
            parseGroups(g,tmp);
        }

    }
}

GroupModel parseXML(std::string path, std::vector<Light>* lightsVec) {
    XMLDocument doc;
    XMLError xmlError = doc.LoadFile(path.c_str());
    cout << doc.ErrorStr() << endl;
    if (xmlError != XML_SUCCESS) {
        cout << "error" << endl;
    }
    else {
        cout << "load Successful" << endl;
    }
    XMLNode* root = doc.FirstChildElement("scene");

    if (root == nullptr) {
        cout << "no root" << endl;
    }

    XMLElement* light = root->FirstChildElement("lights");
    if (light != nullptr) {
        int erro = parseLights(light, lightsVec);
        if (erro) {
            cout << "Numero maximo de luzes excedido" << endl;
            return nullptr;
        }
    }
    XMLElement* group = root->FirstChildElement("group");
    GroupModel headGroup = newGroupModel();
    while (group != nullptr) {
        GroupModel groupModel = newGroupModel();
        addGroup(headGroup , groupModel);
        parseGroups(group, groupModel);
        group = group->NextSiblingElement("group");
    }
   
    return headGroup;
}


