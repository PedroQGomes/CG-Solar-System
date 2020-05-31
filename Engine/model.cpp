#include<stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include "model.h"
#include <cstdio>
#include <IL/il.h>

int color = 0;
std::string sun = "../../Texturas/2k_sun.jpg";

struct modelStruct {
	std::vector<float> * vertices;
	std::vector<unsigned int> *indices;
	GLuint vBuff[1];
	GLuint iBuff[1];
	//new stuff
	std::vector<float> * normais;
	std::vector<float> * texturas;
	GLuint txtBuffer[1];
	GLuint nBuffer[1];
	GLuint textura;
	std::string* textureName;

} ;


Model newModel() {
	Model model = (Model)malloc(sizeof(struct modelStruct));
	if (!model)
		return NULL;
	model->vertices = new std::vector<float>();
	model->indices = new std::vector<unsigned int>();
	model->texturas = new std::vector<float>();
	model->normais = new std::vector<float>();
	
	return model;
}

void setVertices(Model model, std::vector<float>* ver) {
	if (model)
		model -> vertices = ver;
}

void setIndices(Model model, std::vector<unsigned int>* index) {
	if (model)
		model->indices = index;
}

void setNormais(Model model, std::vector<float>* n) {
	if (model)
		model->normais = n;
}
void setTextureCoords(Model model, std::vector<float>* textCord) {
	if (model)
		model->texturas = textCord;
}

int getIndex(Model m, int i) {
	if (m)
		return m->indices->at(i);
	else
		return -1;
}

int getNumIndexes(Model m) {
	if (m)
		return (int)m->indices->size();
	else
		return 0;
}

void freeModel(Model model) {
	if (model) {
		model->vertices->clear();
		model->indices->clear();
		model->texturas->clear();
		model->normais->clear();
		free(model);
	}
}



void addVertices(Model model, float v) {
	if (model) {
		model->vertices->push_back(v);
	}
}

void addIndice(Model model, unsigned int i) {
	if (model) {
		model->indices->push_back(i);
	}
}

void addTexture(Model model, float x) {
	if (model) {
		model->texturas->push_back(x);
	}
}

void addNormal(Model model, float x) {
	if (model) {
		model->normais->push_back(x);
	}
}


std::vector<float>* getVertices(Model model) {
	if (model)
		return model->vertices;
	else
		return nullptr;
}

std::vector<unsigned int>* getIndices(Model model) {
	if (model)
		return model->indices;
	else
		return NULL;
}

std::vector<float>* getNormais(Model model) {
	if (model)
		return model->normais;
	else
		return NULL;
}

std::vector<float>* getTextureCoords(Model model) {
	if (model)
		return model->texturas;
	else
		return NULL;
}


float getVertice(Model model, int i) {
	float v = (*(model->vertices)).at(i);
	return v;
}

int getSize(Model model) {
	return (*(model->vertices)).size();
}

void drawModel(Model m) {
	if (m) {
		
		//glcolor3f(0.0,0.0,0.0);
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		GLenum error = glGetError();
		if (GL_NO_ERROR != error) {
			fprintf(stderr, "Error: %s\n", glewGetErrorString(error));
		} 
		glVertexPointer(3, GL_FLOAT, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, m->nBuffer[0]);
		glNormalPointer(GL_FLOAT, 0, 0);

		if ((*(m->texturas)).size() > 0) {
			glBindBuffer(GL_ARRAY_BUFFER, m->txtBuffer[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, 0);
			glBindTexture(GL_TEXTURE_2D, m->textura);
		}



		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glDrawElements(GL_TRIANGLES, (*m->indices).size(), GL_UNSIGNED_INT, NULL);
	

		if ((*m->texturas).size() > 0) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		
	} 
	
}

void fillBuffers(Model m) {

	if (m) {		
		std::vector<float> vertexes = *m->vertices;
		std::vector<unsigned int> indexes = *m->indices;
		std::vector<float> normais = *m->normais;
		std::vector<float> texturas = *m->texturas;


		float* vertex = vertexes.data();
		unsigned int* index = indexes.data();
		float* normal = normais.data();
		float* textura = texturas.data();

		//printf("lol %f\n", vertexes.at(1));
		glGenBuffers(1, m->vBuff);
		glBindBuffer(GL_ARRAY_BUFFER, m->vBuff[0]);
		glBufferData(GL_ARRAY_BUFFER, (*m->vertices).size() * sizeof(float), vertex, GL_STATIC_DRAW);


		glGenBuffers(1, m->iBuff);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m->iBuff[0]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*m->indices).size() * sizeof(unsigned int), index, GL_STATIC_DRAW);
		
		
		glGenBuffers(1, m->nBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m->nBuffer[0]);
		glBufferData(GL_ARRAY_BUFFER, (*m->normais).size() * sizeof(float), normal, GL_STATIC_DRAW);

		if ((*m->texturas).size() > 0) {
			glGenBuffers(1, m->txtBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, m->txtBuffer[0]);
			glBufferData(GL_ARRAY_BUFFER, (*m->texturas).size() * sizeof(float), textura, GL_STATIC_DRAW);
		}

	}

}


void setTexture(Model m, std::string texture) {
	if (m) {
		m->textureName = new std::string(std::move(texture));
	}
}

std::string getName(Model m) {
	if (m)
		return *(m->textureName);
	else
		return NULL;
}


void textureModel(Model m) {

	if (m && (*m->texturas).size() > 0) {
		unsigned int t, tw, th;
		unsigned char* texData;
		

		ilInit();
		ilEnable(IL_ORIGIN_SET);
		ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
		ilGenImages(1, &t);
		ilBindImage(t);
		//printf("%s\n", m->textureName->c_str());
		ilLoadImage((ILstring) m->textureName->c_str());
		tw = ilGetInteger(IL_IMAGE_WIDTH);
		th = ilGetInteger(IL_IMAGE_HEIGHT);
		ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		texData = ilGetData();

		glGenTextures(1, &m->textura);

		glBindTexture(GL_TEXTURE_2D, m->textura);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		
	}

}


