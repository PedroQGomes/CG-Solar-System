#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include "parser.h"

int ts = 0;
using namespace std;
model parseModel(std::string file) {

	printf("\nParsing\n");

	model m;
	float xF, yF, zF;
	vertex v;
	std::string real_path;
	real_path = "../../Generated/" + file;
	std::string linha;
	ifstream f (real_path);
	if (f.fail()) printf("O ficheiro nao existe.\n");
	while (getline(f,linha)) {
		istringstream iss(linha);
		ts++;
		if (!(iss >> xF >> yF >> zF)) {
			unsigned int s = xF;
			//printf("Linha %d  X %u\n", ts , s); 
			m.indices.push_back(s);
		}
		else {
			v.x = xF;
			v.y = yF;
			v.z = zF;
			m.vertexes.push_back(xF);
			m.vertexes.push_back(yF);
			m.vertexes.push_back(zF);
		}
	}

	

	printf("tamanho %d\n", m.vertexes.size());
	
	printf("finished parsing\n");
	return m;
	}