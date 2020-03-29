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
std::string path = "../../Generated/";
model toDraw;
int cur = 0;
GroupModel tmp;
int count = 0;
std::vector<GroupModel>::iterator it;

const float PI = 3.14159265358979323846;
float angle;
float alfa = 0.0f, beta = 0.5f, radius = 100.0f;
float camX=5.0f, camY=5.0f, camZ=5.0f;
int objectCount;

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


void mydraw() {
	glPushMatrix();
	long tmpx = translationGetX((*it)->translation);
	long tmpy = translationGetY((*it)->translation);
	long tmpz = translationGetZ((*it)->translation);

	long stmpx = scaleGetX((*it)->scale);
	long stmpy = scaleGetY((*it)->scale);
	long stmpz = scaleGetZ((*it)->scale);


	glTranslatef(count, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	drawModel((*it)->models->front());
	glPopMatrix();

	count++;
}


void renderScene(void) {

// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// set the camera
	glLoadIdentity();
	//glMatrixMode(GL_PROJECTION);
	
	gluLookAt(camX,camY,camZ, 
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);

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

	for (int i = 0; i < objectCount; i++) {
		mydraw();
		it++;

	}
// End of frame
	glutPostRedisplay();
	glutSwapBuffers();
}



// write function to process keyboard events

void processKeys(unsigned char c, int xx, int yy) {

// put code to process regular keys in here

}
void spherical2Cartesian() {

	camX = radius * cos(beta) * sin(alfa);
	camY = radius * sin(beta);
	camZ = radius * cos(beta) * cos(alfa);
}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {

	case GLUT_KEY_RIGHT:
		alfa -= 0.1; break;

	case GLUT_KEY_LEFT:
		alfa += 0.1; break;

	case GLUT_KEY_UP:
		beta += 0.1f;
		if (beta > 1.5f)
			beta = 1.5f;
		break;

	case GLUT_KEY_DOWN:
		beta -= 0.1f;
		if (beta < -1.5f)
			beta = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: radius -= 1.0f;
		if (radius < 1.0f)
			radius = 1.0f;
		break;

	case GLUT_KEY_PAGE_UP: radius += 1.0f; break;
	}
	spherical2Cartesian();
	glutPostRedisplay();

}

int glMain(int argc, char**argv) {
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1400, 1000);
	glutCreateWindow("Engine");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


	// put here the registration of the keyboard callbacks
	//glutKeyboardFunc(processKeys);
	//glutSpecialFunc(processSpecialKeys);
	

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);	
	//spherical2Cartesian();
	// enter GLUT's main cycle <<>
	glutMainLoop();

	return 1;
}







int main(int argc, char **argv) {
	
   

    tmp = parseXML("../solarSystem.xml");
	std::vector<GroupModel> aux = getGroups(tmp);
	
	it = aux.begin();
	objectCount = aux.size();
	
	printf("aqui\n");
		std::cout << translationGetX((*it)->translation) << std::endl;
		std::cout << translationGetY((*it)->translation) << std::endl;
		std::cout << translationGetZ((*it)->translation) << std::endl;

	

	glMain(0, argv);


	return 1;
}

