#include "translation.h"


Translation newTranslation() {
	Translation t = (Translation)(malloc(sizeof(struct translation)));

	if (t) {
		t->o = newOperation3f();
	}

	return t;
}

void translationSetX(Translation t, float x) {
	if (t) setX(t->o, x);
}

void translationSetY(Translation t, float y) {
	if (t) setY(t->o, y);
}

void translationSetZ(Translation t, float z) {
	if (t) setZ(t->o, z);
}

float translationGetX(Translation t) {
	if (t) {
		return getX(t->o);
	}
	else {
		return 0;
	}
}

float translationGetY(Translation t) {
	if (t) {
		return getY(t->o);
	}
	else {
		return 0;
	}
}

float translationGetZ(Translation t) {
	if (t) {
		return getZ(t->o);
	}
	else {
		return 0;
	}
}
