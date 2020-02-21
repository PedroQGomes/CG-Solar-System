

/*
*Função que, dada uma string e um ficheiro, escreve a string no ficheiro
*@param text string a escrever
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeToF(char * text, std::ofstream& file);

/*
*Função que, dado um conjuto de coordenadas x,y e z, as escreve no ficheiro
*segundo o formato (x,y,z)
*@param x valor da coordenada x do vértice
*@param y valor da coordenada y do vértice
*@param z valor da coordenada z do vértice
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeVertexToF(float x, float y, float z, std::ofstream& file);
