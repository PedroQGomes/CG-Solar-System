#include "scale.h"


Scale newScale() {

	Scale s = (Scale)(malloc(sizeof(struct scale)));

	if (s) {
		s->o = newOperation3f();
	}

	return s;
}


void scaleSetX(Scale s, float x) {
	if (s) setX(s->o,x);
}

void scaleSetY(Scale s, float y) {
	if (s) setY(s->o, y);
}

void scaleSetZ(Scale s, float z) {
	if (s) setZ(s->o, z);
}

float scaleGetX(Scale s) {
	if (s) {
		return getX(s->o);
	}else{
		return 0;
	}
}

float scaleGetY(Scale s) {
	if (s) {
		return getY(s->o);
	}else{
		return 0;
	}
}

float scaleGetZ(Scale s) {
	if (s) {
		return getZ(s->o);
	}else{
		return 0;
	}
}