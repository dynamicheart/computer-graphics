#include "Camp.h"

Camp::Camp() {
	this->shader = Shader("../assets/model.vert", "../assets/model.frag");
	this->model = Model("../assets/campfire/campfire OBJ.obj");
}

void Camp::Draw(Camera camera, glm::mat4 projection, glm::mat4 view, Light light){
	this->shader.Use();   // <-- Don't forget this one!
						 // Transformation matrices
	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

	// Set the lighting uniforms
	glUniform3f(glGetUniformLocation(this->shader.Program, "viewPos"), camera.Position.x, camera.Position.y, camera.Position.z);

	// Point light 1
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[0].position"), light.pointLights[0].position.x, light.pointLights[0].position.y, light.pointLights[0].position.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[0].ambient"), light.pointLights[0].ambient.x, light.pointLights[0].ambient.y, light.pointLights[0].ambient.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[0].diffuse"), light.pointLights[0].diffuse.x, light.pointLights[0].diffuse.y, light.pointLights[0].diffuse.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[0].specular"), light.pointLights[0].specular.x, light.pointLights[0].specular.y, light.pointLights[0].specular.z);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[0].constant"), light.pointLights[0].constant);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[0].linear"), light.pointLights[0].linear);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[0].quadratic"), light.pointLights[0].quadratic);
	// Point light 2
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[1].position"), light.pointLights[1].position.x, light.pointLights[1].position.y, light.pointLights[1].position.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[1].ambient"), light.pointLights[1].ambient.x, light.pointLights[1].ambient.y, light.pointLights[1].ambient.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[1].diffuse"), light.pointLights[1].diffuse.x, light.pointLights[1].diffuse.y, light.pointLights[1].diffuse.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "pointLights[1].specular"), light.pointLights[1].specular.x, light.pointLights[1].specular.y, light.pointLights[1].specular.z);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[1].constant"), light.pointLights[1].constant);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[1].linear"), light.pointLights[1].linear);
	glUniform1f(glGetUniformLocation(this->shader.Program, "pointLights[1].quadratic"), light.pointLights[1].quadratic);
	// SpotLight
	glUniform3f(glGetUniformLocation(this->shader.Program, "spotLight.position"), camera.Position.x, camera.Position.y, camera.Position.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "spotLight.direction"), camera.Front.x, camera.Front.y, camera.Front.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "spotLight.ambient"), light.spotLight.ambient.x, light.spotLight.ambient.y, light.spotLight.ambient.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "spotLight.diffuse"), light.spotLight.diffuse.x, light.spotLight.diffuse.y, light.spotLight.diffuse.z);
	glUniform3f(glGetUniformLocation(this->shader.Program, "spotLight.specular"), light.spotLight.specular.x, light.spotLight.specular.y, light.spotLight.specular.z);
	glUniform1f(glGetUniformLocation(this->shader.Program, "spotLight.constant"), light.spotLight.constant);
	glUniform1f(glGetUniformLocation(this->shader.Program, "spotLight.linear"), light.spotLight.linear);
	glUniform1f(glGetUniformLocation(this->shader.Program, "spotLight.quadratic"), 0.032);
	glUniform1f(glGetUniformLocation(this->shader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
	glUniform1f(glGetUniformLocation(this->shader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));

	// Draw the loaded model
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// It's a bit too big for our scene, so scale it down

	glUniformMatrix4fv(glGetUniformLocation(this->shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
	this->model.DrawAutoDefault(this->shader);

}
