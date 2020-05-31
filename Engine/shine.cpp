#include <malloc.h>
#include "shine.h"
#include <GL/glew.h>

struct shine {
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float ambient[4];
};

Shine newShine() {
	Shine s = (Shine)malloc(sizeof(struct shine));
	if (!s)
		return NULL;
	for (int i = 0; i < 4; i++) {
		if (i != 3) {
			s->diffuse[i] = 0.8f;
			s->specular[i] = 0.0f;
			s->emissive[i] = 0.0f;
			s->ambient[i] = 0.2f;
		}
		else {
			s->diffuse[i] = 1.0f;
			s->specular[i] = 1.0f;
			s->emissive[i] = 1.0f;
			s->ambient[i] = 1.0f;
		}
	}
	return s;
}

void setDiffuse(Shine s, float* dif) {
	if (!s)
		return;
	for (int i = 0; i < 3; i++)
		s->diffuse[i] = dif[i];
}

void setSpecular(Shine s, float* spec) {
	if (!s)
		return;
	for (int i = 0; i < 3; i++)
		s->specular[i] = spec[i];
}

void setEmissive(Shine s, float* em) {
	if (!s)
		return;
	for (int i = 0; i < 3; i++)
		s->emissive[i] = em[i];
}

void setAmbient(Shine s, float* am) {
	if (!s)
		return;
	for (int i = 0; i < 3; i++)
		s->ambient[i] = am[i];
}

void setShineness(Shine s) {
	glMaterialfv(GL_FRONT, GL_DIFFUSE, s->diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, s->specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, s->emissive);
	glMaterialfv(GL_FRONT, GL_AMBIENT, s->ambient);
}