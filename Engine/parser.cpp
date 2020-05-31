#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <fstream>
#include <sstream>
#include "parser.h"

int ts = 0;
using namespace std;
int parseModel(Model m , std::string file) {

	printf("\nParsing\n");
	if (m == nullptr) {
		return 2;
	}
	float xF, yF, zF;
	std::string real_path;
	real_path = "../../Generated/" + file;
	std::string linha;
	ifstream f (real_path);
	if (f.fail()) printf("Erro ao abrir %s\n",file.c_str());
	bool change = false;
	bool firstIt = true;
	while (getline(f,linha)) {
		istringstream iss(linha);
		ts++;
		if (!(iss >> xF >> yF >> zF)) {
			if (firstIt) firstIt = false;
			if (change) {
				addTexture(m, xF);
				addTexture(m, yF);
			}
			else {
				unsigned int s = xF;
				addIndice(m, s);
			}
		}
		else { 
			if (!firstIt && !change) change = true;
			if (change) {
				addNormal(m, xF);
				addNormal(m, yF);
				addNormal(m, zF);
			}
			else {
				addVertices(m, xF);
				addVertices(m, yF);
				addVertices(m, zF);
			}
			
		}
	}

	

	printf("tamanho %d\n", (getVertices(m))->size());
	
	printf("finished parsing\n");
	return 0;
	}