
#include<stdio.h>
#include<stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

float x = 0.0f;
float z = 0.0f;

float pX = 1.0;
float pY = 2;
float pZ = 1.0;

const float PI = 3.14159265358979323846;

float camX = 00, camY = 30, camZ = 40;
int startX, startY, tracking = 0;

int alpha = 0, beta = 45, r = 50;
float radius = 50.0f, ri = 35.0f, rc = 15.0f;

unsigned int t, tw, th;
unsigned char * imageData;

GLuint buffer[1];

float h(int i, int j) {
	float h = imageData[th*i + j] * 30.0 / 255.0;
	return h;
}

float hf(float x, float z) {
	

	double x1 = floor(x), x2 = x1 + 1;
	double z1 = floor(z), z2 = z1 + 1;

	
	float fz = z - z1;
	float fx = x - x1;

	float y1 = h(x1 + tw/2, z1 + th/2) * (1 - fz) + h(x1 + tw/2, z2 + th/2) * fz;
	float y2 = h(x2 + tw/2, z1 + th/2) * (1 - fz) + h(x2 + tw/2, z2 + th/2) * fz;

	float heightR = y1 * (1 - fx) + y2 * fx;

	return heightR;

}

void drawTree(float size) {
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glColor3f(139.0 / 255, 69.0 / 255, 19.0 / 255);
	glutSolidCone(size / 4, size * 2, 5, 5);

	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0, 0, size*1.5f);
	glutSolidCone(size, size * 4, 5, 5);


	glPopMatrix();
}

void drawTorus(float size) {
	glPushMatrix();

	glColor3f(1.0f, 0.5f, 1.0f);
	glTranslatef(0, hf(0,0), 0);
	glutSolidTorus(size*0.3f, size, 50, 50);

	glPopMatrix();
}


void drawInnerPots() {

	float angle2 = glutGet(GLUT_ELAPSED_TIME) / 20;
	float angleP = 2 * PI / 8;
	float x, z;
	//glRotatef(angle = glutGet(GLUT_ELAPSED_TIME) / 2, 1, 1, 0);
	glPushMatrix();

	glColor3f(0, 0, 1.0f);

	for (int i = 0; i < 8; i++) {
		glPushMatrix();
		x = rc * cos(angleP * i + (angle2 * PI / 180));
		z = rc * sin(angleP * i + (angle2 * PI / 180));
		glTranslatef(x, 1 + hf(x,z), z);
		glRotatef(-((360 / 8) * i) - angle2, 0, 1, 0);
		glutSolidTeapot(2);
		glPopMatrix();
	}

	glPopMatrix();
}

void drawOuterPots() {

	float angle2 = glutGet(GLUT_ELAPSED_TIME) / 30;
	float angleP = 2 * PI / 16;
	float x, z;
	glPushMatrix();

	glColor3f(1.0f, 0, 0);

	for (int i = 0; i < 16; i++) {
		x = ri * cos(angleP * i + (angle2 * PI / 180));
		z = ri * sin(angleP * i + (angle2 * PI / 180));
		glPushMatrix();
		glTranslatef(x,1 + hf(x,z), z);
		glRotatef(-90 - ((360 / 16) * i) - angle2, 0, 1, 0);
		glutSolidTeapot(2);
		glPopMatrix();
	}

	glPopMatrix();
}

void drawForest(int n) {
	srand(1);

	float rX, rZ;

	while (n > 0) {

		rX = (rand() % 200) - 100;
		rZ = (rand() % 200) - 100;

		if (sqrtf(pow(rX, 2) + pow(rZ, 2)) > radius) {
			glPushMatrix();
			glTranslatef(rX, hf(rX,rZ), rZ);
			drawTree(2);
			glPopMatrix();
			n--;
		}
	}
}


/*
void spherical2Cartesian() {
	camX = r * cos(beta) * sin(alpha);
	camY = r * sin(beta);
	camZ = r * cos(beta) * cos(alpha);
}*/

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0) h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(45, ratio, 1, 1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawTerrain() {
	glColor3f(1,1,1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// colocar aqui o código de desnho do terreno usando VBOs com TRIANGLE_STRIPS
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	for (int i = 0; i < th - 1; i++) {
		glDrawArrays(GL_TRIANGLE_STRIP, i*tw * 2, 2 * tw);
	}
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
}


void renderScene(void) {

	float pos[4] = { -1.0, 1.0, 1.0, 0.0 };

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	pY = 2 + hf(pX, pZ);
	float teste = 10.0;
	printf("%f\n", pY);
	gluLookAt(pX, pY, pZ,
		pX + sin(alpha * PI / 180), pY, pZ + cos(alpha * PI / 180),
		0.0f, 1.0f, 0.0f);

	drawTerrain();

	// Draw torus
	drawTorus(5);

	//Inner circle of teapots
	drawInnerPots();

	//Outer circle of teapots
	drawOuterPots();

	//Draw forest around the pots
	drawForest(200);

	glutPostRedisplay();
	// End of frame
	glutSwapBuffers();
}




void processKeys(unsigned char key, int xx, int yy) {
	// put code to process regular keys in here
	if (key == 'w') {
		pX += sin(alpha * PI / 180);
		pZ += cos(alpha * PI / 180);
	}
	else if (key == 's') {
		pX -= sin(alpha* PI / 180);
		pZ -= cos(alpha* PI / 180);
	}
	else if (key == 'a') {
		pX += sin((PI / 2) + alpha * PI / 180);
		pZ += cos((PI / 2) + alpha * PI / 180);
	}
	else if (key == 'd') {
		pX -= sin((PI / 2) + alpha * PI / 180);
		pZ -= cos((PI / 2) + alpha * PI / 180);
	}
}

void processSpecialKeys(int key, int xx, int yy) {
	if (key == GLUT_KEY_RIGHT) {
		alpha -= 1;
	}
	else if (key == GLUT_KEY_LEFT) {
		alpha += 1;
	}
}



void processMouseButtons(int button, int state, int xx, int yy) {

	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
		else
			tracking = 0;
	}
	else if (state == GLUT_UP) {
		if (tracking == 1) {
			alpha += (xx - startX);
			beta += (yy - startY);
		}
		else if (tracking == 2) {

			r -= yy - startY;
			if (r < 3)
				r = 3.0;
		}
		tracking = 0;
	}
}

/*
void processMouseMotion(int xx, int yy) {

	int deltaX, deltaY;
	int alphaAux, betaAux;
	int rAux;

	if (!tracking)
		return;

	deltaX = xx - startX;
	deltaY = yy - startY;

	if (tracking == 1) {


		alphaAux = alpha + deltaX;
		betaAux = beta + deltaY;

		if (betaAux > 85.0)
			betaAux = 85.0;
		else if (betaAux < -85.0)
			betaAux = -85.0;

		rAux = r;
	}
	else if (tracking == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - deltaY;
		if (rAux < 3)
			rAux = 3;
	}
	camX = rAux * sin(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camZ = rAux * cos(alphaAux * 3.14 / 180.0) * cos(betaAux * 3.14 / 180.0);
	camY = rAux * sin(betaAux * 3.14 / 180.0);
}*/

void init() {

	// 	Load the height map "terreno.jpg"
	ilGenImages(1, &t);
	ilBindImage(t);
	// terreno.jpg is the image containing our height map
	ilLoadImage((ILstring)"terreno.jpg");
	// convert the image to single channel per pixel
	// with values ranging between 0 and 255
	ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
	// important: check tw and th values
	// both should be equal to 256
	// if not there was an error loading the image
	// most likely the image could not be found
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);

	// imageData is a LINEAR array with the pixel values
	imageData = ilGetData();

	// 	Build the vertex arrays
	glewInit();
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, buffer);

	int arraySize = tw * 3 * 2 * (th - 1);
	float * vertexB = (float *)(malloc(sizeof(float) * arraySize));

	int minX = -((float)tw -1)/ 2.0;
	int minZ = -((float)th -1)/ 2.0;
	int index = 0;


	for (int i = 0; i < th - 1; i++) {
		for (int j = 0; j < tw; j++) {
			vertexB[index++] = minX + j * 1.0f;
			vertexB[index++] = h(j, i);
			vertexB[index++] = minZ + i * 1.0f;

			vertexB[index++] = minX + j * 1.0f;
			vertexB[index++] = h(j,i+1);
			vertexB[index++] = minZ + (i + 1)*1.0f;
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*arraySize, vertexB, GL_STATIC_DRAW);
	free(vertexB);

	// 	OpenGL settings
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);
}


int main(int argc, char **argv) {

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("CG@DI-UM");


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);



	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(processMouseButtons);
	//glutMotionFunc(processMouseMotion);

	ilInit();
	init();

	// enter GLUT's main cycle
	glutMainLoop();

	return 0;
}


