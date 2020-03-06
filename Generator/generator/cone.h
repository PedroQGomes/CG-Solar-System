#pragma once

#include "write.h"
#include "common.h"

int cone(float radius, float height, int slices, int stacks, std::string file);

int coneBottomCircle(float radius, int slices, std::string file);

int coneUpperBody(float radius, float height, int slices, int stacks, std::string file);