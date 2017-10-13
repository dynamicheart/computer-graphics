

#define GLUT_DISABLE_ATEXIT_HACK

#include <cmath>
#include <stdlib.h>
#include <GL/glut.h>
#include "Camera.h"
#include "Ball.h"
#include "Ground.h"
#include "ColorProtocol.h"
#include "Loader.h"
#include <regex>

Ground ground(8, 8, RED, WHITE);
Camera camera;
Ball ball(1, MAGENTA, 7, ground.centerx(), ground.centerz());
Loader loader;

void init() {
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	ground.create();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camera.getX(), camera.getY(), camera.getZ(),
	          ground.centerx(), 0.0, ground.centerz(),
	          0.0, 1.0, 0.0);

	ground.draw();

	if(loader.hasLoad) {
		loader.draw();
	} else {
		ball.update();
	}

	glFlush();
	glutSwapBuffers();
}

void reshape(const GLint w, const GLint h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(const int v) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, v);
}

void special(const int key, int, int) {
	switch (key) {
		case GLUT_KEY_LEFT:
			camera.moveLeft();
			break;
		case GLUT_KEY_RIGHT:
			camera.moveRight();
			break;
		case GLUT_KEY_UP:
			camera.moveUp();
			break;
		case GLUT_KEY_DOWN:
			camera.moveDown();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void key(const unsigned char key, int x, int y) {
	switch (key) {
		case 'a':
			camera.moveLeft();
			break;
		case 'd':
			camera.moveRight();
			break;
		case 'w':
			camera.moveUp();
			break;
		case 's':
			camera.moveDown();
			break;
		case 'q':
			exit(0);
		default:
			break;
	}
	glutPostRedisplay();
}

void mouse(const int button, int state, int x, int y) {
	switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		default:
			break;
	}
}

int main(int argc, char** argv) {
	if(argc > 2) {
		printf("Usage: ./BouncingBall-3D [filepath]\n");
		return -1;
	}
	if (argc == 2) {
		const std::regex rex(".*.obj$");
		if (!std::regex_match(argv[1], rex)) {
			printf("Unsupported file type\n");
			return -1;
		}
		loader.hasLoad = true;
		loader.load(argv[1]);
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Bouncing Balls");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutTimerFunc(100, timer, 0);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return 0;
}
