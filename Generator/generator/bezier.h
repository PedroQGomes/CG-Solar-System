#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "point.h"


int bezierParser(char* fileName, std::vector<Point>* controlPoints, std::vector<int>* indices);

int mkBezier(std::vector<Point>* controlPoints, std::vector<int>* indices, int tessellation, char* fileName);

#endif BEZIER_H