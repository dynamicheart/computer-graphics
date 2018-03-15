#pragma once
#include <vector>
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

#include "Camera.h"

struct DirLight {
	glm::vec3 direction;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct PointLight {
	glm::vec3 position;
	glm::float_t constant;
	glm::float_t linear;
	glm::float_t quadratic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SpotLight {
	glm::vec3 postion;
	glm::vec3 direction;
	glm::float_t cutOff;
	glm::float_t outerCutOff;

	glm::float_t constant;
	glm::float_t linear;
	glm::float_t quadratic;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Light {
public:
	DirLight dirLight;
	vector<PointLight> pointLights;
	SpotLight spotLight;
	Light();
	void SwitchDirLight();
	void NextLevelPointLight(GLuint index);
	void SwitchSpotLight();
	void SwitchPointLight();
	void Update(Camera camera);
private:
	GLuint level;
};
