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

	// Game clock
	int startTime;
	int lastFrameTime;
	int elapsedTime;



	// Setup start of game HUD
	void Setup(int numPlayers, vec3 endHolePos);

	// Start game clock
	void StartGameClock();

	// Called when player stroke counter incremented
	void PlayerFired(int playerIndex, Player &player);



	// Keep clock ticking
	void Update();





};
