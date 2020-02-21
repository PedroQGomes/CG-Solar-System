#include <stdio.h>
#include <stdlib.h>

int writeToF(char * text, FILE * file) {
	if (file == NULL) {
		printf("NULL File");
		return -1;
	}
	fprintf(file, "%s", text);
	return 1;
}

int writeVertexToF(float x, float y, float z, FILE * file) {

	if (file == NULL) {
		printf("NULL File");
		return -1;
	}

	fprintf(file, "%f %f %f\n", x, y, z);
	return 1;
}

FILE * openFile(char * file) {
	FILE * f;
	fopen_s(&f, file, "w");
	return f;
}

void closeFile(FILE * file) {
	fclose(file);
}