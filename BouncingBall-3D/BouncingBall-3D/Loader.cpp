

#include "Loader.h"
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glut.h>
#include <iostream>

#define SCALE 1


Loader::Loader(const double interval, const double maximumHeight, GLfloat* c): direction(DOWN), velocity(0),
                                                                               isMoving(false),
                                                                               interval(interval/500.0), y(maximumHeight),
                                                                               minmumHeight(1),
                                                                               maximumHeight(maximumHeight), c(c),
                                                                               hasLoad(false) {}

void Loader::load(char* filename) {
	std::ifstream ifs(filename);
	std::string buf;

	while (std::getline(ifs, buf)) {
		switch (buf[0]) {
			case 'v': {
				switch (buf[1]) {
					case 't': {
						std::istringstream iss(buf);
						std::string head;
						auto t = new Texture();
						iss >> head >> t->tu >> t->tv;
						textures.push_back(*t);
						delete t;
						break;
					}
					case 'n': {
						std::istringstream iss(buf);
						std::string head;
						auto n = new Normal();
						iss >> head >> n->nx >> n->ny >> n->nz;
						normals.push_back(*n);
						delete n;
						break;
					}
					default: {
						std::istringstream iss(buf);
						std::string head;
						auto v = new Point();
						iss >> head >> v->x >> v->y >> v->z;
						points.push_back(*v);
						delete v;
						break;
					}
				}
				break;
			}
			case 'f': {
				for (auto i = 0; i < int(buf.size()); i++) { if (buf[i] == '/') buf[i] = ' '; }


				std::istringstream iss(buf);
				auto f = new Face();
				std::string head;
				iss >> head;

				for (auto i = 0; i < 3; i ++) {
					if (points.size() > 0) {
						iss >> f->v[i];
						f->v[i] --;
					}

					if (textures.size() > 0) {
						iss >> f->t[i];
						f->t[i] --;
					}

					if (normals.size() > 0) {
						iss >> f->n[i];
						f->n[i] --;
					}
				}

				faces.push_back(*f);
				delete f;
				break;
			}
			default:
				break;
		}
	}

	isMoving = true;
	hasLoad = true;
}

void Loader::draw() {
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c);
	for (auto i = 0; i < int(faces.size()); i++) {
		glPushMatrix();
		glTranslatef(3.5, y, 3.5);
		glBegin(GL_TRIANGLES);
		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[0]].tu, textures[faces[i].t[0]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[0]].nx, normals[faces[i].n[0]].ny, normals[faces[i].n[0]].nz);
		}
		glVertex3f(points[faces[i].v[0]].x / SCALE, points[faces[i].v[0]].y / SCALE, points[faces[i].v[0]].z / SCALE);


		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[1]].tu, textures[faces[i].t[1]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[1]].nx, normals[faces[i].n[1]].ny, normals[faces[i].n[1]].nz);
		}
		glVertex3f(points[faces[i].v[1]].x / SCALE, points[faces[i].v[1]].y / SCALE, points[faces[i].v[1]].z / SCALE);


		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[2]].tu, textures[faces[i].t[2]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[2]].nx, normals[faces[i].n[2]].ny, normals[faces[i].n[2]].nz);
		}
		glVertex3f(points[faces[i].v[2]].x / SCALE, points[faces[i].v[2]].y / SCALE, points[faces[i].v[2]].z / SCALE);
		glEnd();
		glPopMatrix();
	}
}

void Loader::update() {
	if(isMoving) {
		switch (direction) {
		case DOWN:
			y -= velocity * interval + 0.5 * GRAVITATIONAL_ACCELERATION * interval * interval;
			if (y <= minmumHeight) {
				y = minmumHeight;
				direction = UP;

				if (velocity == 0) {
					isMoving = false;
				}
			}
			velocity += GRAVITATIONAL_ACCELERATION * interval;

			break;

			break;
		case UP:
			y += velocity * interval - 0.5 * GRAVITATIONAL_ACCELERATION * interval * interval;
			velocity -= GRAVITATIONAL_ACCELERATION * interval;

			if (velocity <= 0) {
				velocity = 0;
				direction = DOWN;
			}
			break;
		default:
			break;
		}
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c);
	for (auto i = 0; i < int(faces.size()); i++) {
		glPushMatrix();
		glTranslatef(3.5f, y, 3.5f);
		glBegin(GL_TRIANGLES);
		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[0]].tu, textures[faces[i].t[0]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[0]].nx, normals[faces[i].n[0]].ny, normals[faces[i].n[0]].nz);
		}
		glVertex3f(points[faces[i].v[0]].x / SCALE, points[faces[i].v[0]].y / SCALE, points[faces[i].v[0]].z / SCALE);


		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[1]].tu, textures[faces[i].t[1]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[1]].nx, normals[faces[i].n[1]].ny, normals[faces[i].n[1]].nz);
		}
		glVertex3f(points[faces[i].v[1]].x / SCALE, points[faces[i].v[1]].y / SCALE, points[faces[i].v[1]].z / SCALE);


		if (textures.size() > 0) { glTexCoord2f(textures[faces[i].t[2]].tu, textures[faces[i].t[2]].tv); }
		if (normals.size() > 0) {
			glNormal3f(normals[faces[i].n[2]].nx, normals[faces[i].n[2]].ny, normals[faces[i].n[2]].nz);
		}
		glVertex3f(points[faces[i].v[2]].x / SCALE, points[faces[i].v[2]].y / SCALE, points[faces[i].v[2]].z / SCALE);
		glEnd();
		glPopMatrix();
	}
}

void Loader::restart() { isMoving = true; }

void Loader::stop() { isMoving = false; }

void Loader::reset() {
	isMoving = true;
	velocity = 0;
	y = maximumHeight;
	direction = DOWN;
}
