#include "Ground.h"


Ground::Ground(const int width, const int depth, GLfloat* c1, GLfloat* c2) : c1(c1), c2(c2), displayListId(0),
																			 width(width), depth(depth) { }

double Ground::centerx() const { return width / 2; }

double Ground::centerz() const { return depth / 2; }

void Ground::create() {
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);
	GLfloat lightPosition[] = {4, 3, 7, 1};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
	glEnable(GL_LIGHT1);
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c1);
	glVertex3d(0, 0, 0);
	glVertex3d(width/2, 0, 0);
	glVertex3d(width/2, 0, depth/2);
	glVertex3d(0, 0, depth/2);

	glVertex3d(width / 2, 0, depth / 2);
	glVertex3d(width, 0, depth / 2);
	glVertex3d(width, 0, depth);
	glVertex3d(width / 2, 0, depth);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, c2);
	glVertex3d(width / 2, 0, 0);
	glVertex3d(width, 0, 0);
	glVertex3d(width, 0, depth / 2);
	glVertex3d(width / 2, 0, depth / 2);

	glVertex3d(width / 2, 0, depth / 2);
	glVertex3d(width / 2, 0, depth);
	glVertex3d(0 , 0, depth);
	glVertex3d(0, 0, depth /2);

	glEnd();
	glEndList();
}

void Ground::draw() const { glCallList(displayListId); }
