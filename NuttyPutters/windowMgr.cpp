#include <iostream>

#include "glfw3.h"
#include "windowMgr.h"

/// windowMgr is a singleton class, accessed by all the scene files
/// It initialises and sets up the window, & contains the Update loop
/// On window close, it runs through closing steps
/// Called from main.cpp

// Private Constructor
windowMgr::windowMgr() { }
// Private Deconstructor
windowMgr::~windowMgr() { }


// Set instance to NULL initially, since it'll be created on demand in main
windowMgr* windowMgr::instance = NULL;

// Return windowMgr singleton instance
windowMgr* windowMgr::getInstance()
{
	// If it doesn't exist, create it
	if (instance == NULL)
		instance = new windowMgr();
	
	// Return created/existing instance
	return instance;
}

// Setup; GLFW stuff, creates window
GLFWwindow* windowMgr::Init()
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


	return win;
}

// Switches on current scene, calls on appropriate file to render/read input
void windowMgr::Update()
{		
	// While window is open...
	while (!glfwWindowShouldClose(win))
	{
		// Scene manager (property of winMgr) tracks game state
		switch (sceneManager.curScene)
		{
		// Start scene
		case 1:
			// Setup scene (key callbacks etc)
			startSceneMgr.Init(win);
			// Draw content
			startSceneMgr.screenContent(win);
			break;
		// Second scene
		case 2:
			// Setup scene
			secondSceneMgr.Init(win);
			// Draw content
			secondSceneMgr.screenContent(win);
		default: break;
		}
		// DEBUG - for testing, write our current scene
		std::cout << sceneManager.curScene << std::endl;
	}

		
}

// On window close
void windowMgr::CleanUp()
{
	glfwDestroyWindow(win); // Runs when commented out - why?
	glfwTerminate();
	exit(EXIT_SUCCESS);
}



