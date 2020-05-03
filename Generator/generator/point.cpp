#include "point.h"
#include <stdlib.h>

struct point {
    float x;
    float y;
    float z;
};

Point newPoint() {
    Point v = (Point)malloc(sizeof(struct point));
    if (!v)
        return NULL;
    v->x = 0;
    v->y = 0;
    v->z = 0;
    return v;
}

void freePoint(Point v) {
    if (v)
        free(v);
}

void setX(Point v, float x) {
    if (v)
        v->x = x;
}
void setY(Point v, float y) {
    if (v)
        v->y = y;
}
void setZ(Point v, float z) {
    if (v)
        v->z = z;
}

float getX(Point v) {
    if (v)
        return v->x;
    else
        return 1;
}

float getY(Point v) {
    if (v)
        return v->y;
    else
        return 1;
}

float getZ(Point v) {
    if (v)
        return v->z;
    else
        return 1;
}
