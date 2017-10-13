

#include <cmath>
#include "Ball.h"


Ball::Ball(const double r, GLfloat* c, const double h, const double x, const double z) :
	radius(r), color(c), maximumHeight(h), density(1), x(x),
	y(h), z(z), direction(-1), lastUpdatedTime(clock()) { }

void Ball::update() {
	const auto currentTime = clock();
	const auto duration = float(currentTime - lastUpdatedTime) / CLOCKS_PER_SEC;
	if (direction < 0) {
		y = maximumHeight - 0.5 * GRAVITATIONAL_ACCELERATION * duration * duration;
	} else {
		y = radius + log2(2 * GRAVITATIONAL_ACCELERATION * (maximumHeight - radius)) * duration - 0.5 *
			GRAVITATIONAL_ACCELERATION * duration * duration;
	}

	if (y > maximumHeight) {
		y = maximumHeight;
		direction = -1;
		lastUpdatedTime = currentTime;
	} else if (y < radius) {
		y = radius;
		direction = 1;
		lastUpdatedTime = currentTime;
	}
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glTranslated(x, y, z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix();
}
