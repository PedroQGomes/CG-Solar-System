

/*
*Fun��o que, dada uma string e um ficheiro, escreve a string no ficheiro
*@param text string a escrever
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeToF(char * text, FILE * file);

/*
*Fun��o que, dado um conjuto de coordenadas x,y e z, as escreve no ficheiro
*segundo o formato (x,y,z)
*@param x valor da coordenada x do v�rtice
*@param y valor da coordenada y do v�rtice
*@param z valor da coordenada z do v�rtice
*@param file nome do ficheiro
*@return 1 if successful
*/
int writeVertexToF(float x, float y, float z, FILE * file);

/*
*Fun��o que, dado o nome de um ficheiro, devolve um apontador para o mesmo
*@param file nome do ficheiro
*@return apontador para o ficheiro (NULL no caso de insucesso)
*/
FILE * openFile(char * file);

/*
*Fun��o que, dado um ficheiro, fecha o ficheiro
*@param f apontador do ficheiro
*/
void closeFile(FILE * file);