#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "point.h"


int parseBezierPatch(char* fileName, std::vector<Point>* controlPoints, std::vector<int>* indices);

int generateBezierModel(std::vector<Point>* controlPoints, std::vector<int>* indices, int tessellation, char* fileName);

#endif BEZIER_H