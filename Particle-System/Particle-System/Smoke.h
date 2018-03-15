#pragma once
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"

class Smoke {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	int lifetime;

	Smoke();

	Smoke(glm::vec3 position, glm::vec3 velocity, GLuint lifetime);
	void Draw(Shader shader, Camera camera);
	void Update();
private:
};
