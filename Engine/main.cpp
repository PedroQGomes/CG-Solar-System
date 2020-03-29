#include "headers.h"
#include "parser.h"
#include "model.h"
#include "vertex.h"
#include "xmlParser.h"
#include "scale.h"
#include "rotation.h"
#include "translation.h"
#include "operation3f.h"

#include <vector>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


//std::string path = "../../../Generated Files/";
std::string path = "../Generated/";
model toDraw;

int moving;
float startx;
float starty;

float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX, camY, camZ;

void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

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
	gluLookAt(camX, camY, camZ,
			0.0, 0.0, 0.0,
			0.0f, 1.0f, 0.0f);

// put the geometric transformations here
    glBegin(GL_LINES);
// X axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f( 100.0f, 0.0f, 0.0f);
// Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
// Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();

// put drawing instructions here
	drawModel(toDraw);

	
// End of frame
	glutPostRedisplay();
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

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}



int main(int argc, char **argv) {
	
   /* std::vector<std::string> filePathsOfShapes = parseXML("shapes.xml");
    for(int i = 0; i < filePathsOfShapes.size(); i++){
        printf("%s\n",filePathsOfShapes[i].c_str());
    }
	
    std::string real_path;
	
    for(int i = 0; i < filePathsOfShapes.size();i++) {
        real_path = path + filePathsOfShapes[i];
        toDraw = parseModel(real_path);
    } */

    GroupModel tmp = parseXML("solarSystem.xml");

	//glMain(0, argv);

	return 1;
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		moving = 1;
		startx = x;
		starty = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		moving = 0;

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		moving = 2;
		starty = y;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
		moving = 0;
}

void motion(int x, int y)
{
	if (moving == 1)
	{
		alfa += (x - startx) / 50;
		beta += (y - starty) / 50;
		startx = x;
		starty = y;
	}
	if (moving == 2)
	{
		radius += (y - starty);
		starty = y;
	}
	spherical2Cartesian();
	glutPostRedisplay();
}


