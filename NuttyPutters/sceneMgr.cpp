

#include "sceneMgr.h"

// Constructor
sceneMgr::sceneMgr()
{
	// On construction, first scene is start menu
	curScene = 1;
}

void sceneMgr::changeScene(unsigned int newScene)
{
	// Change current scene tracker to new scene
	curScene = newScene;
}

// Returns current scene number
unsigned int sceneMgr::getScene()
{
	return curScene;
}
