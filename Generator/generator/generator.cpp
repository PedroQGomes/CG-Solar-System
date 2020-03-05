// generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include "plane.h"
#include "box.h"
#include "cone.h"

//Path relativo para a diretoria onde os ficheiros s�o gerados
std::string path = "../../Generated/";

//Numero m�nimo de argumentos necess�rios ()
const int MIN_ARGS = 4;

//N�mero de argumentos necess�rios para gerar um plano
const int PLANE_ARGS = 4;
//plano 4 plano.txt

//N�mero de argumentos necess�rios para gerar uma caixa
const int BOX_ARGS = 6;
//box 2 2 2 box.txt

//N�mero de argumentos necess�rios para gerar uma esfera
const int SPHERE_ARGS = 6;

//N�mero de argumentos necess�rios para gerar um cone
const int CONE_ARGS = 7;

int main(int argc, char** argv)
{
	if (argc < MIN_ARGS) {
		return printf("Not enough arguments");
	}

	std::string type = argv[1];
	

	if (type.compare("plane") == 0 && argc == PLANE_ARGS) {

			
			printf("It's a plane!\n");
			float size = std::stof(argv[2]);
			std::string real_path = path + argv[3];
			plane(size, real_path);
	}
	else if (type.compare("box") == 0) {
		printf("It's a box!\n");
		float x = std::stof(argv[2]);
        float y = std::stof(argv[3]);
        float z = std::stof(argv[4]);
        std::string real_path2 = path + argv[5];
        box(x,y,z,real_path2);
	}
	else if(type.compare("cone") == 0){
		printf("It's a cone!\n");
		float radius = std::stof(argv[2]);
		float height = std::stof(argv[3]);
		int slices = std::stof(argv[4]);
		int stacks = std::stof(argv[5]);
		std::string real_path = path + argv[6];
		cone(radius, height, slices, stacks, real_path);
	}
	else if (type.compare("sphere") == 0) {
		printf("It's a sphere!\n");
	}
	else printf("It's..... nothing.\n");
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
