//
// Created by pedro on 06/03/20.
//

#include "sphere.h"

int sphere(float radius,int slices, int stacks, std::string file) {

    std::ofstream f;
    f.open(file);

    float angle = (2 * PI) / slices;
    float x1, z1, x2, z2,y_count,y;
    float altura = radius*2;
    y_count = altura/stacks;
    y = 0;
    for(int j = 0; j<stacks;j++) {

        for (int i = 0; i < slices; i++) {

            x1 = radius * cos(angle * i);
            z1 = radius * sin(angle * i);
            x2 = radius * cos(angle * (i + 1));
            z2 = radius * sin(angle * (i + 1));

            writeVertexToF(x2, y, z2, f);
            writeVertexToF(x1, y, z1, f);
            writeVertexToF(0.0, y, 0.0, f);
        }
        y += y_count;
    }



    f.close();


    return 1;
}
