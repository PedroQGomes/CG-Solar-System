

#include <string>
#include <iostream>
#include <vector>
#include "xmlParser.h"
#include "tinyxml2.h"
using namespace tinyxml2;
using namespace std;

vector<string> parseXML(std::string path) {
    vector<string> tmp;
    printf("%s\n",path.c_str());
    XMLDocument doc;
    XMLError xmlError = doc.LoadFile("teste.xml");
    if(xmlError != XML_SUCCESS) {
        cout << "error" << endl;
        return tmp;
    }
    XMLElement* root = doc.FirstChildElement("scene");



    if (root == nullptr) {
        cout << "no root" << endl;
        return tmp;
    }
    for(XMLElement* element = root->FirstChildElement("model"); element != nullptr; element = element->NextSiblingElement("model")) {
        XMLAttribute * att = const_cast<XMLAttribute *>(element->FirstAttribute());
        tmp.push_back(att->Value());
    }
    return tmp;

}
