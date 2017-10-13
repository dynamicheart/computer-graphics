#pragma once

#include <GL/glut.h>
#include "Object.h"

#define DRAG_COEFFICIENT 0.47
#define FLUID_DENSITY 1.225

class Ball: Object{
	double radius;
	GLfloat* color;
	double maximumHeight;
	double density;

	double x;
	double y;
	double z;

	int direction;
	double velocity;
	bool isMoving;
	double interval;

	// Calculated
	double mass;
	double crossSectionalArea;

	enum {DOWN, UP};

public:
	Ball(const double r, GLfloat* c, const double h, const double x, const double z, const double density, const int interval);

	void update() override;

	void restart() override;

	void stop() override;

	void reset() override;
};
