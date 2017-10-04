// Standard stuff


// Our files
#include "windowMgr.h"

// GLFW
#include "glfw3.h"

// GLOBALS
windowMgr winMgr;


GLFWwindow* window;
// Possible to create this window inside of windowMgr
// Then have a function to return a reference to the window 
// when necessary (input etc)

void Update()
{
	// While window is open...
	while (!glfwWindowShouldClose(window))
	{
		winMgr.Update(window);
	}
	
}


int main(int argc, char **argv)
{
	
	

	// Create window
	

	// Setup window
	winMgr.Init(window);

	// Run update loop
	Update();



	// On window close
	winMgr.CleanUp(window);
	return 0;
}