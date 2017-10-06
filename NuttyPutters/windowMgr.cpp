#include <iostream>

#include "glfw3.h"
#include "windowMgr.h"

/// Window manager deals with initialisation of glfw libraries, creating the game window,
/// adds key callbacks and terminates window when done

// Close window on escape press - regardless of scene (don't want to keep this)
void windowMgr::EscKeyCallback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}

// Setup; GLFW libraries, creates window
void windowMgr::Init(GLFWwindow* &win)
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

	// Set general key callbacks
	glfwSetKeyCallback(win, EscKeyCallback);
}


// Switches on current scene, calls on appropriate file to render/read input
void windowMgr::Update(GLFWwindow* &win)
{			
	switch (sceneManager.curScene)
	{
	// Start screen
	case 1:
		// Draw content
		startSceneMgr.screenContent(win);
		// Setup key callbacks for input

		break;
	default: break;
	}
		
}

void windowMgr::CleanUp(GLFWwindow* &win)
{
	//glfwDestroyWindow(win);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

// Constructor - calls constructors for property classes
windowMgr::windowMgr()
{
	// Initialise start scene 
	startSceneMgr = startScene(*this);
}


