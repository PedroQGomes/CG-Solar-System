#include "translation.h"
#include <GL\glut.h>
#include "catMR.h"


Translation newTranslation() {
	Translation result = (Translation)malloc(sizeof(struct translation));
	if (!result)
		return NULL;

	result->o = newOperation3f();
	result->pontos = new std::vector<Vertex>();
	result->oldY = (float*)malloc(sizeof(float) * 3);
	result->oldY[0] = 0;
	result->oldY[1] = 1;
	result->oldY[2] = 0;
	result->time = 0;
	
	return result;
}
void getCurvePoint(Translation trans, float gt, float* pos, float* deriv) {
	if (trans) {
		int objCount = trans->pontos->size();
		
		float t = gt * objCount;
		int index = static_cast<int>(floor(t));
		t = t - index;


		int indices[4];
		indices[0] = (index + objCount - 1) % objCount;
		indices[1] = (indices[0] + 1) % objCount;
		indices[2] = (indices[1] + 1) % objCount;
		indices[3] = (indices[2] + 1) % objCount;

		float p[4][3];
		for (int i = 0; i < 4; i++) {
			p[i][0] = (trans->pontos->at(indices[i]))->x;
			p[i][1] = (trans->pontos->at(indices[i]))->y;
			p[i][2] = (trans->pontos->at(indices[i]))->z;
			//printf("aqui x z %f %f\n", (trans->pontos->at(indices[i]))->x, (trans->pontos->at(indices[i]))->z);
		}
		getCMRPoint(t, p[0], p[1], p[2], p[3], pos, deriv);
	}
}

void drawTranslation(Translation t,int timestp) {
	if(t && t->pontos->size() == 0){

		glTranslatef(t->o->x, t->o->y, t->o->z);


	}else if (t) {
		float pos[3];
		float deriv[3];

		float scaledT = glutGet(GLUT_ELAPSED_TIME) / t->time;
		float tmp2 = 5.0f;
		float tmp1 = glutGet(GLUT_ELAPSED_TIME) / tmp2;

		getCurvePoint(t, scaledT, (float*)pos, (float*)deriv);
		glTranslatef(pos[0], pos[1], pos[2]);
		//printf("x %f\n", pos[0]);
		//printf("y %f\n", pos[1]);
		//printf("z %f\n", pos[2]);

		normaliza((float*)deriv);

		float z[3];
		cross((float*)deriv, t->oldY, (float*)z);
		normaliza((float*)z);

		cross((float*)z, (float*)deriv, t->oldY);
		normaliza(t->oldY);

		float rotateMatrix[4][4];
		mkMatrix((float*)deriv, t->oldY, (float*)z, (float*)rotateMatrix);

		glMultMatrixf((float*)rotateMatrix);

	}


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
