#include "stdafx.h"
#include"AllCamera.h"

using namespace AllCamera;
using namespace std;
using namespace glm;

free_camera cam;

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}


int main(int argc, char **argv)
{
	cam.set_Posistion(glm::vec3(0.0f, 10.0f, 0.0f));
	cam.set_Target(vec3(0.0f, 0.0f, 0.0f));
	auto aspect = static_cast<float>(640 / 480);
	cam.set_projection(quarter_pi<float>(), aspect, 2.414f, 1000.0f);

	// Create window
	GLFWwindow* window;
	// Set error callbackc function
	glfwSetErrorCallback(error_callback);
	// Initialise GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Initialise the window, check for error after
	window = glfwCreateWindow(640, 480, "Triangle Simulator 2017", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Assign context
	glfwMakeContextCurrent(window);
	// Assign key callback function for close on ESC
	glfwSetKeyCallback(window, key_callback);
	// While window is not to be closed...
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);



    return 0;
}