#include "parser.h"


model parseModel(std::string file) {
	
	printf("\nParsing\n");

	model m;
	float xF, yF, zF;
	vertex v;

	std::ifstream f("\\plano2.txt", std::ifstream::in);
	printf("Big Oof\n");
	if(f.fail()) printf("F\n");
	printf("ily\n");
	while (f >> xF >> yF >> zF) {
		v.x = xF;
		v.y = yF;
		v.z = zF;
		printf("%f",xF);
		m.vertexes.push_back(v);
	}
	
	return m;
}