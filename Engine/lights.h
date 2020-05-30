#pragma once
#include "operation3f.h"

typedef struct light {
	GLenum number; // number of the light
	float position[4]; // position
	float ambient[4]; // ambient component
	float diffuse[4]; // diffuse component
	float specular[4]; // specular component
	float spotDirection[3]; // direction
	float spotExponent;
	float spotCut;

}*Light;

Light newLight(GLenum i, float* pos, float* amb, float* dif, float* spec, float* sD, float sE, float sC);
void drawLight(Light l);
void enableLight(Light l);

