

#ifndef ENGINE_XMLPARSER_H
#define ENGINE_XMLPARSER_H

#include "groupModel.h"
#include "lights.h"

GroupModel parseXML(std::string path, std::vector<Light> *lightsVec);




#endif //ENGINE_XMLPARSER_H
