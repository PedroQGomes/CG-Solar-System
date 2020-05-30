#include "write.h"

int writeToF(char * text, std::ofstream& file) {
	if (!file.good()) {
		printf("NULL File");
		return -1;
	}
	
	file << text;

	return 1;
}

void write2IntToFile(float i, float j, std::ofstream& file) {
	if (!file.good()) {
		printf("NULL File");
	
	}
	file << i << " " << j << "\n";


}


int writeIntToF(int i, FILE* file) {
	if (file == NULL) {
		printf("Error!");
		return 1;
	}
	fprintf(file, "%d\n", i);
	return 0;
}

int writeIntToFile(int i, std::ofstream& file) {
	if (!file.good()) {
		printf("NULL File");
		return 1;
	}
	file << i << "\n";
	return 0;
}

int writePointToFile(float x, float y, float z, FILE* file) {

	if (file == NULL)
	{
		printf("Error!");
		return 1;
	}
	fprintf(file, "%f %f %f\n", x, y, z);
	return 0;
}

int writePointToF(float x, float y, float z, std::ofstream& file) {

	if (!file.good()) {
		printf("NULL File");
		return -1;
	}

	file << x << " " << y << " " << z << "\n";
	return 1;
}

FILE* openFile(char* file) {
	FILE* fp;
	fopen_s(&fp,file, "w");
	return fp;
}