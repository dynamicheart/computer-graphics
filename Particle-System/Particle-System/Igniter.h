#pragma once
// Std. Includes
#include <vector>
#include <random>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Flame.h"
#include "Model.h"
#include "Camera.h"


class Igniter {
public:
	Igniter();
	Igniter(glm::vec3 initPos, GLfloat radius, glm::vec3 initVelocity);
	void Emit();
	void Update();
	void Draw(Camera camera, glm::mat4 projection, glm::mat4 view);
	void Blow(Camera camera);
private:
	Shader shader;
	vector<Flame> flames;
	glm::vec3 initPos;
	glm::vec3 initVelocity;
	GLfloat radius;
	
	GLuint VAO, VBO, texture;

	default_random_engine generator;
	normal_distribution<GLfloat> distribution;
};
