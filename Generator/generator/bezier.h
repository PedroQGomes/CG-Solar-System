#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include <string>
#include "point.h"


int bezierParser(std::string fileName, std::vector<Point>* controlPoints, std::vector<int>* indices);

int mkBezier(std::vector<Point>* controlPoints, std::vector<int>* indices, int tessellation, std::string file);

#endif BEZIER_H