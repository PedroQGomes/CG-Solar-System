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
    translationSetX(tmp,e->IntAttribute("X",0));
    translationSetY(tmp,e->IntAttribute("Y",0));
    translationSetZ(tmp,e->IntAttribute("Z",0));
    setTranslation(groupModel,tmp);
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
    rotationSetAngle(rotation,e->FloatAttribute("angle",0.0F));
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

GroupModel parseXML(std::string path) {
    XMLDocument doc;
    XMLError xmlError = doc.LoadFile(path.c_str());
    cout << doc.ErrorStr() << endl ;
    if(xmlError != XML_SUCCESS) {
        cout << "error" << endl;
    } else {
        cout << "load Successful" << endl;
    }

    XMLNode* root = doc.FirstChildElement("scene");

    if (root == nullptr) {
        cout << "no root" << endl;
    }

    GroupModel groupModel = newGroupModel();
    parseGroups(root,groupModel);
    return groupModel;
}


