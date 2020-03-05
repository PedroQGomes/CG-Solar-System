#include "parser.h"


model parseModel(std::string file) {
	
	printf("\nParsing\n");

	model m;
	float xF, yF, zF;
	vertex v;

	//std::ofstream f("plano.txt");
	std::ifstream f("../../Generated/box.xml");

	if(f.fail()) printf("O ficheiro nao existe.\n");

	while (f >> xF >> yF >> zF) {
		printf("STILL PARSING!\n");
		v.x = xF;
		v.y = yF;
		v.z = zF;
		printf("%f\n",xF);
		m.vertexes.push_back(v);
	}


	printf("Done?");
	return m;
	}