# MIEI - 3ºAno - Computação Gráfica

O trabalho pratico proposto consiste em desenvolver um engine para uma cena em 3D que terá como tema o sistema solar. O trabalho pratico contem 4 fases de desenvolvimento que são as seguintes

* Fase 1 - Primitivas gráficas
* Fase 2 - Transformações geométricas
* Fase 3 - Superfícies cúbicas e VBOs
* Fase 4 - Normais e coordenadas de textura

## Fase 1 - Primitivas gráficas

Esta fase consiste em desenvolver duas aplicações, uma para gerar ficheiros com a informação dos modelos e um engine para ler os ficheiros e mostrar os modelos numa cena.

Os modelos que são desenvolvidos nesta fase são os seguintes:

* Plano centrado na origem composto por dois triângulos
* Caixa com um dado numero de divisões 
* Esfera
* Cone

## Fase 2 - Transformações geométricas

Esta fase consiste em criar cenas hierárquicas usando transformações geométricas. Uma cena é definida como uma árvore em que os nodos contem transformações geométricas e um conjunto de modelos.

As transformações geométricas que são consideradas são as seguintes

* Translação
* Rotação
* Escala

## Fase 3 - Superfícies cúbicas e VBOs

Esta fase consiste em que a aplicação geradora dos modelos crie um novo tipo de modelo baseado nos Patches Bezier. A aplicação geradora recebe como parâmetros o nome do ficheiro a onde os pontos de controlo estão definidos. Por outro lado o engine cria animações,rotações translações e escalas,baseadas nas curvas de Catmull-Rom

## Fase 4 - Normais e coordenadas de textura

Esta fase consiste em que a aplicação geradora dos modelos deve criar coordenadas de textura e as normais para cada vértice. O engine por outro lado deve ter luz e as funcionalidades de textura a funcionar tal como ler e aplicar as alterações feitas aos ficheiros de modelo.


### Dependências

Neste projeto são usadas as seguintes bibliotecas

```
OpenGL
```
```
Glut
```
```
Devil
```


### Compilação e Testes

O projeto desenvolvido tem duas aplicações e para ambas é aconselhável o uso de um **IDE** para a a compilação e execução. No caso de escolher o **Visual Studio** é simplesmente criar um projeto com a opção de "from existing sources" e escolher e escolher a diretoria do repositório da aplicação que pretende utilizar, Generator ou Engine.
