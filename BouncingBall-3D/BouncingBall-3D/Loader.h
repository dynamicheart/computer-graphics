#pragma once

#include<vector>

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

class Loader {
private:
	std::vector<Point> points;
	std::vector<Texture> textures;
	std::vector<Normal> normals;
	std::vector<Face> faces;
public:
	bool hasLoad = false;

	void load(char *filename);
	void draw();
};
