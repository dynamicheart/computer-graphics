#pragma once
#include <random>
using namespace std;
// GL Includes
#include <GL/glew.h> // Contains all the necessery OpenGL includes

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

class Skybox {
public:
	Skybox();
	void Draw(Camera camera, glm::mat4 view, glm::mat4 projection);
private:
	GLuint skyboxVAO, skyboxVBO;
	Shader skyboxShader;
	GLuint cubemapTexture;
};
