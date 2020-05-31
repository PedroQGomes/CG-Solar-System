#pragma once
#include "headers.h"
#include "vertex.h"


typedef struct modelStruct* Model;




Model newModel();


void addVertices(Model m, float v);


void addIndice(Model m, unsigned int i);

void addNormal(Model m, float x);

void addTexture(Model m, float x);



int getIndex(Model m, int i);

std::string getName(Model m);


int getSize(Model m);


int getNumIndexes(Model m);


void freeModel(Model m);

std::vector<unsigned int>* getIndices(Model m);

std::vector<float>* getVertices(Model m);

std::vector<float>* getNormais(Model m);

std::vector<float>* getTextureCoords(Model m);

float getVertice(Model model, int i);

void fillBuffers(Model m);
void setIndices(Model m, std::vector<unsigned int>* in);
void setVertices(Model m, std::vector<float>* ver);
void setNormais(Model m, std::vector<float>* n);
void setTextureCoords(Model m, std::vector<float>* v);
void setTexture(Model m, std::string texture);
void textureModel(Model m);
void drawModel(Model m);
void setAmbient(Model m, float* am);
void setEmissive(Model m, float* em);
void setSpecular(Model m, float* spec);
void setDiffuse(Model m, float* dif);
