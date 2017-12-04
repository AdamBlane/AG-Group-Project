#pragma once


#include "UI.h"
#include "Player.h"
/// This handles general gameplay logic for both 1 and 2 player modes
/// 1 player settings: time limit, stroke limit
/// 2 player settings: elapsed timer, stroke count (no limits for either), 
///					   powerup logic etc
class GameLogicMgr
{
public:
	GameLogicMgr() {}
	~GameLogicMgr() {}

	// Game logic controls HUD 
	UI uiMgr;

	// Different gameplay logic for 1 and 2 player modes
	int players;
	int timeLimit;
	bool p1Finished, p2Finished;
	int p1Score, p2Score;
	bool gameEnded = false;


	// Game clock
	int startTime;
	int lastFrameTime;
	int elapsedTime;



	// Setup start of game HUD
	void Setup(int numPlayers, int diff);

	// Start game clock
	void StartGameClock();

	// Called when player stroke counter incremented
	void PlayerFired(int playerIndex, Player &player);

	// Keep clock ticking
	void Update();

	// When a player finishes, mark their total time
	void SetEndTime(Player &player);
	
	// Used for demo on 4th
	void PrintPlayerScore(Player player);

	// Choose a random powerup
	void RandomPowerup(Player &player);

};
