#include <random>
#include "glew_glfw.h"
#include "GameLogicMgr.h"
#include "windowMgr.h"

// Setup start of game HUD
void GameLogicMgr::Setup(int numPlayers)
{
	// Set number of players this game
	players = numPlayers;
	gameEnded = false;

	// Deprecated - not enforcing time limit anymore
	// Set this level time limit in seconds
	//switch (diff) diff was number of tiles
	//{
	//// Easy 
	//case 8:
	//	// decide easy time limit
	//	timeLimit = 90;
	//	break;
	//// Medium
	//case 12:
	//	// decide med time limit
	//	timeLimit = 120;
	//	break;
	//case 16:
	//	// decide hard time limit
	//	timeLimit = 180;
	//	break;
	//default: 
	//	// decide default behaviour
	//	timeLimit = 120;
	//	break;
	//}

	// Invoke UImgr to perform its setup
	if (players == 1)
	{
		uiMgr.p1Setup();
	}
	else if (players == 2)
	{
		uiMgr.p2Setup();
	
	}
	
	// Setup game clock
	//uiMgr.SetupClock(endHolePos, endHoleDir);

}

// Start tracking time for this game
void GameLogicMgr::StartGameClock()
{
	// This marks the start time
	startTime = glfwGetTime();
}

// Marks pause start time
void GameLogicMgr::PauseGameClock()
{
	pauseStartTime = glfwGetTime();
}

// Set pause duration
void GameLogicMgr::UnpauseGameClock()
{
	pauseDuration += glfwGetTime() - pauseStartTime;
}

// Keep clocks ticking...
void GameLogicMgr::UpdateClock()
{
	// Update elapsed timer clock
	// Time from current subtract start time

	lastFrameTime = elapsedTime;
	elapsedTime = glfwGetTime() - startTime;
	elapsedTime -= pauseDuration;
	//pauseStartTime = pauseDuration = 0;

	// No longer have time limit in 1p mode; using world clock in both modes
	// Work out how much time is left given this game's time limit
	//int timeRemaining = timeLimit - elapsedTime;
	//uiMgr.UpdateHUDClock(timeRemaining);

	// Only update the UI every second
	if (elapsedTime > lastFrameTime && !gameEnded)
	{
		uiMgr.UpdateWorldClock(abs(elapsedTime));	
	}
}

// Update power bar
void GameLogicMgr::UpdatePowerBar(Player player)
{
	// If amount of players in game is euqal to 1 then - require because player one behaviour is different for both players
	if (players == 1)
	{
		// Check which player this is
		if (player.id == 1)
		{
			// Update p1 power bar
			windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(0.88 + (player.power /23), -1.47f, 0.0f));
		}
	}
	// Else if to players in game 
	else
	{
		// Check which player this is
		if (player.id == 1)
		{
			// Update p1 power bar
			windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(-0.12 + (player.power / 15.5), -1.67f, 0.0f));
		}
		else if (player.id == 2)
		{
			// Update p2 power bar
			windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(-0.12 + (player.power / 23), -1.67f, 0.0f));
		}
	}
}

// Called after a player fired a shot
// Checks against stroke limit if this is 1 player mode
// Updates UI to refelct increase to strokeCounter
void GameLogicMgr::PlayerFired(Player &player)
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
			uiMgr.UpdateStrokeCounter(player.id - 1, player.strokeCounter);
		}
		else if (players == 2)
		{

			// Update UI
			uiMgr.UpdateStrokeCounter(player.id - 1, player.strokeCounter);
		}
	}


}

// Called when a player finishes, sets their end score
void GameLogicMgr::SetScore(Player &player)
{
	// Only occur once; the first time this is called, player.gameOver will be false
	if (!player.gameOver)
	{
		// Set end time
		player.totalTime = elapsedTime;
		// Set final score - multiply time by strokes. Divide by 10 for smaller form
		player.finalScore = (player.totalTime * player.strokeCounter) / 10;

	}	
}

// Print final scores of player(s)
void GameLogicMgr::ShowEndgameScoreboard(vector<Player> players)
{
	// If 1 player mode, print only p1 score
	if (players.size() == 1)
	{
		//Counting how many digits score has
		// Convert to string here, number of digits is string.length()
		string scoreStr = to_string(players[0].finalScore);
		int countP1Score = scoreStr.length();
		//If the count of digits for p1 score is higher than the digit limit allowed (default 7)
		if (countP1Score > digitLimitForScore)
		{
			//for each digit above the limit
			for (int i = digitLimitForScore + 1; i < countP1Score; i++)
			{
				//divide score by 10
				players[0].finalScore /= 10;
			}
		}

		// Invoke UI to set hud textures for player score
		uiMgr.p1GameScoreboard(scoreStr);
		p1Score = players[0].finalScore;
	}
	// Else if 2 player mode, print both player scores
	else if (players.size() == 2)
	{
		string scoreStr1 = to_string(players[0].finalScore);
		string scoreStr2 = to_string(players[1].finalScore);
		//Counting how many digits both score have
		int countP1Score = scoreStr1.length();
		int countP2Score = scoreStr2.length();

		//I know it's nasty :(

		//I'm separating the cases because it needs to take into account the score with the highest digit and 
		//divide both scores for each digit over the digit limit

		//If the count of digits for p1 score is higher than the digit limit allowed (default 7)
		if (countP1Score > digitLimitForScore)
		{
			//for each digit over the digit limit
			for (int i = digitLimitForScore + 1; i < countP1Score; i++)
			{
				//divide score of player with exceding digits by 10
				players[0].finalScore /= 10;

				//doing the same for other player, but dividing it only it it is equal or higher than 10
				if (players[1].finalScore >= 10)
				{
					players[1].finalScore /= 10;
				}
			}
		}
		//If the count of digits for p2 score is higher than the digit limit allowed (default 7)
		else if (countP2Score > digitLimitForScore)
		{
			//for each digit over the digit limit

			for (int i = digitLimitForScore + 1; i < countP2Score; i++)
			{
				//divide score of player with exceding digits by 10
				players[1].finalScore /= 10;

				//doing the same for other player, but dividing it only it it is equal or higher than 10
				if (players[0].finalScore >= 10)
				{
					players[0].finalScore /= 10;
				}
			}
		}

		uiMgr.p2GameScoreboard(scoreStr1, scoreStr2);
		p1Score = players[0].finalScore;
		p2Score = players[1].finalScore;
	}
}

// Used in demo (no leaderboard yet)
void GameLogicMgr::PrintPlayerScore(Player player)
{
	// Assume: P1 reaches end of level before P2
	// Then: player param given is player one
	// Print score for this player
	switch (player.id)
	{
	// This will be p1
	case 1:
	{
		if (!p1Finished)
		{
			cout << "##### Player " << player.id << " #####" << endl;
			cout << "Total time: " << player.totalTime << " seconds" << endl;
			cout << "Total strokes: " << player.strokeCounter << endl;
			// P1 score is set
			p1Score = player.totalTime * player.strokeCounter;
			cout << "Final score: " << p1Score << endl;
			// Set bool for this player to finished 
			p1Finished = true;
			if (players == 1)
				cout << "To return to main menu, pause game (P) then hit C!" << endl;
		}
		break;
	}
	// Since it's p1, this won't run...
	case 2:
	{
		if (!p2Finished)
		{
			cout << "##### Player " << player.id << " #####" << endl;
			cout << "Total time: " << player.totalTime << " seconds" << endl;
			cout << "Total strokes: " << player.strokeCounter << endl;
			// Therefore p2 is not set, because he hasn't finished
			p2Score = player.totalTime * player.strokeCounter;
			cout << "Final score: " << p2Score << endl;
			// Set bool for this player to finished 
			p2Finished = true;
		}
	} // end p2 endgame scoring
		break;
	default: cout << "Error in GameLogicMgr::PrintPlayerScore" << endl; break;
	} // end switch on this given player id
	

	// if 2 players and both players finished, compute and print score
	
	if (p1Finished && p2Finished && !gameEnded)
	{
		if (p1Score > p2Score)
			cout << "Player 2 is the winner!" << endl;
		else if (p2Score > p1Score)
			cout << "Player 1 is the winner!" << endl;
		else if (p1Score == p2Score)
			cout << "Both players draw!" << endl;

		cout << "To return to main menu, pause game (P) then hit C!" << endl;
		gameEnded = true;
	}

	//uiMgr.SetScoreToPrint(players, p1Score, p2Score);
	
}

// Randomly choose and assign a power to player
void GameLogicMgr::RandomPowerup(Player &player)
{
	// Pick random number between 1 and number of available pickups 
	default_random_engine rng(random_device{}());
	uniform_int_distribution<int> distribution(1, 2);
	int choice = distribution(rng);
	
	// Enact powerup 
	switch (choice)
	{
	// Player gets big!
	case 1:
	{
		player.transform.getScale() = vec3(0.7);
		player.radius = 0.8;
		player.mass = 1.4;
	}
		break;
	// Player gets small!
	case 2:
	{
		player.transform.getScale() = vec3(0.3);
		player.radius = 0.3;
		player.mass = 1.0;
	}
		break;
	
	default: break;
	}
}