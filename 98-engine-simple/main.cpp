#include "geometry_builder.h"
#include "tile.h"
#include <iostream>
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"
//
#include "glfw3.h"
#include <stdlib.h>
#include <stdio.h>


using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;

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

	const GLfloat rotationSpeed = 0.1;

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
		case GLFW_KEY_A:
			rotationZ -= rotationSpeed;
			break;
		case GLFW_KEY_D:
			rotationZ += rotationSpeed;
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


//void createCube(GLfloat startPosX, GLfloat startPosY, GLfloat startPosZ, GLfloat edgeLength)
//{
//
//	GLfloat vertices[] =
//	{
//		// front face
//		startPosX, startPosY + edgeLength, startPosZ, // top left
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // top right
//		startPosX + edgeLength, startPosY, startPosZ, // bottom right
//		startPosX, startPosY, startPosZ, // bottom left
//
//		// back face
//		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top left
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
//		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
//		startPosX, startPosY, startPosZ - edgeLength, // bottom left
//
//		// left face
//		startPosX, startPosY + edgeLength, startPosZ, // top left
//		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top right
//		startPosX, startPosY, startPosZ - edgeLength, // bottom right
//		startPosX, startPosY, startPosZ, // bottom left
//
//		// right face
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // top left
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // top right
//		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
//		startPosX + edgeLength, startPosY, startPosZ, // bottom left
//
//		// top face
//		startPosX, startPosY + edgeLength, startPosZ, // top left
//		startPosX, startPosY + edgeLength, startPosZ - edgeLength, // top right
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ - edgeLength, // bottom right
//		startPosX + edgeLength, startPosY + edgeLength, startPosZ, // bottom left
//
//		// bottom face
//		startPosX, startPosY, startPosZ, // top left
//		startPosX, startPosY, startPosZ - edgeLength, // top right
//		startPosX + edgeLength, startPosY, startPosZ - edgeLength, // bottom right
//		startPosX + edgeLength, startPosY, startPosZ  // bottom left
//	};
//
//	GLfloat colour[] =
//	{
//		255, 0, 0,
//		0, 255, 0,
//		0, 0, 255
//	};
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glColor3f(colour[0], colour[1], colour[2] );
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//
//	glDrawArrays(GL_QUADS, 0, 24);
//
//	glDisableClientState(GL_VERTEX_ARRAY);
//}
//
//void createCuboid(GLfloat startPosX, GLfloat startPosY, GLfloat startPosZ, GLfloat side1, GLfloat side2)
//{
//
//	GLfloat vertices[] =
//	{
//		// front face
//		startPosX, startPosY + side1, startPosZ, // top left
//		startPosX + side2, startPosY + side1, startPosZ, // top right
//		startPosX + side2, startPosY, startPosZ, // bottom right
//		startPosX, startPosY, startPosZ, // bottom left
//
//		// back face
//		startPosX, startPosY + side1, startPosZ - side2, // top left
//		startPosX + side2, startPosY + side1, startPosZ - side2, // top right
//		startPosX + side2, startPosY, startPosZ - side2, // bottom right
//		startPosX, startPosY, startPosZ - side2, // bottom left
//
//		// left face
//		startPosX, startPosY + side1, startPosZ, // top left
//		startPosX, startPosY + side1, startPosZ - side2, // top right
//		startPosX, startPosY, startPosZ - side2, // bottom right
//		startPosX, startPosY, startPosZ, // bottom left
//
//		// right face
//		startPosX + side2, startPosY + side1, startPosZ, // top left
//		startPosX + side2, startPosY + side1, startPosZ - side2, // top right
//		startPosX + side2, startPosY, startPosZ - side2, // bottom right
//		startPosX + side2, startPosY, startPosZ, // bottom left
//
//		// top face
//		startPosX, startPosY + side1, startPosZ, // top left
//		startPosX, startPosY + side1, startPosZ - side2, // top right
//		startPosX + side2, startPosY + side1, startPosZ - side2, // bottom right
//		startPosX + side2, startPosY + side1, startPosZ, // bottom left
//
//		// bottom face
//		startPosX, startPosY, startPosZ, // top left
//		startPosX, startPosY, startPosZ - side2, // top right
//		startPosX + side2, startPosY, startPosZ - side2, // bottom right
//		startPosX + side2, startPosY, startPosZ  // bottom left
//
//	};
//
//	GLfloat colour[] =
//	{
//		255, 0, 0,
//		0, 255, 0,
//		0, 0, 255
//	};
//
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glColor3f(colour[0], colour[2], colour[2]);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glVertexPointer(3, GL_FLOAT, 0, vertices);
//
//	glDrawArrays(GL_QUADS, 0, 24);
//
//	glDisableClientState(GL_VERTEX_ARRAY);
//}


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
	window = glfwCreateWindow(1280, 720, "Triangle Simulator 2017", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Assign context
	glfwMakeContextCurrent(window);
	// Assign key callback function for close on ESC
	glfwSetKeyCallback(window, keyCallback);

	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		std::cout << "Glew failed to initialize!" << std::endl;
	}

	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//Mesh cube(Mesh::CUBOID);

	//cube.size(0.1, 0.1, 0.5);

	//cube.createMesh();

	vec3 measures = vec3(0.2f, 0.4f, 0.1f);
	vec3 tilePos = vec3(0.0f, 0.0f, 0.0f);

	Mesh floor(Mesh::CUBOID);
	floor.setPosition(tilePos.x, tilePos.y, tilePos.z);
	floor.size(measures.x, measures.y, measures.z);
	floor.createMesh();

	//Mesh border1(Mesh::CUBOID);
	//border1.setPosition(tilePos.x, tilePos.y + floor.getSize().x, tilePos.z);
	//border1.size(0.1f, 0.1f, 1.0f);
	//border1.createMesh();

	//Mesh border2(Mesh::CUBOID);
	//border2.setPosition(tilePos.x + (floor.getSize().y - 0.1f), tilePos.y + floor.getSize().x, tilePos.z);
	//border2.size(0.1f, 0.1f, 1.0f);
	//border2.createMesh();

	//Mesh boxMesh(&(*box));

	// Import a shader
	Shader colourShader("..\\NuttyPutters\\include\\shaders\\colorShader");
	Shader textureShader("..\\NuttyPutters\\include\\shaders\\textureShader");
	Texture textureWood("..\\NuttyPutters\\include\\res\\img\\wood.jpg");

	Camera camera(glm::vec3(0, 2, 2), 70.0f, (float)1600 / (float)900, 0.01f, 1000.0f);

	Transform transform;

	float counter = 0.0f;

	// While window is not to be closed...
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind shader
		//colourShader.Bind();
		textureShader.Bind();
		// Bind Shader -  to unit 0
		textureWood.Bind(0);

		//transform.getPos().x = sinf(counter);
		transform.getRot().x = rotationX;
		transform.getRot().y = rotationY;
		transform.getRot().z = rotationZ;

		textureShader.Update(transform, camera);

		//cube.Draw();

		floor.Draw();
		//border1.Draw();
		//border2.Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();

		counter += 0.01f;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);



	return 0;
}