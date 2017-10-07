
#include "windowMgr.h"
#include "loadGameScene.h"

// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }


// Draw stuff
void loadGameScene::screenContent(GLFWwindow * win)
{
	float ratio;
	int width, height;

	// Get size of window in case resized
	glfwGetFramebufferSize(win, &width, &height);
	ratio = width / (float)height;
	// Make viewport match window size
	// 0,0 = bottom left corner, takes half of screen sideways
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
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();
}

// Input - go back to main menu
void loadGameScene::key_callbacks(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}
}

// Setup scene; add key callbacks
void loadGameScene::Init(GLFWwindow * win)
{
	glfwSetKeyCallback(win, key_callbacks);
}
