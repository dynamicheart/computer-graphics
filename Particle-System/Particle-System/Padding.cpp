
#include "Padding.h"

Padding::Padding(glm::vec3 position, glm::vec3 velocity, glm::vec3 scale, glm::vec3 axis, glm::float_t angle){
	this->position = position;
	this->velocity = velocity;
	this->scale = scale;
	this->axis = axis;
	this->angle = angle;
}

void Padding::Draw(Shader shader, Camera camera) {
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model = glm::rotate(model, this->angle, this->axis);
	//model = glm::scale(model, this->scale);
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Padding::Draw(Shader shader, Model ourModel, Camera camera, glm::float_t scale) {
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model = glm::rotate(model, this->angle, this->axis);
	//model = glm::scale(model, this->scale);
	model = glm::scale(model, glm::vec3(scale));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	ourModel.DrawAutoDefault(shader);
}

void Padding::DrawNoTexture(Shader shader, Model ourModel, Camera camera, glm::float_t scale) {
	glm::mat4 model;
	model = glm::translate(model, this->position);
	model = glm::rotate(model, this->angle, this->axis);
	//model = glm::scale(model, this->scale);
	model = glm::scale(model, glm::vec3(scale));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	ourModel.DrawNoTexture(shader);
}


void Padding::Update(Camera camera) {
	this->position = this->position + this->velocity;
	this->angle += rand() / ((glm::float_t(RAND_MAX) * 30.0f));
	this->velocity += 0.0001f * (camera.Position - this->position);
}