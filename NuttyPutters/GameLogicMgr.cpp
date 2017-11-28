#include "glew_glfw.h"
#include "GameLogicMgr.h"

// Setup start of game HUD
void GameLogicMgr::Setup(int numPlayers, vec3 endHolePos)
{
	// Set number of players this game
	players = numPlayers;

	// Invoke UImgr to perform its setup
	if (players == 1)
	{
		uiMgr.p1Setup();
	}
	else if (players == 2)
	{
		uiMgr.p2Setup(endHolePos);
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
	// Only allows for 2 digits of stroke count
	if (player.strokeCounter < 100)
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
		if (players == 1)
		{
			uiMgr.UpdateHUDClock(elapsedTime);
		}
		else if (players == 2)
		{
			uiMgr.UpdateWorldClock(elapsedTime);
		}
		
	}
}


