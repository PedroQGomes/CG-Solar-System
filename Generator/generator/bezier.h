#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <string>
#include "point.h"

typedef struct bezier* BezierPatch;

BezierPatch initParser(std::string file);
void mkBezierModel(BezierPatch bp, int tess, std::string file);


#endif BEZIER_H