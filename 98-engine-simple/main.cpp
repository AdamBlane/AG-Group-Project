#include <iostream>
#include "engine.h"
#include "entity_manager.h"
#include "physics_system.h"
#include "renderer.h"
#include "state_machine.h"
#include "engine_states.h"
#include "input_handler.h"
//
#include "glfw3.h"
#include <stdlib.h>
#include <stdio.h>


using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	//std::cout << key << std::endl;

	const GLfloat rotationSpeed = 10;

	// actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			rotationX -= rotationSpeed;
			break;
		case GLFW_KEY_DOWN:
			rotationX += rotationSpeed;
			break;
		case GLFW_KEY_RIGHT:
			rotationY += rotationSpeed;
			break;
		case GLFW_KEY_LEFT:
			rotationY -= rotationSpeed;
			break;
		}


	}
}

//old function
void createCubeOLD(GLfloat startPosX, GLfloat startPosY, GLfloat startPosZ, GLfloat edgeLength)
{

	GLfloat vertices[] =
	{
		// front face
		startPosX - edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // top right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ + edgeLength, // bottom right
		startPosX - edgeLength, startPosY - edgeLength, startPosZ + edgeLength, // bottom left

		// back face
		startPosX - edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // bottom right
		startPosX - edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // bottom left

		// left face
		startPosX - edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // top left
		startPosX - edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX - edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // bottom right
		startPosX - edgeLength, startPosY - edgeLength, startPosZ + edgeLength, // bottom left

		// right face
		startPosX + edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ + edgeLength, // bottom left

		// top face
		startPosX - edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // top left
		startPosX - edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY + edgeLength, startPosZ + edgeLength, // bottom left

		// bottom face
		startPosX - edgeLength, startPosY - edgeLength, startPosZ + edgeLength, // top left
		startPosX - edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY - edgeLength, startPosZ + edgeLength  // bottom left
	};

	GLfloat colour[] =
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(colour[0], colour[1], colour[2] );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}


void createCube(GLfloat startPosX, GLfloat startPosY, GLfloat startPosZ, GLfloat edgeLength)
{

	GLfloat vertices[] =
	{
		// front face
		startPosX, startPosY + edgeLength, startPosZ, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // top right
		startPosX + edgeLength, startPosY, startPosZ, // bottom right
		startPosX, startPosY, startPosZ, // bottom left

		// back face
		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
		startPosX, startPosY, startPosZ - edgeLength, // bottom left

		// left face
		startPosX, startPosY + edgeLength, startPosZ, // top left
		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX, startPosY, startPosZ - edgeLength, // bottom right
		startPosX, startPosY, startPosZ, // bottom left

		// right face
		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // top left
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY, startPosZ, // bottom left

		// top face
		startPosX, startPosY + edgeLength, startPosZ, // top left
		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // bottom left

		// bottom face
		startPosX, startPosY, startPosZ, // top left
		startPosX, startPosY, startPosZ - edgeLength, // top right
		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
		startPosX + edgeLength, startPosY, startPosZ  // bottom left
	};

	GLfloat colour[] =
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(colour[0], colour[1], colour[2] );
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void createCuboid(GLfloat startPosX, GLfloat startPosY, GLfloat startPosZ, GLfloat side1, GLfloat side2)
{

	GLfloat vertices[] =
	{
		// front face
		startPosX, startPosY + side1, startPosZ, // top left
		startPosX + side2, startPosY + side1, startPosZ, // top right
		startPosX + side2, startPosY, startPosZ, // bottom right
		startPosX, startPosY, startPosZ, // bottom left

		// back face
		startPosX, startPosY + side1, startPosZ - side2, // top left
		startPosX + side2, startPosY + side1, startPosZ - side2, // top right
		startPosX + side2, startPosY, startPosZ - side2, // bottom right
		startPosX, startPosY, startPosZ - side2, // bottom left

		// left face
		startPosX, startPosY + side1, startPosZ, // top left
		startPosX, startPosY + side1, startPosZ - side2, // top right
		startPosX, startPosY, startPosZ - side2, // bottom right
		startPosX, startPosY, startPosZ, // bottom left

		// right face
		startPosX + side2, startPosY + side1, startPosZ, // top left
		startPosX + side2, startPosY + side1, startPosZ - side2, // top right
		startPosX + side2, startPosY, startPosZ - side2, // bottom right
		startPosX + side2, startPosY, startPosZ, // bottom left

		// top face
		startPosX, startPosY + side1, startPosZ, // top left
		startPosX, startPosY + side1, startPosZ - side2, // top right
		startPosX + side2, startPosY + side1, startPosZ - side2, // bottom right
		startPosX + side2, startPosY + side1, startPosZ, // bottom left

		// bottom face
		startPosX, startPosY, startPosZ, // top left
		startPosX, startPosY, startPosZ - side2, // top right
		startPosX + side2, startPosY, startPosZ - side2, // bottom right
		startPosX + side2, startPosY, startPosZ  // bottom left

	};

	GLfloat colour[] =
	{
		255, 0, 0,
		0, 255, 0,
		0, 0, 255
	};

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(colour[0], colour[2], colour[2]);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);
}

int main(int argc, char **argv)
{

	// Create window
	GLFWwindow* window;
	// Set error callbackc function
	glfwSetErrorCallback(error_callback);
	// Initialise GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Initialise the window, check for error after
	window = glfwCreateWindow(WIDTH, HEIGHT, "Triangle Simulator 2017", NULL, NULL);
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Assign context
	glfwMakeContextCurrent(window);
	// Assign key callback function for close on ESC
	glfwSetKeyCallback(window, keyCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	// While window is not to be closed...
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, WIDTH, HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WIDTH, 0, HEIGHT, 0, 1000);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		//glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

		//glBegin(GL_TRIANGLES);
		//glColor3f(1.f, 0.f, 0.f);
		//glVertex3f(-0.6f, -0.4f, 0.f);
		//glColor3f(0.f, 1.f, 0.f);
		//glVertex3f(0.6f, -0.4f, 0.f);
		//glColor3f(0.f, 0.f, 1.f);
		//glVertex3f(0.f, 0.6f, 0.f);
		//glEnd();

		glPushMatrix();
		glTranslatef(WIDTH / 2, HEIGHT / 2, -500);
		glRotatef(rotationX, 1, 0, 0);
		glRotatef(rotationY, 0, 1, 0);
		glTranslatef(-WIDTH / 2, -HEIGHT / 2, 500);

		createCuboid(WIDTH / 2, HEIGHT / 2, -500, 2, 100);

		createCuboid((WIDTH / 2) - 150, HEIGHT / 2, -500, 2, 100);

		glPopMatrix();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);



	return 0;
}