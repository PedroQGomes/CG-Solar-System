//
// Created by pedro on 05/03/20.
//

#include "box.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "write.h"
#include "point.h"
#include <vector>

using namespace std;


int box(float x,float y, float z, float slices, std::string file) {

    std::ofstream f;
    f.open(file);
    float x1, y1, z1, sX, sY, sZ;

    x1 = x / 2;
    z1 = z / 2;
	y1 = y / 2;

	sX = x / slices;
	sY = y / slices;
	sZ = z / slices;

	std::vector<Point> normais;
	std::vector<Point> texturas;

    printf("Writting\n");

	//Face Frontal
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - j * sX, y1 - i * sY, z1, f);
			Point norma = newPoint();
			setX(norma, 0.0f);
			setY(norma, 0.0f);
			setZ(norma, 1.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	

	//Face Lateral Direita
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1, y1 - sY*i, z1 - j * sZ, f);
			Point norma = newPoint();
			setX(norma, 1.0f);
			setY(norma, 0.0f);
			setZ(norma, 0.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	
	
	//Face Lateral Esquerda
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(-x1, y1 - sY * i, z1 - j * sZ, f);
			Point norma = newPoint();
			setX(norma, -1.0f);
			setY(norma, 0.0f);
			setZ(norma, 0.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	
	
	//Face Traseira
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - j * sX, y1 - i * sY, -z1, f);
			Point norma = newPoint();
			setX(norma, 0.0f);
			setY(norma, 0.0f);
			setZ(norma, -1.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	
	
	//Face Superior
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - i * sX, y1, z1 - j * sZ, f);
			Point norma = newPoint();
			setX(norma, 0.0f);
			setY(norma, 1.0f);
			setZ(norma, 0.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	
	//Face Inferior
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - i * sX, -y1, z1 - j * sZ, f);
			Point norma = newPoint();
			setX(norma, 0.0f);
			setY(norma, -1.0f);
			setZ(norma, 0.0f);
			normais.push_back(norma);
			Point texura = newPoint();
			setX(texura, static_cast<float>(i) / slices);
			setY(texura, static_cast<float>(j) / slices);
			texturas.push_back(texura);
		}
	}
	mkIndices(slices, f);
	writeNormalsAndTxt(normais,texturas,f);

    return 1;
}

void mkIndices(int divison, std::ofstream& f) {
	int curr = 0;
	for (int numPlanos = 0; numPlanos < 3; numPlanos++) {

		for (int i = 0; i < divison; i++) {
			for (int j = 0; j < divison; j++) {
				int A = i * (divison + 1) + j + curr;
				int B = (i + 1) * (divison + 1) + j + curr;
				int C = A + 1;
				int D = B + 1;
				writeIntToFile(A, f);
				writeIntToFile(C, f);
				writeIntToFile(B, f);

				writeIntToFile(B, f);
				writeIntToFile(C, f);
				writeIntToFile(D, f);
			}
		}
		curr += (divison + 1) * (divison + 1);
		for (int i = 0; i < divison; i++) {
			for (int j = 0; j < divison; j++) {
				int A = i * (divison + 1) + j + curr;
				int B = (i + 1) * (divison + 1) + j + curr;
				int C = A + 1;
				int D = B + 1;

				writeIntToFile(D, f);
				writeIntToFile(C, f);
				writeIntToFile(B, f);

				writeIntToFile(C, f);
				writeIntToFile(A, f);
				writeIntToFile(B, f);
			}
		}
		curr += (divison + 1) * (divison + 1);
	}
}


void writeNormalsAndTxt(std::vector<Point> normais, std::vector<Point> texturas, std::ofstream& f){
		
	for (int i = 0; i < normais.size(); i++) {
		writePointToF(getX(normais.at(i)), getY(normais.at(i)), getZ(normais.at(i)),f);

	}

	for (int i = 0; i < texturas.size(); i++) {
		write2IntToFile(getX(normais.at(i)), getY(normais.at(i)),f);

	}

	}