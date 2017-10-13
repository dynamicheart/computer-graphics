

#include "Camera.h"
#include <cmath>

Camera::Camera(): theta(90), y(5), dTheta(0.04), dy(0.2) {};

double Camera::getX() const { return 10 * cos(theta); }

double Camera::getY() const { return y; }

double Camera::getZ() const { return 10 * sin(theta); }

void Camera::moveRight() { theta += dTheta; }

void Camera::moveLeft() { theta -= dTheta; }

void Camera::moveUp() { y += dy; }

void Camera::moveDown() { if (y > dy) y -= dy; }
