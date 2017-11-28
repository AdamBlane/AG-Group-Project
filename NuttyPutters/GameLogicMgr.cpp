#include "glew_glfw.h"
#include "GameLogicMgr.h"

// Setup start of game HUD
void GameLogicMgr::Setup(int numPlayers)
{
	// Set number of players this game
	players = numPlayers;

	// Invoke UImgr to perform its setup
	uiMgr.Setup(players);

	int timer = glfwGetTime();
	// Act on number of players since logic is different for both game modes
	if (players == 1)
	{
		// Need a countdown timer
		// Need a stroke limit
		// Update stroke counter on fire
	} 
	else if (players == 2)
	{
		// Need elapsed timer
		// Update stroke counter on fire
	}
}

// Start tracking time for this game
void GameLogicMgr::StartGameClock()
{
	// This marks the start time
	startTime = glfwGetTime();
}

// Called after a player fired a shot
// Checks against stroke limit if this is 1 player mode
// Updates UI to refelct increase to strokeCounter
void GameLogicMgr::PlayerFired(int playerIndex, Player &player)
{
	// Is this a 1 player game? 
	if (players == 1)
	{
		// If so, need to check for fail condition (no more shots allowed)
		// TODO

		// Update UI - tell it which player to update for and its stroke value
		uiMgr.UpdateStrokeCounter(playerIndex, player.strokeCounter);
	}
	else if (players == 2)
	{

		// Update UI
		uiMgr.UpdateStrokeCounter(playerIndex, player.strokeCounter);
	}

}


// Keep clocks ticking...
void GameLogicMgr::Update()
{
	// Update elapsed timer clock
	// Time from current subtract start time
	lastFrameTime = elapsedTime;
	elapsedTime = glfwGetTime() - startTime;
	
	// Only update the UI every second
	if (elapsedTime > lastFrameTime)
	{
		
	}
}


