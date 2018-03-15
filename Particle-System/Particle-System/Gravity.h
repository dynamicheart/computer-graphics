#pragma once
// Std. Includes
#include <vector>
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
#include "Padding.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"

class Gravity {
public:
	Gravity();
	Gravity(Camera camera);
	void Emit(Camera camera);
	void Update(Camera camera);
	void Draw(Camera camera, glm::mat4 projection, glm::mat4 view, Light light);
	void NextModel();
	void RemoveAll();

private:
	Shader containerShader;
	vector<Padding> paddings;
	GLuint VAO, VBO, diffuseMap, specularMap, emissionMap;
	
	glm::vec3 initPos;
	glm::vec3 initVelocity;

	vector<Model> model;
	Shader modelShader;

	GLuint displayObject;
};
