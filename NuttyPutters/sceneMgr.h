#pragma once

#include <string>
#include "startScene.h"
#include "playerSelect.h"
#include "loadGameScene.h"
#include "highscoreScene.h"
#include "optionsScene.h"


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
	playerSelect playerSelectScene; //2
	loadGameScene loadGameScene; //3
	highscoreScene highscoreScene; //4
	optionsScene optionsScene; //5

	void changeScene(unsigned int newScene);
	unsigned int getScene();
};