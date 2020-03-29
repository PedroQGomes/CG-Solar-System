#pragma once
#include "operation3f.h"

typedef struct translation{
	Operation3f o;
} *Translation;

Translation newTranslation();

void translationSetX(Translation t, float x);

void translationSetY(Translation t, float y);

void translationSetZ(Translation t, float z);

float translationGetX(Translation t);

float translationGetY(Translation t);

float translationGetZ(Translation t);