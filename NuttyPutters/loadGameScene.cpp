#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }

// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow* win)
{
	// Load images into grid
	cout << "Load Game Screen" << endl;

	// Read all saved seeds
	ifstream saves("saves.csv");

	// Read all saved games as strings
	while (!saves.eof())
	{
		string line;
		getline(saves, line);
		seeds.push_back(line); // store in seeds list
	}

}

// Main loop
void loadGameScene::Loop(GLFWwindow* win)
{
	// Input
	Input(win);

	// Render
	Render(win);


}

// Act on input
void loadGameScene::Input(GLFWwindow* win)
{
	// B goes back to main menu screen
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

	// MENU NAVIGATION
	// Go back/down an item
	if (glfwGetKey(win, GLFW_KEY_LEFT))
	{
		leftPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT))
	{
		// Only if left was just released...
		if (leftPressed)
		{
			// Reduce current seed count if not at min
			if (currentSeed > 0)
			{
				currentSeed--;
				cout << "Choice " << currentSeed << ": " << seeds.at(currentSeed) << endl;
			}
			leftPressed = false;
		}
	}

	// Go up/forward an item
	if (glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		rightPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		if (rightPressed)
		{
			// Increment current seed count if not at max
			if (currentSeed < seeds.size() - 1)
			{
				currentSeed++;
				cout << "Choice " << currentSeed << ": " << seeds.at(currentSeed) << endl;
			}
			rightPressed = false;
		}

	}
	// Select this level to load
	if (glfwGetKey(win, GLFW_KEY_ENTER))
	{
		// Current seed is index of seeds list, send as optional param
		windowMgr::getInstance()->sceneManager.changeScene(6, 12,seeds.at(currentSeed)); // 12 is mandatory course lenght (to be disregarded dw)
	}
	
}

// Draw stuff
void loadGameScene::Render(GLFWwindow* win)
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
