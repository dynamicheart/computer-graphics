#include "Ground.h"


Ground::Ground(const int width, const int depth, GLfloat* c1, GLfloat* c2) : c1(c1), c2(c2), displayListId(0),
																			 width(width), depth(depth) { }

double Ground::centerx() const { return width / 2; }

double Ground::centerz() const { return depth / 2; }

void Ground::create() {
	displayListId = glGenLists(1);
	glNewList(displayListId, GL_COMPILE);
	/*GLfloat lightPosition[] = {4, 3, 7, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);*/
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);
	for (auto x = 0; x < width - 1; x++) {
		for (auto z = 0; z < depth - 1; z++) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE,
						 (x + z) % 2 == 0 ? c1 : c2);
			glVertex3d(x, 0, z);
			glVertex3d(x + 1, 0, z);
			glVertex3d(x + 1, 0, z + 1);
			glVertex3d(x, 0, z + 1);
		}
	}
	glEnd();
	glEndList();
}

void Ground::draw() const { glCallList(displayListId); }
