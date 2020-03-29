#pragma once
#include "operation3f.h"

typedef struct scale {
	Operation3f o;
}*Scale;

Scale newScale();

void scaleSetX(Scale s, float x);

void scaleSetY(Scale s, float y);

void scaleSetZ(Scale s, float z);

float scaleGetX(Scale s);

float scaleGetY(Scale s);

float scaleGetZ(Scale s);