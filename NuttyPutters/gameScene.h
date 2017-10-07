#pragma once

// GLFW
#include "glfw3.h"

class gameScene
{
public:
	// Default constructor
	gameScene();
	// Deconstructor
	~gameScene();

	// Track number of players for this game
	unsigned int playerCount;

	// Set player Count
	void setPlayers(unsigned int players);
	

	// Check player count, draw accordingly
	void checkPlayers(GLFWwindow* win);
	// Draw stuff for 1 player
	void screenContent1P(GLFWwindow* win);
	// Draw for 2 players
	void screenContent2P(GLFWwindow* win);


	// Input
	static void key_callbacks(GLFWwindow* win, int key, int scancode, int action, int mods);
	// Setup scene
	void Init(GLFWwindow* win);
};