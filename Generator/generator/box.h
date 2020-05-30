//
// Created by pedro on 05/03/20.
//



#include <string>
#include "point.h"
#include <vector>

int box(float x, float y, float z,float slices, std::string file);
void mkIndices(int div, std::ofstream& f);
void writeNormalsAndTxt(std::vector<Point> normais, std::vector<Point> texturas, std::ofstream& f);


