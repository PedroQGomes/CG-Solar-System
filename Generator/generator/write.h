#include <iostream>
#include <fstream>
#include <string>

/*
*Funcao que, dada uma string e um ficheiro, escreve a string no ficheiro
*@param text string a escrever
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeToF(char * text, std::ofstream& file);

/*
*Fun��o que, dado um conjuto de coordenadas x,y e z, as escreve no ficheiro
*segundo o formato (x,y,z)
*@param x valor da coordenada x do v�rtice
*@param y valor da coordenada y do v�rtice
*@param z valor da coordenada z do v�rtice
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeVertexToF(float x, float y, float z, std::ofstream& file);
