#include<stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "model.h"
#include <cstdio>

int color = 0;

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
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glcolor3f(0.0,0.0,0.0);
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		GLenum error = glGetError();
		if (GL_NO_ERROR != error) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		} 
		glVertexPointer(3, GL_FLOAT, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m->nBuffer[0]);
		glNormalPointer(GL_FLOAT, 0, 0);

		if (m->texturas.size() > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, m->txtBuffer[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			glBindTexture(GL_TEXTURE_2D, m->textura);
		}



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glDrawElements(GL_TRIANGLES, m->indices.size(), GL_UNSIGNED_INT, NULL);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		if (m->texturas.size() > 0) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	} 
	
}

void fillBuffers(model *m) {

	if (m) {		
		std::vector<float> vertexes = m->vertexes;
		std::vector<unsigned int> indexes = m->indices;
		std::vector<float> normais = m->normais;
		std::vector<float> texturas = m->texturas;


		float* vertex = &vertexes[0];
		unsigned int* index = &indexes[0];
		float* normal = &normais[0];
		float* textura = &texturas[0];

		//printf("lol %f\n", vertexes.at(1));
		glGenBuffers(1, m->vBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		glBufferData(GL_ARRAY_BUFFER, m->vertexes.size() * sizeof(float), vertex, GL_STATIC_DRAW);


		glGenBuffers(1, m->iBuff);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m->indices.size() * sizeof(unsigned int), index, GL_STATIC_DRAW);
		
		
		glGenBuffers(1, m->nBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m->nBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, m->normais.size() * sizeof(float), normal, GL_STATIC_DRAW);

		if (m->texturas.size() > 0) {
			glGenBuffers(1, m->txtBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m->txtBuffer[0]);
			glBufferData(GL_ARRAY_BUFFER, m->texturas.size() * sizeof(float), textura, GL_STATIC_DRAW);
		}

	}

}



void loadTexture(Model* m) {
	if (m && m->texturas.size() > 0) {
		unsigned int t, tw, th;
		unsigned char* texData;
		/*
		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		ilGenImages(1, &t);
		ilBindImage(t);
		ilLoadImage((ILstring)m->texture->c_str());
		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1, &m->textureID);

		glBindTexture(GL_TEXTURE_2D, m->textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		*/
	}

}


