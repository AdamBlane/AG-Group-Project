#include "playerSelect.h"
#include "windowMgr.h"

// Constructor
playerSelect::playerSelect() { }
// Deconstructor
playerSelect::~playerSelect() { }


// Draw stuff for this scene
void playerSelect::screenContent(GLFWwindow * win)
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
	glColor3f(0.f, 1.f, 1.f);
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
void playerSelect::key_callbacks(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	// Move back to start scene
	if (key == GLFW_KEY_B && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}
	// Move to game scene with 1 player
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		// Tell sceneManager's game how many players
		windowMgr::getInstance()->sceneManager.gameScene.setPlayers(1);
		// Move to game scene
		windowMgr::getInstance()->sceneManager.changeScene(6);
	}
	// Move back to game scene with 2 players
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		// Tell sceneManager's game how many players
		windowMgr::getInstance()->sceneManager.gameScene.setPlayers(2);
		// Move to game scene
		windowMgr::getInstance()->sceneManager.changeScene(6);
	}
}

// Setup scene; add callbacks
void playerSelect::Init(GLFWwindow * win)
{
	glfwSetKeyCallback(win, key_callbacks);
}
