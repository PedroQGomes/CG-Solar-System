//
// Created by pedro on 05/03/20.
//

#include "box.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "write.h"

using namespace std;


int box(float x,float y, float z, float slices, std::string file) {

    std::ofstream f;
    f.open(file);
    float x1, z1;

    x1 = x / 2;
    z1 = z / 2;

    printf("Writting\n");
    //face frontal
    writeVertexToF(-x1, 0.0, z1, f);
    writeVertexToF( x1, 0.0, z1, f);
    writeVertexToF( -x1, y,z1, f);

    writeVertexToF( x1, 0.0,z1, f);
    writeVertexToF(x1, y,z1, f);
    writeVertexToF(-x1, y, z1, f);


    //face lateral direita
    writeVertexToF( x1, 0.0,z1, f);
    writeVertexToF(x1, 0.0,-z1, f);
    writeVertexToF(x1, y, z1, f);


    writeVertexToF( x1, 0.0,-z1, f);
    writeVertexToF(x1, y,-z1, f);
    writeVertexToF(x1, y, z1, f);

    //20 face superior
    writeVertexToF( -x1, y,z1, f);
    writeVertexToF(x1, y,z1, f);
    writeVertexToF(x1, y, -z1, f);


    writeVertexToF( x1, y,-z1, f);
    writeVertexToF(-x1, y,-z1, f);
    writeVertexToF(-x1, y, z1, f);

    //20 face esquerda
    writeVertexToF( -x1, 0,-z1, f);
    writeVertexToF(-x1, 0,z1, f);
    writeVertexToF(-x1, y, z1, f);


    writeVertexToF( -x1, y,z1, f);
    writeVertexToF(-x1, y,-z1, f);
    writeVertexToF(-x1, 0, -z1, f);


    //20 face back
    writeVertexToF( -x1, y,-z1, f);
    writeVertexToF(x1, y,-z1, f);
    writeVertexToF(x1, 0, -z1, f);


    writeVertexToF( x1, 0,-z1, f);
    writeVertexToF(-x1, 0,-z1, f);
    writeVertexToF(-x1, y, -z1, f);


    //20 face inferior
    writeVertexToF( x1, 0,z1, f);
    writeVertexToF(-x1, 0,z1, f);
    writeVertexToF(-x1, 0, -z1, f);


    writeVertexToF( -x1, 0,-z1, f);
    writeVertexToF(x1, 0,-z1, f);
    writeVertexToF(x1, 0, z1, f);

    //slices
    if(slices > 1){
            float aux = x /slices;
            float count = 1;
            float tmpx1 = x1 -aux;
            while (count < slices){
                writeVertexToF(tmpx1, 0.0,z1, f);
                writeVertexToF(tmpx1, 0.0,-z1, f);
                writeVertexToF(tmpx1, y, z1, f);


                writeVertexToF(tmpx1, 0.0,-z1, f);
                writeVertexToF(tmpx1, y,-z1, f);
                writeVertexToF(tmpx1, y, z1, f);

                tmpx1 -= aux;
                count++;
            }



    }

    return 1;
}