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


    printf("Writting\n");

	//Face Frontal
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - j * sX, y1 - i * sY, z1, f);
		}
	}
	

	//Face Lateral Direita
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1, y1 - sY*i, z1 - j * sZ, f);
		}
	}
	
	
	//Face Lateral Esquerda
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(-x1, y1 - sY * i, z1 - j * sZ, f);
		}
	}
	
	
	//Face Traseira
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - j * sX, y1 - i * sY, -z1, f);
		}
	}
	
	
	//Face Superior
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - i * sX, y1, z1 - j * sZ, f);
		}
	}
	
	//Face Inferior
	for (int i = 0; i <= slices; i++) {
		for (int j = 0; j <= slices; j++) {
			writePointToF(x1 - i * sX, -y1, z1 - j * sZ, f);
		}
	}
	mkIndices(slices, f);
    return 1;
}

void mkIndices(int div, std::ofstream& f) {
	int curr = 0;
	for (int numPlanos = 0; numPlanos < 3; numPlanos++) {
		// Face para fora
		// D -- C
		// B -- A
		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {
				int indexA = i * (div + 1) + j + curr;
				int indexB = (i + 1) * (div + 1) + j + curr;
				int indexC = indexA + 1;
				int indexD = indexB + 1;
				writeIntToFile(indexA, f);
				writeIntToFile(indexC, f);
				writeIntToFile(indexB, f);

				writeIntToFile(indexB, f);
				writeIntToFile(indexC, f);
				writeIntToFile(indexD, f);
			}
		}
		curr += (div + 1) * (div + 1);
		for (int i = 0; i < div; i++) {
			for (int j = 0; j < div; j++) {
				int indexA = i * (div + 1) + j + curr;
				int indexB = (i + 1) * (div + 1) + j + curr;
				int indexC = indexA + 1;
				int indexD = indexB + 1;

				writeIntToFile(indexD, f);
				writeIntToFile(indexC, f);
				writeIntToFile(indexB, f);

				writeIntToFile(indexC, f);
				writeIntToFile(indexA, f);
				writeIntToFile(indexB, f);
			}
		}
		curr += (div + 1) * (div + 1);
	}
}
