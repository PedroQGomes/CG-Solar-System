#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <string>
#include "point.h"

typedef struct bezier* BezierPatch;

BezierPatch initParser(std::string fileName);
int mkBezierModel(BezierPatch bp, int tessellation, std::string fileName);

#endif BEZIER_H