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
	win = glfwCreateWindow(1600, 900, "Test", NULL, NULL);

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
		// Exit game
		case 0:
			CleanUp();
			break;
		// Start scene
		case 1:
			// Setup scene (key callbacks etc)
			sceneManager.startScene.Init(win);
			// Draw content
			sceneManager.startScene.screenContent(win);			
			break;
		// Player Select scene
		case 2:
			// Setup scene
			sceneManager.playerSelectScene.Init(win);
			// Draw content
			sceneManager.playerSelectScene.screenContent(win);
			break;
		// Load Game scene
		case 3:
			// Setup scene
			sceneManager.loadGameScene.Init(win);
			// Draw content
			sceneManager.loadGameScene.screenContent(win);
			break;
		// Highscore scene
		case 4:
			// Setup
			sceneManager.highscoreScene.Init(win);
			// Draw content
			sceneManager.highscoreScene.screenContent(win);
			break;
		// Options scene
		case 5:
			// Setup
			sceneManager.optionsScene.Init(win);
			// Draw content
			sceneManager.optionsScene.screenContent(win);
			break;
		// Game scene
		case 6:
			// Setup
			sceneManager.gameScene.Init(win);
			// Draw
			sceneManager.gameScene.checkPlayers(win);
			break;
		default: break;
		}
		// DEBUG - for testing, write our current scene
		//std::cout << sceneManager.curScene << std::endl;
	}

		
}

// On window close
void windowMgr::CleanUp()
{
	glfwDestroyWindow(win); // Runs when commented out - why?
	glfwTerminate();
	exit(EXIT_SUCCESS);
}



