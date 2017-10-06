
#include "windowMgr.h"
#include "secondScene.h"

#include "glfw3.h"

// Basic constructor
secondScene::secondScene()
{
}


// Draw stuff
void secondScene::screenContent(GLFWwindow * win)
{
	float ratio;
	int width, height;

	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

	glBegin(GL_TRIANGLES);
	glColor3f(0.f, 1.f, 0.f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();


	glfwSwapBuffers(win);
	glfwPollEvents();
}


// Input
void secondScene::backScene_callback(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// Tell windowMgr that we need to move to next scene
		//parent->sceneManager.changeScene(2);
		//ChangeScene(2);
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}
}

// Setup; add key callbacks
void secondScene::Init(GLFWwindow * win)
{
	glfwSetKeyCallback(win, backScene_callback);
}
