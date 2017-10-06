// Standard stuff
#include <string>
#include <iostream>

// Our files
#include "windowMgr.h"

// GLFW
#include "glfw3.h"

using namespace std; 

// GLOBALS
windowMgr* winMgr; // Pointer to winMgr since it's a singleton




int main(int argc, char **argv)
{
	// Get singleton instance of windowMgr
	winMgr = windowMgr::getInstance();
	
	// Setup window
	winMgr->Init();

	// Run update loop
	winMgr->Update();

	// On window close
	winMgr->CleanUp();

	return 0;
}