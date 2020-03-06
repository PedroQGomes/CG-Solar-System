#include "parser.h"


model parseModel(std::string file) {
	
	printf("\nParsing\n");

	model m;
	float xF, yF, zF;
	vertex v;

	std::ifstream f(file);

	if(f.fail()) printf("O ficheiro nao existe.\n");

	while (f >> xF >> yF >> zF) {
		v.x = xF;
		v.y = yF;
		v.z = zF;
		m.vertexes.push_back(v);
	}

	return m;
	}