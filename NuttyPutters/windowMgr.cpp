#include <iostream>

#include "glfw3.h"
#include "windowMgr.h"



void windowMgr::EscKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}

// Setup; GLFW libraries, creates window
void windowMgr::Init(GLFWwindow* &win)
{
	// Initialise GLFW libraries
	if (!glfwInit())
		exit(EXIT_FAILURE);

	// Create window
	win = glfwCreateWindow(400, 400, "Test", NULL, NULL);

	// Check window was created successfully
	if (!win)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make window the current context
	glfwMakeContextCurrent(win);

	// Set key callbacks
	glfwSetKeyCallback(win, EscKeyCallback);
}

void windowMgr::Update(GLFWwindow* &win)
{
	while (!glfwWindowShouldClose(win))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(win, &width, &height);
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

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
}

void windowMgr::CleanUp(GLFWwindow* &win)
{
	//glfwDestroyWindow(win);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
