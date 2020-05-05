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
		}else if (count > 0 && count > bp->numOfPatches + 1) {
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

void multMatrix(float* m, float* v, float* r) {

	for (int j = 0; j < 4; ++j) {
		r[j] = 0;
		for (int k = 0; k < 4; ++k) {
			r[j] += v[k] * m[j * 4 + k];
		}
	}
}

void getBezier(float u, float v, float** pX, float** pY, float** pZ, float* coords) {
	float U[4] = { u * u * u, u * u, u, 1 };
	float V[4] = { v * v * v, v * v, v, 1 };

	// B(u,v) = U * M * P(x,y,z) * M_t * V
	// M_t = M (symmetric matrix)
	float MV[4];
	multMatrix(*bezierM, V, MV);

	float PMV[3][4];
	multMatrix((float*)pX, MV, PMV[0]);
	multMatrix((float*)pY, MV, PMV[1]);
	multMatrix((float*)pZ, MV, PMV[2]);

	float MPMV[3][4];
	multMatrix(*bezierM, PMV[0], MPMV[0]);
	multMatrix(*bezierM, PMV[1], MPMV[1]);
	multMatrix(*bezierM, PMV[2], MPMV[2]);

	for (int i = 0; i < 3; i++) {
		coords[i] = 0;
		for (int j = 0; j < 4; j++) {
			coords[i] += U[j] * MPMV[i][j];
		}
	}
}



void mkBezierModel(BezierPatch bp, int tess, std::string file) {

	std::ofstream f;
	f.open(file);

	if (!f.good()) {
		printf("File not found\n");
	}
	

	float pX[4][4];
	float pY[4][4];
	float pZ[4][4];
	
	for (int i = 0; i < (*(bp->indices)).size(); i += 16) {
		// copy 16 vertexes to P matrix
		for (int a = 0; a < 4; a++) {
			
			for (int b = 0; b < 4; b++) {
				
				// index of index vector (makes lots of sense, I know)
				int res = i + a * 4 + b;
				int index = (*(bp->indices)).at(res);
				
				pX[a][b] = getX((*(bp->pontos)).at(index));
				
				pY[a][b] = getY((*(bp->pontos)).at(index));
				
				pZ[a][b] = getZ((*(bp->pontos)).at(index));
				
			}
		}

		// until tesselation + 1 to avoid ifs when last point
		for (int u = 0; u <= tess; u++) {

			float coordsP[3];

			// same as comment b4
			for (int v = 0; v <= tess; v++) {

				getBezier(u / (float)tess, v / (float)tess, (float**)pX, (float**)pY, (float**)pZ, coordsP);
				writePointToF(coordsP[0], coordsP[1], coordsP[2], f);
			}
		}
	}

	// indexes
	int indicesPerPatch = (tess + 1) * (tess + 1); 
	for (int i = 0; i < (*(bp->indices)).size(); i += 16) {
		
		int currentPatch = i / 16;

		for (int u = 0; u < tess; u++) {
			for (int v = 0; v < tess; v++) {
				// A -- B
				// C -- D
				int indexA = currentPatch * indicesPerPatch + ((tess + 1) * u) + v;
				int indexB = indexA + 1;
				int indexC = currentPatch * indicesPerPatch + (tess + 1) * (u + 1) + v;
				int indexD = indexC + 1;

				writeIntToFile(indexA, f);
				writeIntToFile(indexC, f);
				writeIntToFile(indexB, f);

				writeIntToFile(indexC, f);
				writeIntToFile(indexD, f);
				writeIntToFile(indexB, f);

			}
		}
	}
}


