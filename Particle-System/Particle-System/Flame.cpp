#include "Flame.h"

Flame::Flame() {

}

Flame::Flame(glm::vec3 position, glm::vec3 velocity, GLuint lifetime) {
	this->position = position;
	this->velocity = velocity;
	this->lifetime = lifetime;
}

void Flame::Draw(Shader shader, Camera camera) {
	glm::mat4 model;
	model = glm::translate(model, this->position);
	glm::vec3 direction = camera.Position - glm::vec3(2.74f, -1.7f, 0.06f);
	glm::float_t a = (180.0f * glm::acos(glm::abs(glm::dot(glm::normalize(glm::vec3(0, 0, -1)), glm::normalize(direction)))) / glm::pi<glm::float_t>());
	if ((180.0f * glm::acos(glm::abs(glm::dot(glm::normalize(glm::vec3(0, 0, -1)), glm::normalize(direction)))) / glm::pi<glm::float_t>()) > 60.0f) {
		model = glm::rotate(model, 90.0f, glm::vec3(0, 1, 0));
	}
	
	model = glm::scale(model, glm::vec3(0.06f, 0.06f, 0.06f));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Flame::Update() {
	this->position = this->position + this->velocity;
	this->lifetime--;
}
	