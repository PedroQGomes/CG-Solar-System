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
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			writeVertexToF(x1, i*sY -y1 , z1 - (sZ*j), f);
			writeVertexToF(x1, i*sY - y1, z1 - (sZ*(j+1)), f);
			writeVertexToF(x1, (i + 1)*sY - y1, z1 - (sZ*(j + 1)), f);

			
			writeVertexToF(x1, (i + 1)*sY - y1, z1 - (sZ*(j + 1)), f);
			writeVertexToF(x1, (i + 1)*sY - y1, z1 - (sZ*j), f);
			writeVertexToF(x1, i*sY - y1, z1 - (sZ*j), f);
		}
	}
	

	//Face Lateral Direita
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			writeVertexToF(x1 - sX * j, i*sY - y1, -z1, f);
			writeVertexToF(x1 - sX * (j + 1), i*sY - y1, -z1, f);
			writeVertexToF(x1 - sX * (j + 1), (i + 1)*sY - y1, -z1, f);

			writeVertexToF(x1 - sX * (j + 1), (i + 1)*sY - y1, -z1, f);
			writeVertexToF(x1 - sX * j, (i + 1)*sY - y1, -z1, f);
			writeVertexToF(x1 - sX * j, i*sY - y1, -z1, f);
		}
	}
	
	
	//Face Lateral Esquerda
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {

			writeVertexToF(-x1 + (sX * j), i*sY - y1, z1, f);
			writeVertexToF(-x1 + (sX * (j+1)), i*sY - y1, z1, f);
			writeVertexToF(-x1 + (sX * (j+1)), (i+1)*sY - y1, z1, f);

			writeVertexToF(-x1 + (sX * (j+1)), (i + 1)*sY - y1, z1, f);
			writeVertexToF(-x1 + (sX * j), (i+1)*sY-y1, z1, f);
			writeVertexToF(-x1 + (sX * j), i*sY - y1, z1, f);
		}
	}
	
	
	//Face Traseira
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			writeVertexToF(-x1, i*sY - y1, -z1 + (sZ*j), f);
			writeVertexToF(-x1, i*sY - y1, -z1 + (sZ*(j + 1)), f);
			writeVertexToF(-x1, (i + 1)*sY - y1, -z1 + (sZ*(j + 1)), f);

			writeVertexToF(-x1, (i + 1)*sY - y1, -z1 + (sZ*(j + 1)), f);
			writeVertexToF(-x1, (i + 1)*sY - y1, -z1 + (sZ*j), f);
			writeVertexToF(-x1, i*sY - y1, -z1 + (sZ*j), f);
		}
	}
	
	
	//Face Superior
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			writeVertexToF(x1 - sX * j, y1, z1 - sZ * i, f);
			writeVertexToF(x1 - sX * j, y1, z1 - sZ * (i + 1), f);
			writeVertexToF(x1 - sX * (j + 1), y1, z1 - sZ * (i + 1), f);

			writeVertexToF(x1 - sX * (j + 1), y1, z1 - sZ * (i + 1), f);
			writeVertexToF(x1 - sX * (j+1), y1, z1 - sZ * i, f);
			writeVertexToF(x1 - sX * j, y1, z1 - sZ * i, f);
		}
	}
	
	//Face Inferior
	for (int i = 0; i < slices; i++) {
		for (int j = 0; j < slices; j++) {
			writeVertexToF(x1 - sX * j, -y1, z1 - sZ * i, f);
			writeVertexToF(x1 - sX * (j + 1), -y1, z1 - sZ * (i + 1), f);
			writeVertexToF(x1 - sX * j, -y1, z1 - sZ * (i + 1), f);

			writeVertexToF(x1 - sX * (j + 1), -y1, z1 - sZ * (i + 1), f);
			writeVertexToF(x1 - sX * j, -y1, z1 - sZ * i, f);
			writeVertexToF(x1 - sX * (j + 1), -y1, z1 - sZ * i, f);
		}
	}
	
    return 1;
}