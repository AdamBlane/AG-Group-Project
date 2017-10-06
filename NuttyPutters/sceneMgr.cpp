
#include "sceneMgr.h"

/// Scene Manager is a property of windowMgr
/// It tracks gamestate, called by scene files on particular input

// Constructor
sceneMgr::sceneMgr()
{
	// On construction, first scene is start menu
	curScene = 1;
}

// Deconstructor
sceneMgr::~sceneMgr() { }

// Update game state to new scene
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
