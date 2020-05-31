#pragma once
#ifndef SHINE_H
#define SHINE_H
typedef struct shine* Shine;
Shine newShine();

void setDiffuse(Shine s, float* dif);
void setSpecular(Shine s, float* spec);
void setEmissive(Shine s, float* em);
void setAmbient(Shine s, float* am);
void setShineness(Shine s);

#endif
