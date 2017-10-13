#pragma once

#include <ctime>
#include <GL/glut.h>

#define GRAVITATIONAL_ACCELERATION 9.8
#define DRAG_COEFFICIENT 0.47

class Ball {
	double radius;
	GLfloat* color;
	double maximumHeight;
	double density;

	double x;
	double y;
	double z;

	int direction;

	clock_t lastUpdatedTime;
public:
	Ball(const double r, GLfloat* c, const double h, const double x, const double z);

	void update();
};