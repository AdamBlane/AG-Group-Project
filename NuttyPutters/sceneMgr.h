#pragma once
// Externals
#include <string>
// Internals
#include "startScene.h"
#include "playerSelectScene.h"
#include "loadGameScene.h"
#include "highscoreScene.h"
#include "optionsScene.h"
#include "gameScene.h"
#include "glfw3.h"

class sceneMgr {
public:
	// Use int for switch in winMgr.update
	unsigned int curScene;

	// Constructor
	sceneMgr();
	// Deconstructor
	~sceneMgr();

	// Scenes
	startScene startScene; //1
	playerSelectScene playerSelectScene; //2
	loadGameScene loadGameScene; //3
	highscoreScene highscoreScene; //4
	optionsScene optionsScene; //5
	gameScene gameScene; //6

	// Scene get/set; optional param: difficulty via course size, load game seed string
	void changeScene(unsigned int newScene, int courseLength = 12, string seed = "seed"); 
	unsigned int getScene() { return curScene; }


};