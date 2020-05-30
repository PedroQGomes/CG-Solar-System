#include "sphere.h"
#include <cmath>
#include "point.h"
#include <vector>

int sphere(float radius, int slices, int stacks, std::string file) {

	std::ofstream f;
	f.open(file);
	float x1,x2,z1,z2,y1,y2, h1,h2;
	float angleH = (2 * PI) / slices;
	float angleV = PI / stacks;
	float stackHeight = radius*2/stacks;

   
	
	for (float i = 0; i < stacks; i++) {
		h1 = sin(angleV * i);
		h2 = sin(angleV * (i + 1));
		for (int j = 0; j < slices; j++) {

			x1 = radius * cos(angleH * j);
			z1 = radius * sin(angleH * j);
			x2 = radius * cos(angleH * (j + 1));
			z2 = radius * sin(angleH * (j + 1));

			y1 = radius * sin((-PI/2) + angleV * i);
			y2 = radius * sin((-PI/2) + angleV *(i + 1));

			writePointToF(x1 * h1, y1, z1 * h1, f);
			writePointToF(x1 * h2, y2, z1 * h2, f);
			writePointToF(x2 * h1, y1, z2 * h1, f);

			writePointToF(x1 * h2, y2, z1 * h2, f);
			writePointToF(x2 * h2, y2, z2 * h2, f);
			writePointToF(x2 * h1, y1, z2 * h1, f);
		}
	}


	return 1;



}

int sphereVBO(float radius, int slices, int stacks, std::string file) {
    std::ofstream f;
    f.open(file);
    
    float alpha0 = static_cast<float>((PI * 2) / slices);
    float beta0 = static_cast<float>((PI) / stacks);
    
    std::vector<Point> normais;
    std::vector<Point> texturas;

    for (int stack = 0; stack <= stacks; stack++) {

        float beta = stack * beta0;

        for (int slice = 0; slice <= slices; slice++) {

            float alpha = slice * alpha0;

            float tx, ty, tz;

            tx = radius * sin(beta) * cos(alpha);
            ty = radius * cos(beta);
            tz = radius * sin(beta) * sin(alpha);

            writePointToF(tx, ty, tz, f);


            tx /= radius;
            ty /= radius;
            tz /= radius;

            Point p = newPoint();
            setX(p, tx);
            setY(p, ty);
            setZ(p, tz);
            normais.push_back(p);

            tx = (slices - (float)slice) / slices;
            ty = (stacks - (float)stack) / stacks;
            Point n = newPoint();
            setX(n, tx);
            setY(n, ty);
            texturas.push_back(n);




        }
    }
    //printf("slices %d\n",slices);
    for (int stack = 0; stack < stacks; stack++) {
        for (int slice = 0; slice < slices; slice++) {
            int A, B, C, D;
            A = stack * (slices + 1) + slice;
            B = (stack + 1) * (slices + 1) + slice;
            C = A + 1;
            D = B + 1;
            //printf("aqui\n");
            writeIntToFile(A, f);
            writeIntToFile(B, f);
            writeIntToFile(C, f);

            writeIntToFile(B, f);
            writeIntToFile(D, f);
            writeIntToFile(C, f);
        }
    }

    for (int i = 0; i < normais.size(); i++) {
        writePointToF(getX(normais.at(i)), getY(normais.at(i)), getZ(normais.at(i)), f);

    }

    for (int i = 0; i < texturas.size(); i++) {
        write2IntToFile(getX(normais.at(i)), getY(normais.at(i)), f);

    }

    return 0;


}
