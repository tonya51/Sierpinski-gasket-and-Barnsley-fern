#include <Windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define RAD36 0.628319
#define RAD18 0.314159
#define RAD60 1.047198

int win, oldX, oldY, newX, newY;
GLfloat red, green, blue;
GLfloat left = -250.0, right = 250.0, bottom = -250.0, top = 250.0;
int total = 50000; // number of points
int fractal = 1; // the kind of fractal

void newColor(void){

	/* assigns random colors */
	// srand(time(NULL));
	red = (float)rand()/(float)RAND_MAX;
	green = (float)rand()/(float)RAND_MAX;
	blue = (float)rand()/(float)RAND_MAX;

}

void myinit(void){

	glEnable(GL_BLEND);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(left, right, bottom, top);
	glMatrixMode(GL_MODELVIEW);
	newColor();

}

void display(void){

	typedef GLfloat point2[2];
	int i, j;
	point2 p = {0.0, 0.0};
	glColor3f(red, green, blue);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if(fractal == 1){
		/* pentagon */
		point2 vertices[5] = {{-200.0*tan(RAD36), -200.0}, {200.0*tan(RAD36), -200.0}, {0.0, 200.0/cos(RAD36)}, {(200.0/cos(RAD36))*cos(RAD18), (200.0/cos(RAD36))*sin(RAD18)}, {-(200.0/cos(RAD36))*cos(RAD18), (200.0/cos(RAD36))*sin(RAD18)}};

		for(i = 0; i < total; i++){
			j = rand()%5;
			p[0] = (p[0] + vertices[j][0])*(3.0/8.0);
			p[1] = (p[1] + vertices[j][1])*(3.0/8.0);

			glBegin(GL_POINTS);
				glVertex2fv(p);
			glEnd();
		}

	}

	else if(fractal == 2){
		/* hexagon */
		point2 vertices[6] = {{0.0, -200.0}, {200.0*sin(RAD60), -200.0*cos(RAD60)}, {200.0*sin(RAD60), 200.0*cos(RAD60)}, {0.0, 200.0}, {-200.0*sin(RAD60), 200.0*cos(RAD60)}, {-200.0*sin(RAD60), -200.0*cos(RAD60)}};

		for(i = 0; i < total; i++){
			j = rand()%6;
			p[0] = (p[0] + vertices[j][0])*(1.0/3.0);
			p[1] = (p[1] + vertices[j][1])*(1.0/3.0);

			glBegin(GL_POINTS);
				glVertex2fv(p);
			glEnd();
		}

	}

	else{
		/* Barnsley fern */
		float x, y, r;
		
		for(i = 0; i < total; i++){
			r = (float)rand()/(float)RAND_MAX;

			if(r <= 0.85){
				x = 0.85*p[0] + 0.04*p[1];
				y = -0.04*p[0] + 0.85*p[1] + 1.16;
			}

			else if(r <= 0.92){
				x = 0.2*p[0] - 0.26*p[1];
				y = 0.23*p[0] + 0.22*p[1] + 1.6;
			}

			else if(r <= 0.99){
				x = -0.15*p[0] + 0.28*p[1];
				y = 0.26*p[0] + 0.24*p[1] + 0.44;
			}

			else{
				x = 0;
				y = 0.16*p[1];
			}

			glBegin(GL_POINTS);
				glVertex2fv(p);
			glEnd();
			p[0] = x;
			p[1] = y;
		}

	}
	
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y){

	/* move only if the fractal is either a pentagon or a hexagon */
	if(fractal == 1 || fractal == 2){

		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
			oldX = x;
			oldY = y;
		}

	}

}

void motion(int x, int y){

	/* move only if the fractal is either a pentagon or a hexagon */
	if(fractal == 1 || fractal == 2){
		int dx, dy;
		/* new position of the pointer along the x axis */
		newX = x;
		newY = y;
		/* pointer relocation along the x axis */
		dx = newX - oldX;
		dy = newY - oldY;
		/* new orthographic coordinates */
		left = left - dx;
		right = right - dx;
		top = top + dy;
		bottom = bottom + dy;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(left, right, bottom, top);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
		oldX = x;
		oldY = y;
	}

}

void chooseFromMenu(int option){

	int i;
	
	if(option == 1){
		/* redisplay the fractal with 100000 points */
		total = 100000;
		newColor();
		glutPostRedisplay();
	}

	else if(option == 2){
		/* redisplay the fractal with 200000 points */
		total = 200000;
		newColor();
		glutPostRedisplay();
	}

	else if(option == 3){
		/* display the pentagon */
		total = 50000;
		fractal = 1;
		left = -250.0;
		right = 250.0;
		bottom = -250.0;
		top = 250.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(left, right, bottom, top);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
	}

	else if(option == 4){
		/* display the hexagon */
		total = 50000;
		fractal = 2;
		left = -250.0;
		right = 250.0;
		bottom = -250.0;
		top = 250.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(left, right, bottom, top);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
	}

	else if(option == 5){
		/* display the Barnsley fern */
		total = 50000;
		fractal = 3;
		left = -5.0;
		right = 5.0;
		bottom = -2.0;
		top = 8.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(left, right, bottom, top);
		glMatrixMode(GL_MODELVIEW);
		glutPostRedisplay();
	}

	else{
		/* quit and exit the window */
		glutDestroyWindow(win);
		exit(0);
	}

}

void buildMenu(){

	int menu;
	menu = glutCreateMenu(chooseFromMenu);
	/* menu entries */
	glutAddMenuEntry("100000 points", 1);
	glutAddMenuEntry("200000 points", 2);
	glutAddMenuEntry("Pentagon", 3);
	glutAddMenuEntry("Hexagon", 4);
	glutAddMenuEntry("Barnsley Fern", 5);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

void main(int argc, char** argv){

	/* Standard GLUT initialization */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(680, 680); // 680x680 window
	glutInitWindowPosition(343, 34); // window positioned in the middle of a 1366x768 screen
	win = glutCreateWindow("Pentagon");
	glutDisplayFunc(display);
	myinit();
	buildMenu();
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutMainLoop();

}