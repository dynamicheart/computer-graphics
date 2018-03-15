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

class Padding {
public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 scale;
	glm::vec3 axis;
	glm::float_t angle;

	Padding(glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec3 axis, glm::float_t angle);
	void Draw(Shader shader, Camera camera);
	void Draw(Shader shader, Model model, Camera camera, glm::float_t scale);
	void DrawNoTexture(Shader shader, Model ourModel, Camera camera, glm::float_t scale);
	void Update(Camera camera);
};