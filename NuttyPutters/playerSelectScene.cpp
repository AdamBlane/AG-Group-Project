#include "playerSelectScene.h"
#include "windowMgr.h"

// Constructor
playerSelectScene::playerSelectScene() { }
// Deconstructor
playerSelectScene::~playerSelectScene() { }


// Draw stuff for this scene
void playerSelectScene::Loop(GLFWwindow * win)
{
	// Input
	Input(win);

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

// Act on user input 
void playerSelectScene::Input(GLFWwindow* win)
{
	// Move back to start scene
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1); // This calls init for scene
	}
	// Move to game scene with 1 player
	if (glfwGetKey(win, GLFW_KEY_1))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(6, courseLength); // This calls init for scene
	}
	
	// TOOD - Have something affect course length here

}

// Setup scene; does nothing atm
void playerSelectScene::Init(GLFWwindow * win)
{
	// TODO
}
