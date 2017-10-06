#pragma once

#include <string>


class sceneMgr {
public:
	
	unsigned int curScene;

	sceneMgr();
	void changeScene(unsigned int newScene);
	unsigned int getScene();
};