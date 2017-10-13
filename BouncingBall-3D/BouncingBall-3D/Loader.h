#pragma once

#include<vector>
#include "Object.h"
#include <GL/glut.h>

struct Point {
	double x;
	double y;
	double z;
};

struct Texture {
	double tu;
	double tv;
};

struct Normal {
	double nx;
	double ny;
	double nz;
};

struct Face {
	int v[3];
	int t[3];
	int n[3];
};

class Loader: Object {
	std::vector<Point> points;
	std::vector<Texture> textures;
	std::vector<Normal> normals;
	std::vector<Face> faces;

	int direction;
	double velocity;
	bool isMoving;
	double interval;

	double y;

	double minmumHeight;
	double maximumHeight;
	GLfloat* c;
	enum { DOWN, UP };
public:
	bool hasLoad;


	Loader(double interval, double maximumHeight, GLfloat *c);

	void load(char *filename);
	void draw();
	void update() override;
	void restart() override;
	void stop() override;
	void reset() override;
};
