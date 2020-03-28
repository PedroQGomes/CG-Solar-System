#pragma once


typedef struct operation3f {
	float x;
	float y;
	float z;
} * Operation3f;


void setX(Operation3f o, float x);

void setY(Operation3f o, float y);

void setZ(Operation3f o, float z);

float getX(Operation3f o);

float getY(Operation3f o);

float getZ(Operation3f o);