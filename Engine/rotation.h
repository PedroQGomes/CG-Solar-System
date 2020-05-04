#pragma once
#include "operation3f.h"
#include <GL/glut.h>

typedef struct rotation {
	float angle;
	Operation3f o;
}*Rotation;


Rotation newRotation();

void rotationSetX(Rotation r, float x);

void rotationSetY(Rotation r, float y);

void rotationSetZ(Rotation r, float z);

void rotationSetAngle(Rotation r, float a);

float rotationGetX(Rotation r);

float rotationGetY(Rotation r);

float rotationGetZ(Rotation r);

float rotationGetAngle(Rotation r);

void drawRotation(Rotation r,int time);
