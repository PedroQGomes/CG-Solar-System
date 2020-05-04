#include<stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "model.h"
#include <cstdio>



void addVertex(model * m, float f) {
	m->vertexes.push_back(f);
}


float getVertex(model * m, int i) {
	float v = m->vertexes.at(i);
	return v;
}

int getSize(model m) {
	return m.vertexes.size();
}

void drawModel(model * m) {
	if (m) {
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		GLenum error = glGetError();
		glVertexPointer(3, GL_FLOAT, 0, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, NULL);
		if (GL_NO_ERROR != error) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		}
	}
	
}

void fillBuffers(model *m) {

	if (m) {		
		std::vector<float> vertexes = m->vertexes;
		std::vector<unsigned int> indexes = m->indices;
		float* vertex = &vertexes[0];
		unsigned int* index = &indexes[0];
		//printf("lol %u\n", indexes.at(1));
		glGenBuffers(1, m->vBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		glBufferData(GL_ARRAY_BUFFER, m->vertexes.size() * sizeof(float), vertex, GL_STATIC_DRAW);


		glGenBuffers(1, m->iBuff);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indices.size() * sizeof(unsigned int), index, GL_STATIC_DRAW);
		
	}



}


