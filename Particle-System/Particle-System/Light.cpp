#include "Light.h"

Light::Light() {
	dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);
	dirLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	dirLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
	dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);

	PointLight pointLight0;
	pointLight0.position = glm::vec3(0.7f, 0.2f, 2.0f);
	pointLight0.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight0.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	pointLight0.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight0.constant = 1.0f;
	pointLight0.linear = 0.09f;
	pointLight0.quadratic = 0.032;
	this->pointLights.push_back(pointLight0);

	PointLight pointLight1;
	pointLight1.position = glm::vec3(2.74f, -1.4f, 0.06f);
	pointLight1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	pointLight1.diffuse = glm::vec3(0.8f, 0.1f, 0.1f);
	pointLight1.specular = glm::vec3(1.0f, 0.1f, 0.1f);
	pointLight1.constant = 1.0f;
	pointLight1.linear = 0.09f;
	pointLight1.quadratic = 0.032;
	this->pointLights.push_back(pointLight1);

	spotLight.postion = glm::vec3(0);
	spotLight.direction = glm::vec3(0);
	spotLight.ambient = glm::vec3(0);
	spotLight.diffuse = glm::vec3(1.0f);
	spotLight.specular = glm::vec3(1.0f);
	spotLight.constant = 1.0f;
	spotLight.linear = 0.09f;
	spotLight.quadratic = 0.032;
	spotLight.cutOff = glm::cos(glm::radians(12.5f));
	spotLight.outerCutOff = glm::cos(glm::radians(15.0f));

	level = 0;
}

void Light::Update(Camera camera) {
	spotLight.postion = camera.Position;
	spotLight.direction = camera.Front;
	pointLights[0].position.x = 1.0f + sin(glfwGetTime()) * 2.0f;
	pointLights[0].position.y = sin(glfwGetTime() / 2.0f) * 1.0f;
	pointLights[1].position.x = 2.74f + sin(rand()/((glm::float_t)RAND_MAX/100)) * 0.05f;
	pointLights[1].position.z = 0.06f + sin(rand() / ((glm::float_t)RAND_MAX / 100)) * 0.05f;
	pointLights[1].position.y = -1.4f + sin(rand() / ((glm::float_t)RAND_MAX / 100)) * 0.05f;
}

void Light::SwitchDirLight() {
	if (dirLight.ambient.x != 0) {
		dirLight.ambient = glm::vec3(0);
		dirLight.diffuse = glm::vec3(0);
		dirLight.specular = glm::vec3(0);
	}
	else {
		dirLight.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		dirLight.diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		dirLight.specular = glm::vec3(0.5f, 0.5f, 0.5f);
	}
}

void Light::SwitchSpotLight() {
	if (spotLight.diffuse.x != 0) {
		spotLight.diffuse = glm::vec3(0);
		spotLight.specular = glm::vec3(0);
	}
	else {
		spotLight.diffuse = glm::vec3(1.0f);
		spotLight.specular = glm::vec3(1.0f);
	}
}

void Light::SwitchPointLight() {
	if (pointLights[1].diffuse.x != 0) {
		pointLights[1].ambient = glm::vec3(0);
		pointLights[1].diffuse = glm::vec3(0);
		pointLights[1].specular = glm::vec3(0);
	}
	else {
		pointLights[1].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		pointLights[1].diffuse = glm::vec3(0.8f, 0.1f, 0.1f);
		pointLights[1].specular = glm::vec3(1.0f, 0.1f, 0.1f);
	}
	
}

void Light::NextLevelPointLight(GLuint index) {
	glm::vec3 pointLightColors[] = {
		glm::vec3(1.0f, 0.6f, 0.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(1.0f, 1.0, 0.0),
		glm::vec3(0.2f, 0.2f, 1.0f)
	};
	level++;
	level = level % 6;
	switch (level) {
	case 0:
		pointLights[0].ambient = glm::vec3(0.05f, 0.05f, 0.05f);
		pointLights[0].diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
		pointLights[0].specular = glm::vec3(1.0f, 1.0f, 1.0f);
		break;
	case 1:
		pointLights[0].ambient = pointLightColors[0] * 0.1f;
		pointLights[0].diffuse = pointLightColors[0];
		pointLights[0].specular = pointLightColors[0];
		break;
	case 2:
		pointLights[0].ambient = pointLightColors[1] * 0.1f;
		pointLights[0].diffuse = pointLightColors[1];
		pointLights[0].specular = pointLightColors[1];
		break;
	case 3:
		pointLights[0].ambient = pointLightColors[2] * 0.1f;
		pointLights[0].diffuse = pointLightColors[2];
		pointLights[0].specular = pointLightColors[2];
		break;
	case 4:
		pointLights[0].ambient = pointLightColors[3] * 0.1f;
		pointLights[0].diffuse = pointLightColors[3];
		pointLights[0].specular = pointLightColors[3];
		break;
	case 5:
		pointLights[0].ambient = glm::vec3(0);
		pointLights[0].diffuse = glm::vec3(0);
		pointLights[0].specular = glm::vec3(0);
		break;
	default:
		break;
	}
}
