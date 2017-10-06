#pragma once

#include <string>


class sceneMgr {
public:
	// Make int so as to use switch in winMgr.update
	unsigned int curScene;

	// Constructor
	sceneMgr();
	// Deconstructor
	~sceneMgr();


	void changeScene(unsigned int newScene);
	unsigned int getScene();
};