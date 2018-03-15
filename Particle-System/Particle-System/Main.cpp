#include <iostream>
#include <cmath>
#include <random>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include <SOIL/SOIL.h>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "SmokeEmitter.h"
#include "Igniter.h"
#include "Skybox.h"
#include "Camp.h"
#include "Light.h"
#include "Gravity.h"


// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
Light light;
Igniter igniter;
SmokeEmitter smokeEmitter;
Gravity gravity;

bool stall = false;
bool turnOn = true;
int delay0 = 0, delay1 = 0;

GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool    keys[1024];

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

							// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Particle System", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, WIDTH, HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Build and compile our shader program
	Shader lampShader("../assets/lamp.vert", "../assets/lamp.frag");

	//SnowEmitter snowEmitter(glm::vec3(0, 10.0f, 0), glm::vec3(0, -0.001f, 0));
	igniter = Igniter(glm::vec3(2.74f, -1.7f, 0.06f), 0.5f, glm::vec3(0, 0.005f, 0));
	smokeEmitter = SmokeEmitter(glm::vec3(2.67f, -0.5f, 0.06f), 0.45f, glm::vec3(0, 0.005f, 0));
	gravity = Gravity(camera);
	Skybox skybox;
	Camp camp;

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		//// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		do_movement();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		light.Update(camera);

		skybox.Draw(camera, glm::mat4(glm::mat3(camera.GetViewMatrix())), glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f));

		camp.Draw(camera, glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f), camera.GetViewMatrix(), light);


		gravity.Draw(camera, glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f), camera.GetViewMatrix(), light);
		if (!stall) {
			gravity.Update(camera);
		}

		if (turnOn) {
			igniter.Emit();
		}
		
		igniter.Draw(camera, glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f), camera.GetViewMatrix());
		igniter.Update();

		if (turnOn) {
			if (delay0 >= 200) {
				smokeEmitter.Emit();
			}
			else {
				delay0++;
			}
			delay1 = 0;
		}
		else {
			if (delay1 <= 200) {
				smokeEmitter.Emit();
				delay1++;
			}
			delay0 = 0;
		}

		smokeEmitter.Draw(camera, glm::perspective(camera.Zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f), camera.GetViewMatrix());
		smokeEmitter.Update();

		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		light.NextLevelPointLight(0);
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		light.SwitchDirLight();
	}
	if (key == GLFW_KEY_F && action == GLFW_PRESS) {
		light.SwitchSpotLight();
	}
	if (key == GLFW_KEY_K && action == GLFW_PRESS) {
		igniter.Blow(camera);
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		gravity.Emit(camera);
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		gravity.RemoveAll();
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		stall = !stall;
	}
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		gravity.NextModel();
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS) {
		turnOn = !turnOn;
		light.SwitchPointLight();
	}
}

void do_movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
