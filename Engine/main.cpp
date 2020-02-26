#include "headers.h"
#include "parser.h"
#include "model.h"
#include "vertex.h"

#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//std::string path = "../../../Generated Files/plano.txt";
std::string path = "plano.txt";
model toDraw2;
model toDraw;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(5.0,5.0,5.0, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

// put the geometric transformations here


// put drawing instructions here
	//drawModel(toDraw);
	drawModel(toDraw2);

	// End of frame
	glutSwapBuffers();
}



// write function to process keyboard events


int glMain(int argc, char**argv) {
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Engine");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard callbacks

	

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	vertex v1 = newVertex(1.0, 0.0, 1.0);
	vertex v2 = newVertex(1.0,0.0,-1.0);
	vertex v3 = newVertex(-1.0, 0.0, -1.0);
	addVertex(&toDraw, v1);
	addVertex(&toDraw, v2);
	addVertex(&toDraw, v3);
	vertex v4 = newVertex(-1.0, 0.0, -1.0);
	vertex v5 = newVertex(-1.0, 0.0, 1.0);
	vertex v6 = newVertex(1.0, 0.0, 1.0);
	addVertex(&toDraw, v4);
	addVertex(&toDraw, v5);
	addVertex(&toDraw, v6);
	


	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}



int main(int argc, char **argv) {

	//if (argc < 2) std::cout << "N�mero incorreto de argumentos";

	//toDraw = parseModel(argv[argc]);
	printf("Wat");
	//printf("%s", path);
	toDraw2 = parseModel(path);
	

	//argc--;

	glMain(argc, argv);

	return 1;
}
