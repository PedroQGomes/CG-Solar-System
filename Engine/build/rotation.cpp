#include "rotation.h"


Rotation newRotation() {

	Rotation r = (Rotation)(malloc(sizeof(struct rotation)));

	if (r) {
		r->angle = 0;
		r->o = newOperation3f();
	}

	return r;
}

void rotationSetX(Rotation r, float x) {
	if (r) setX(r->o, x);
}

void rotationSetY(Rotation r, float y) {
	if (r) setY(r->o, y);
}

void rotationSetZ(Rotation r, float z) {
	if (r) setX(r->o, z);
}

void rotationSetAngle(Rotation r, float a) {
	if (r) r->angle = a;
}

float rotationGetX(Rotation r){
	if (r){
		return getX(r->o);
	}else {
		return 0;
	}
}

float rotationGetY(Rotation r) {
	if (r){
		return getY(r->o);
	}
	else {
		return 0;
	}
}

float rotationGetZ(Rotation r) {
	if (r){
		return getZ(r->o);
	}
	else {
		return 0;
	}
}

float rotationGetAngle(Rotation r) {
	if (r){
		return r->angle;
	}else{
		return 0;
	}
}