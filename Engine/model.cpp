#include "model.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void addVertex(model * m, vertex v) {
	m->vertexes.push_back(v);
}


vertex getVertex(model * m, int i) {
	vertex v = m->vertexes.at(i);
	return v;
}

int getSize(model m) {
	return m.vertexes.size();
}

void drawModel(model m) {
	vertex v1;
	vertex v2;
	vertex v3;
	for(int i = 0; i < getSize(m); i++){
		v1.x = m.vertexes.at(i).x;
		v1.y = m.vertexes.at(i).y;
		v1.z = m.vertexes.at(i).z;
		i++;
		v2.x = m.vertexes.at(i).x;
		v2.y = m.vertexes.at(i).y;
		v2.z = m.vertexes.at(i).z;
		i++;
		v3.x = m.vertexes.at(i).x;
		v3.y = m.vertexes.at(i).y;
		v3.z = m.vertexes.at(i).z;
		

		glBegin(GL_POLYGON);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(v1.x, v1.y, v1.z);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(v2.x, v2.y, v2.z);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(v3.x, v3.y, v3.z);
		glEnd();
	}
}