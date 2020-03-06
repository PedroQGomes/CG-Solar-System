#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "write.h"

const double PI = 3.14159265358979323846;

int cone(float radius, float height, int slices, int stacks, std::string file);

int coneBottomCircle(float radius, int slices, std::string file);

int coneUpperBody(float radius, float height, int slices, int stacks, std::string file);