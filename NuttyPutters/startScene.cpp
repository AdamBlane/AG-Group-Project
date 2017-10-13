


#include "startScene.h"
#include "windowMgr.h"


/// Start scene contains all render and input data for this scene

// Default constructor
startScene::startScene() { }

// Deconstructor
startScene::~startScene() { }


// Draw stuff
void startScene::screenContent(GLFWwindow* win)
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
	//glColor3f(0.f, 1.f, 0.f);
	glVertex3f(0.6f, -0.4f, 0.f);
	//glColor3f(0.f, 0.f, 1.f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();

	glfwSwapBuffers(win);
	glfwPollEvents();

	
}

// Input
void startScene::key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	// Move to player select scene
	if (key == GLFW_KEY_P && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(2);
	}
	// Move to load game scene
	if (key == GLFW_KEY_L && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(3);
	}
	// Move to highscore scene
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(4);
	}
	// Move to options scene
	if (key == GLFW_KEY_O && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(5);
	}
	// Exit game
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(0);
	}
}



// Setup; add key callbacks
void startScene::Init(GLFWwindow* win)
{
	glfwSetKeyCallback(win, key_callbacks);

}


