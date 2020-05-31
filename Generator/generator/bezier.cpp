#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include "bezier.h"
#include "write.h"
#include "point.h"
using namespace std;

float bezierM[4][4] = { { -1.0f, 3.0f, -3.0f, 1.0f},
					   { 3.0f, -6.0f, 3.0f, 0.0f},
					   { -3.0f, 3.0f, 0.0f, 0.0f},
					   { 1.0f, 0.0f, 0.0f, 0.0f} };


struct bezier {
	std::vector<Point> * pontos;
	std::vector<int> * indices;
	int numOfPatches;
	int numOfCtrPoints;
    
};
void cross(float* a, float* b, float* res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void multMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

BezierPatch initParser(std::string file) {
	printf("parsing bezier model\n");

	std::string linha;
	ifstream f(file);

	if (f.fail()) printf("O ficheiro nao existe.\n");

	BezierPatch bp = (BezierPatch)malloc(sizeof(struct bezier));
	bp->indices = new vector<int>;
	bp->pontos = new vector<Point>;
	bp->numOfCtrPoints = 0;
	bp->numOfPatches = 0;

	int count = 0;
	int patchcount = 0;
	int pointcount = 0;
	int tmpPatch = 0;
	float tx, ty, tz;
	tx = ty = tz = 0.0;
	while (getline(f, linha)) {

		istringstream iss(linha);

		if (count == 0) {
			if (iss >> patchcount) {
				bp->numOfPatches = patchcount;
				count++;
			}
			else {
				printf("Ficheiro mal formatado impossivel de dar parse\n");
				break;
			}
		}
		else if (count > 0 && count <= bp->numOfPatches) {
			std::string token;
			std::string stringNoStream = iss.str();
			int index;
			size_t  pos = 0;
			while ((pos = stringNoStream.find(",")) != std::string::npos) {

				token = stringNoStream.substr(0, pos);
				std::stringstream tmp(token);
				tmp >> index;

				printf("index: %d\n", index);
				bp->indices->push_back(index);
				stringNoStream.erase(0, pos + 1);
			}
			std::stringstream tmpStream(stringNoStream);
			tmpStream >> index;
			bp->indices->push_back(index);
			count++;
		}
		else if (count > 0 && count == bp->numOfPatches + 1) {
			if (iss >> pointcount) {
				bp->numOfCtrPoints = pointcount;
				count++;
			}
			else {
				printf("Ficheiro mal formatado sem pontos de controlo\n");
				break;
			}
		}
		else if (count > 0 && count > bp->numOfPatches + 1) {
			std::string token;
			std::string stringNoStream = iss.str();
			size_t  pos = 0;
			float pontos[3];
			int aux = 0;
			while ((pos = stringNoStream.find(",")) != std::string::npos) {
				token = stringNoStream.substr(0, pos);
				std::stringstream tmp(token);
				tmp >> pontos[aux++];
				stringNoStream.erase(0, pos + 1);
			}
			std::stringstream tmpStream(stringNoStream);
			tmpStream >> pontos[2];
			bp->pontos->push_back(newPoint(pontos[0], pontos[1], pontos[2]));
			count++;
		}
	}
	//printf("\n\n\n");
	//printf("numero de patches %d\n", bp->numOfPatches);

	//printf("indices size %d\n",(*(bp->indices)).size());
	//printf("numero de pontos %d\n", bp->numOfCtrPoints);
	//printf("pontos size %d\n", (*(bp->pontos)).size());


	return bp;

}

void getBezier(float u, float v, float** pX, float** pY, float** pZ, float* coords, float* norm, float* tex) {
	float U[4] = { u * u * u, u * u, u, 1 };
	float V[4] = { v * v * v, v * v, v, 1 };
	float DU[4] = { 3 * u * u, 2 * u, 1, 0 };
	float DV[4] = { 3 * v * v, 2 * v, 1, 0 };
	float dU[3];
	float dV[3];

	// B(u,v) = U * M * P(x,y,z) * M_t * V
	// dB(u,v)/u = DU * M * P(x,y,z) * M_t * V_t
	// dB(u,v)/v = U * M * P(x,y,z) * M_t * dV
	// M_t = M (symmetric matrix)
	float MV[4];
	multMatrixVector(*bezierM, V, MV);

	// dB / u => M_t * V_t
	float uMV[4];
	multMatrixVector(*bezierM, V, uMV);

	// db / v => M_t * dV
	float vMV[4];
	multMatrixVector(*bezierM, DV, vMV);

	float PMV[3][4];
	multMatrixVector((float*)pX, MV, PMV[0]);
	multMatrixVector((float*)pY, MV, PMV[1]);
	multMatrixVector((float*)pZ, MV, PMV[2]);

	// dB / u => P * MV
	float uPMV[3][4];
	multMatrixVector((float*)pX, uMV, uPMV[0]);
	multMatrixVector((float*)pY, uMV, uPMV[1]);
	multMatrixVector((float*)pZ, uMV, uPMV[2]);

	// dB / v => P * MdV
	float vPMV[3][4];
	multMatrixVector((float*)pX, vMV, vPMV[0]);
	multMatrixVector((float*)pY, vMV, vPMV[1]);
	multMatrixVector((float*)pZ, vMV, vPMV[2]);

	float MPMV[3][4];
	multMatrixVector(*bezierM, PMV[0], MPMV[0]);
	multMatrixVector(*bezierM, PMV[1], MPMV[1]);
	multMatrixVector(*bezierM, PMV[2], MPMV[2]);

	// dB / u => M * P * M * V
	float uMPMV[3][4];
	multMatrixVector(*bezierM, uPMV[0], uMPMV[0]);
	multMatrixVector(*bezierM, uPMV[1], uMPMV[1]);
	multMatrixVector(*bezierM, uPMV[2], uMPMV[2]);

	// dB / v => M * P * M * dV
	float vMPMV[3][4];
	multMatrixVector(*bezierM, vPMV[0], vMPMV[0]);
	multMatrixVector(*bezierM, vPMV[1], vMPMV[1]);
	multMatrixVector(*bezierM, vPMV[2], vMPMV[2]);

	for (int i = 0; i < 3; i++) {
		coords[i] = 0.0f;
		dU[i] = 0.0f;
		dV[i] = 0.0f;
		for (int j = 0; j < 4; j++) {
			coords[i] += U[j] * MPMV[i][j];
			dU[i] += DU[j] * uMPMV[i][j];
			dV[i] += U[j] * vMPMV[i][j];
		}
	}

	normalize(dU);
	normalize(dV);
	cross(dV, dU, norm);
	normalize(norm);

	tex[0] = u;
	tex[1] = v;
}

int mkBezierModel(BezierPatch bp, int tessellation, std::string fileName) {

	std::ofstream file;
	file.open(fileName);
	if (!file) {
		fprintf(stderr, "INVALID FILE! %s\n", fileName);
		return 2;
	}
	/*
	BezierPatch bp = (BezierPatch)malloc(sizeof(struct bezier));
	bp->indices = new vector<int>;
	bp->pontos = new vector<Point>;
	bp->numOfCtrPoints = 0;
	bp->numOfPatches = 0;
	*/
	
	float pX[4][4];
	float pY[4][4];
	float pZ[4][4];

	std::vector<Point> normals;
	std::vector<Point> textures;

	//printf("aqui1\n");
	for (int i = 0; i < bp->indices->size(); i += 16) {

		
		for (int a = 0; a < 4; a++) {
			for (int b = 0; b < 4; b++) {
				
				int index = bp->indices->at(i + a * 4 + b);
				pX[a][b] = getX(bp->pontos->at(index));
				pY[a][b] = getY(bp->pontos->at(index));
				pZ[a][b] = getZ(bp->pontos->at(index));
			}
		}

		
		for (int u = 0; u <= tessellation; u++) {

			float coordsP[3];
			float norm[3];
			float tex[2];

			
			for (int v = 0; v <= tessellation; v++) {

				getBezier(u / (float)tessellation, v / (float)tessellation, (float**)pX, (float**)pY, (float**)pZ, coordsP, norm, tex);
				writePointToF(coordsP[0], coordsP[1], coordsP[2], file);
				Point n = newPoint();
				setX(n, norm[0]);
				setY(n, norm[1]);
				setZ(n, norm[2]);
				normals.push_back(n);
				Point t = newPoint();
				setX(t, tex[0]);
				setY(t, tex[1]);
				setZ(t, 0.0f);
				textures.push_back(t);
			}
		}
	}
	
	// indexes
	int indicesPerPatch = (tessellation + 1) * (tessellation + 1);
	for (int i = 0; i < bp->indices->size(); i += 16) {

		int currentPatch = i / 16;

		for (int u = 0; u < tessellation; u++) {
			for (int v = 0; v < tessellation; v++) {
				// A -- B
				// C -- D
				int indexA = currentPatch * indicesPerPatch + ((tessellation + 1) * u) + v;
				int indexB = indexA + 1;
				int indexC = currentPatch * indicesPerPatch + (tessellation + 1) * (u + 1) + v;
				int indexD = indexC + 1;

				writeIntToFile(indexA, file);
				writeIntToFile(indexC, file);
				writeIntToFile(indexB, file);

				writeIntToFile(indexC, file);
				writeIntToFile(indexD, file);
				writeIntToFile(indexB, file);

			}
		}
	}
	
	for (Point v : normals) {
		writePointToF(getX(v), getY(v), getZ(v), file);
	}
	
	for (Point v : textures) {
		write2IntToFile(getX(v), getY(v), file);
	}
}


