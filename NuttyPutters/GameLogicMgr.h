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
	int digitLimitForScore = 7;
	bool gameEnded = false;


	// Game clock
	int startTime;
	int lastFrameTime;
	int elapsedTime;
	int pauseStartTime, pauseDuration;


	// Setup start of game HUD
	void Setup(int numPlayers);

	// Start game clock
	void StartGameClock();
	void PauseGameClock();
	void UnpauseGameClock();
	// Called when player stroke counter incremented
	void PlayerFired(Player &player);

	// Keep clock ticking
	void UpdateClock();


	// Update user power bar
	void UpdatePowerBar(Player player);

	// When a player finishes, mark their total time
	void SetScore(Player &player);
	
	// Print final scores of player(s)
	void ShowEndgameScoreboard(vector<Player> players);

	// Used for demo on 4th
	void PrintPlayerScore(Player player);

	// Choose a random powerup
	void RandomPowerup(Player &player);

};
