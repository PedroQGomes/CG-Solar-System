#pragma once
#ifndef CATMR_H
#define CATMR_H

void mkMatrix(float* x, float* y, float* z, float* m);
void cross(float* a, float* b, float* res);
void normaliza(float* a);
void getCMRPoint(float t, float* p0, float* p1, float* p2, float* p3, float* pos, float* deriv);

#endif