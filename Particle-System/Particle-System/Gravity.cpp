#include "Gravity.h"

Gravity::Gravity() {

}

Gravity::Gravity(Camera camera) {

	this->containerShader = Shader("../assets/basic.vert", "../assets/basic.frag");
	this->modelShader = Shader("../assets/model.vert", "../assets/model.frag");
	// Set up vertex data (and buffer(s)) and attribute pointers
	GLfloat vertices[] = {
		// Positions          // Normals           // Texture Coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	// First, set the container's VAO (and VBO)
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	displayObject = 0;

	// Load textures
	glGenTextures(1, &diffuseMap);
	glGenTextures(1, &specularMap);
	glGenTextures(1, &emissionMap);
	int width, height;
	unsigned char* image;
	// Diffuse map
	image = SOIL_load_image("../assets/container2.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, diffuseMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	// Specular map
	image = SOIL_load_image("../assets/container2_specular.png", &width, &height, 0, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, specularMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	containerShader.Use();
	glUniform1i(glGetUniformLocation(containerShader.Program, "material.diffuse"), 0);
	glUniform1i(glGetUniformLocation(containerShader.Program, "material.specular"), 1);
	glUniform1f(glGetUniformLocation(containerShader.Program, "material.shininess"), 32.0f);

	model.push_back(Model("../assets/bread/Bread.obj"));

}

void Gravity::Emit(Camera camera) {
	Padding padding = Padding(glm::normalize(camera.Front) * (rand() / ((glm::float_t)RAND_MAX/10.0f)) + camera.Position,
		glm::vec3(0.001f * (rand() % 10), 0.001f * (rand() % 10), 0.001f * (rand() % 10)), 
		glm::vec3(rand() / ((glm::float_t)RAND_MAX), rand() / ((glm::float_t)RAND_MAX), rand() / ((glm::float_t)RAND_MAX)), 
		glm::vec3(rand()/((glm::float_t)RAND_MAX), rand() / ((glm::float_t)RAND_MAX), rand() / ((glm::float_t)RAND_MAX)), 
		(glm::float_t)rand() / ((glm::float_t)RAND_MAX /360.0f));

	this->paddings.push_back(padding);
}

void Gravity::Update(Camera camera) {
	for (GLuint i = 0; i < paddings.size(); i++) {
		paddings[i].Update(camera);
	}
}

void Gravity::Draw(Camera camera, glm::mat4 projection, glm::mat4 view, Light light) {
	// Use cooresponding shader when setting uniforms/drawing objects

	if (displayObject == 0)
	{
		containerShader.Use();
		// Directional light
		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.ambient"), 0.2f, 0.2f, 0.2f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
		// Point light 1
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].position"), light.pointLights[0].position.x, light.pointLights[0].position.y, light.pointLights[0].position.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].ambient"), light.pointLights[0].ambient.x, light.pointLights[0].ambient.y, light.pointLights[0].ambient.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].diffuse"), light.pointLights[0].diffuse.x, light.pointLights[0].diffuse.y, light.pointLights[0].diffuse.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[0].specular"), light.pointLights[0].specular.x, light.pointLights[0].specular.y, light.pointLights[0].specular.z);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].constant"), light.pointLights[0].constant);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].linear"), light.pointLights[0].linear);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[0].quadratic"), light.pointLights[0].quadratic);
	// Point light 2
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].position"), light.pointLights[1].position.x, light.pointLights[1].position.y, light.pointLights[1].position.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].ambient"), light.pointLights[1].ambient.x, light.pointLights[1].ambient.y, light.pointLights[1].ambient.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].diffuse"), light.pointLights[1].diffuse.x, light.pointLights[1].diffuse.y, light.pointLights[1].diffuse.z);
	glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[1].specular"), light.pointLights[1].specular.x, light.pointLights[1].specular.y, light.pointLights[1].specular.z);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].constant"), light.pointLights[1].constant);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].linear"), light.pointLights[1].linear);
	glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[1].quadratic"), light.pointLights[1].quadratic);
		// Point light 3
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].position"), -4.0f, 2.0f, -12.0f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].linear"), 0.09);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[2].quadratic"), 0.032);
		// Point light 4
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].position"), 0.0f, 0.0f, -3.0f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
		glUniform3f(glGetUniformLocation(containerShader.Program, "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].linear"), 0.09);
		glUniform1f(glGetUniformLocation(containerShader.Program, "pointLights[3].quadratic"), 0.032);
		// SpotLight
		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.ambient"), light.spotLight.ambient.x, light.spotLight.ambient.y, light.spotLight.ambient.z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.diffuse"), light.spotLight.diffuse.x, light.spotLight.diffuse.y, light.spotLight.diffuse.z);
		glUniform3f(glGetUniformLocation(containerShader.Program, "spotLight.specular"), light.spotLight.specular.x, light.spotLight.specular.y, light.spotLight.specular.z);
		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.constant"), light.spotLight.constant);
		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.linear"), light.spotLight.linear);
		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.quadratic"), 0.032);
		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(containerShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		containerShader.Use();
		GLint viewPosLoc = glGetUniformLocation(containerShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(containerShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(containerShader.Program, "view");
		GLint projLoc = glGetUniformLocation(containerShader.Program, "projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		// Bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// Bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		// Draw 10 containers with the same VAO and VBO information; only their world space coordinates differ
		glBindVertexArray(this->VAO);
		for (GLuint i = 0; i < paddings.size(); i++)
		{
			paddings[i].Draw(containerShader, camera);
		}
		glBindVertexArray(0);
	}
	else if (displayObject == 1) {
		modelShader.Use();   // <-- Don't forget this one!
							 // Transformation matrices
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(glGetUniformLocation(modelShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

		// Set the lighting uniforms
		glUniform3f(glGetUniformLocation(modelShader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

		// Point light 1
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[0].position"), light.pointLights[0].position.x, light.pointLights[0].position.y, light.pointLights[0].position.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[0].ambient"), light.pointLights[0].ambient.x, light.pointLights[0].ambient.y, light.pointLights[0].ambient.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[0].diffuse"), light.pointLights[0].diffuse.x, light.pointLights[0].diffuse.y, light.pointLights[0].diffuse.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[0].specular"), light.pointLights[0].specular.x, light.pointLights[0].specular.y, light.pointLights[0].specular.z);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[0].constant"), light.pointLights[0].constant);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[0].linear"), light.pointLights[0].linear);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[0].quadratic"), light.pointLights[0].quadratic);
		// Point light 2
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[1].position"), light.pointLights[1].position.x, light.pointLights[1].position.y, light.pointLights[1].position.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[1].ambient"), light.pointLights[1].ambient.x, light.pointLights[1].ambient.y, light.pointLights[1].ambient.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[1].diffuse"), light.pointLights[1].diffuse.x, light.pointLights[1].diffuse.y, light.pointLights[1].diffuse.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "pointLights[1].specular"), light.pointLights[1].specular.x, light.pointLights[1].specular.y, light.pointLights[1].specular.z);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[1].constant"), light.pointLights[1].constant);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[1].linear"), light.pointLights[1].linear);
		glUniform1f(glGetUniformLocation(modelShader.Program, "pointLights[1].quadratic"), light.pointLights[1].quadratic);

		// SpotLight
		glUniform3f(glGetUniformLocation(modelShader.Program, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "spotLight.ambient"), light.spotLight.ambient.x, light.spotLight.ambient.y, light.spotLight.ambient.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "spotLight.diffuse"), light.spotLight.diffuse.x, light.spotLight.diffuse.y, light.spotLight.diffuse.z);
		glUniform3f(glGetUniformLocation(modelShader.Program, "spotLight.specular"), light.spotLight.specular.x, light.spotLight.specular.y, light.spotLight.specular.z);
		glUniform1f(glGetUniformLocation(modelShader.Program, "spotLight.constant"), light.spotLight.constant);
		glUniform1f(glGetUniformLocation(modelShader.Program, "spotLight.linear"), light.spotLight.linear);
		glUniform1f(glGetUniformLocation(modelShader.Program, "spotLight.quadratic"), 0.032);
		glUniform1f(glGetUniformLocation(modelShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
		glUniform1f(glGetUniformLocation(modelShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

		for (GLuint i = 0; i < paddings.size(); i++)
		{
			paddings[i].Draw(modelShader, model[0], camera, 0.5f);
		}
	}
}

void Gravity::NextModel() {
	displayObject++;
	displayObject = displayObject % 2;
}

void Gravity::RemoveAll() {
	this->paddings.clear();
}
