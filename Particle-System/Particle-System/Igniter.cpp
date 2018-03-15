#include "Igniter.h"

Igniter::Igniter() {

}

Igniter::Igniter(glm::vec3 initPos, GLfloat radius, glm::vec3 initVelocity) {
	this->initPos = initPos;
	this->initVelocity = initVelocity;
	this->radius = radius;
	this->distribution = normal_distribution<GLfloat>(0.5f, 0.1f);

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	GLfloat vertices[] = {
		// Positions          // Normals           // Texture Coords
		-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, 0.0f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	};

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

	this->shader = Shader("../assets/flame.vert", "../assets/flame.frag");

	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object
											// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load, create texture and generate mipmaps
	int width, height, nrComponents;
	unsigned char* image = SOIL_load_image("../assets/fire.png", &width, &height, &nrComponents, 0);
	GLenum format;
	if (nrComponents == 1)
		format = GL_RED;
	else if (nrComponents == 3)
		format = GL_RGB;
	else if (nrComponents == 4)
		format = GL_RGBA;
	
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Igniter::Emit() {
	for (GLuint i = 0; i < 6; i++) {
		GLfloat r = this->distribution(generator);
		rand();
		glm::float_t ran = rand() / glm::float_t(RAND_MAX / 100);
		glm::vec3 position = this->initPos + glm::vec3(sin(ran) * (r - this->radius), 0, cos(ran) * (r - this->radius));
		glm::vec3 velocity = this->initVelocity;
		this->flames.push_back(Flame(position, velocity, GLuint(12 / (abs(r - radius) + 0.1)) + rand()/(RAND_MAX/(2.5/(abs(r - radius)+ 0.09)))));
	}
}

void Igniter::Draw(Camera camera,glm::mat4 projection, glm::mat4 view) {
	//https://stackoverflow.com/questions/33272502/how-to-handle-opengl-additive-blending-and-depth-test-with-particles-and-deeper
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	this->shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->texture);
	glUniform1i(glGetUniformLocation(this->shader.Program, "ourTexture"), 0);
	glBindVertexArray(this->VAO);
	for (GLint i = 0; i < this->flames.size(); i++) {
		this->flames[i].Draw(this->shader, camera);
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
}

void Igniter::Update() {
	for (vector<Flame>::iterator it = this->flames.begin(); it != this->flames.end();) {
		it->Update();
		if (it->lifetime == 0) {
			it = this->flames.erase(it);
		}
		else {
			it++;
		}
	}
}

void Igniter::Blow(Camera camera) {
	if (glm::distance(camera.Position, initPos) > 3.0f) {
		return;
	}

	for (GLuint i = 0; i < flames.size(); i++) {
		flames[i].velocity.x += rand() / ((glm::float_t) RAND_MAX) * glm::normalize(camera.Front).x * 0.01f;
		flames[i].velocity.z += rand() / ((glm::float_t) RAND_MAX) * glm::normalize(camera.Front).z * 0.01f;
	}
}