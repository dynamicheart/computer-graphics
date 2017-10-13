#pragma once

#include <GL/glut.h>
 
class Ground {
	const GLfloat* c1;
	const GLfloat* c2;
	int displayListId;
	int width;
	int depth;
public:
	Ground(const int width, const int depth, GLfloat* c1, GLfloat* c2);

	double centerx() const;
	double centerz() const;

	void create();

	void draw() const;
};
