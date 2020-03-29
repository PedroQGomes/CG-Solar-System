#include <stdlib.h>
#include "operation3f.h"

Operation3f newOperation3f() {
	Operation3f o = (Operation3f)(malloc(sizeof(struct operation3f)));

	if(o) {
		o->x = 0;
		o->y = 0;
		o->z = 0;
	}

	return o;
}

void setX(Operation3f o, float x) {
	if(o) o->x = x;
}

void setY(Operation3f o, float y) {
	if(o) o->y = y;
}

void setZ(Operation3f o, float z) {
	if(o) o->z = z;
}

float getX(Operation3f o) {
	if(o){
		return o->x;
	}else{
		return 0;
	}
}

float getY(Operation3f o) {
	if(o) {
		return o->y;
	}
	else {
		return 0;
	}
}

float getZ(Operation3f o) {
	if(o){
		return o->z;
	}else{
		return 0;
	}
}