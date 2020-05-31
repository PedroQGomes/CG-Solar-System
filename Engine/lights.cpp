#include <GL/glew.h>
#include <malloc.h>
#include "lights.h"
#include <stdio.h>

Light newLight(GLenum i, float* pos, float* amb, float* dif, float* spec, float* sD, float sE, float sC) {
	Light tmp = (Light)malloc(sizeof(struct light));
	if (!tmp)
		return NULL;
	tmp->number = i;
	for (int i = 0; i < 4; i++) {
		tmp->position[i] = pos[i];
		tmp->ambient[i] = amb[i];
		tmp->diffuse[i] = dif[i];
		tmp->specular[i] = spec[i];
		if (i < 3)
			tmp->spotDirection[i] = sD[i];
	}
	tmp->spotExponent = sE;
	tmp->spotCut = sC;
	return tmp;
}

void drawLight(Light l) {
	if (!l)
		return;
	glClearColor(0, 0, 0, 0);
	glLightfv(l->number, GL_POSITION, l->position);
	glLightfv(l->number, GL_AMBIENT, l->ambient);
	glLightfv(l->number, GL_DIFFUSE, l->diffuse);
	glLightfv(l->number, GL_SPECULAR, l->specular);
	glLightfv(l->number, GL_SPOT_DIRECTION, l->spotDirection);
	glLightf(l->number, GL_SPOT_EXPONENT, l->spotExponent);
	glLightf(l->number, GL_SPOT_CUTOFF, l->spotCut);
}

void enableLight(Light l) {
	if (!l)
		return;
	glEnable(l->number);
}