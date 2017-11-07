#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }


// Draw stuff
void loadGameScene::Loop(GLFWwindow * win)
{
	// Input
	Input(win);


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

// Act on input
void loadGameScene::Input(GLFWwindow * win)
{
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

	// Load a level (picks first for now)
	if (glfwGetKey(win, GLFW_KEY_L))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(6); // Call init...
	}


}



// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow * win)
{
	// Open up file for reading
	ifstream saves("saves.csv");
	// To hold all read lines
	vector<string> lines;
	// Read all saved games
	while (!saves.eof())
	{
		string s;
		getline(saves, s);
		lines.push_back(s);
	}
	// Display in console for now
	for (auto &l : lines)
		cout << l << endl;



}
