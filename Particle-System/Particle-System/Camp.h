#pragma once
// Std. Includes
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
#include "Light.h"

class Camp {
public:
	Camp();
	void Draw(Camera camera, glm::mat4 projection, glm::mat4 view, Light light);
private:
	Shader shader;
	Model model;
};
