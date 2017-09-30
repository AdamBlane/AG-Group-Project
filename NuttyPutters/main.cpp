

#include "windowMgr.h"

// GLFW
#include "glfw3.h"





int main(int argc, char **argv)
{
	// Initialise window manager
	windowMgr winMgr;
	// Create window
	GLFWwindow* window;
	// Setup window
	winMgr.Init(window);

	winMgr.Update(window);

	winMgr.CleanUp(window);

	return 0;
}