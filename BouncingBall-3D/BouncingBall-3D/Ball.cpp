#define _USE_MATH_DEFINES

#include <cmath>
#include "Ball.h"

Ball::Ball(const double r, GLfloat* c, const double h, const double x, const double z, const double density,
		   const int interval) :
	radius(r), color(c), maximumHeight(h), density(density), x(x),
	y(h), z(z), direction(DOWN), velocity(0), isMoving(true), interval(interval/1000.0) {
	crossSectionalArea = M_PI * radius * radius;
	mass = 4.0 / 3.0 * M_PI * radius * radius * radius;
}

void Ball::update() {
	if (isMoving) {
		const auto resistanceAcceleration = 0.5 * DRAG_COEFFICIENT * crossSectionalArea * FLUID_DENSITY * velocity * velocity / mass;

		switch (direction) {
		case DOWN: {
			const auto acceleration = GRAVITATIONAL_ACCELERATION - resistanceAcceleration;
			y -= velocity * interval + 0.5 * acceleration * interval * interval;

			if (y <= radius) {
				y = radius;
				direction = UP;
				
				if(velocity == 0) {
					isMoving = false;
				}
			}
			else {
				velocity += acceleration * interval;
			}

			break;
		}
		case UP: {
			const auto acceleration = GRAVITATIONAL_ACCELERATION + resistanceAcceleration;
			y += velocity * interval - 0.5 * acceleration * interval * interval;
			velocity -= acceleration * interval;

			if (velocity <= 0) {
				velocity = 0;
				direction = DOWN;
			}

			break;
		}
		default:
			break;
		}
	}

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glTranslated(x, y, z);
	glutSolidSphere(radius, 30, 30);
	glPopMatrix();
}

void Ball::restart() { isMoving = true; }

void Ball::stop() { isMoving = false; }

void Ball::reset() {
	isMoving = true;
	velocity = 0;
	y = maximumHeight;
}
