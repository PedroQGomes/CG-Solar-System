#ifndef POINT_H
#define POINT_H


typedef struct point* Point;


Point newPoint();

void freePoint(Point v);

void setX(Point v, float x);

void setY(Point v, float y);

void setZ(Point v, float z);

float getX(Point v);

float getY(Point v);

float getZ(Point v);



#endif