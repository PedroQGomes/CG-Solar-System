#include "write.h"

int writeToF(char * text, std::ofstream& file) {
	if (!file.good()) {
		printf("NULL File");
		return -1;
	}
	
	file << text;

	return 1;
}

int writeVertexToF(float x, float y, float z, std::ofstream& file) {

	if (!file.good()) {
		printf("NULL File");
		return -1;
	}

	file << x << " " << y << " " << z << "\n";
	return 1;
}