#include "UI.h"
#include "windowMgr.h"


//sets hud for pause
void UI::PauseScreen()
{
	windowMgr::getInstance()->meshes.at(0)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);
}

// Sets endgame scoreboard for 1p game
void UI::p1GameScoreboard(int score)
{
	// Aspect ratio for scaling textures
	vec2 ratio = vec2(1.0f, 0.25f);

	//this is used to move position according to how many digits the score has --> to have it centered
	float pos = (ratio.x / 4.0f);

	// Convert to string
	string scoreStr = to_string(score);
	usedMeshesP1 = scoreStr.length();
	// For each character in the score string
	for (int c = 0; c < scoreStr.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = scoreStr[c] - 48;

		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetPos(vec3(pos + ((ratio.x / 4.0f) * c), 0.0f, 0.0f));
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
	}

	//BUTTON TO GO TO MAIN MENU
	windowMgr::getInstance()->meshes.at(16)->SetScale(2.8f, 0.4f);
	windowMgr::getInstance()->meshes.at(16)->SetPos(vec3(0.0f, -1.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(16)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnSelected"]);

	//SCORE SCREEN HUD
	//Single player
	//BackGround
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetTexture(windowMgr::getInstance()->textures["onePlayerScore"]);
}

// Sets endgame scoreboard for 2p game
void UI::p2GameScoreboard(int p1Score, int p2Score)
{
	// Aspect ratio for scaling textures
	vec2 ratio = vec2(1.0f, 0.25f);
	// Player 1
	scoreP1 = p1Score;
	// Convert int score to string
	string score1 = to_string(scoreP1);
	// HUD mesh positions
	float pos1 = 1 - (ratio.x / 4.0f);
	for (int i = 1; i < score1.length(); i++)
	{
		pos1 -= (ratio.x / 4.0f);
	}
	usedMeshesP1 = score1.length();
	// For each character in the score string
	for (int c = 0; c < score1.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = score1[c] - 48;

		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetPos(vec3(pos1 + ((ratio.x / 4.0f) * c), 0.0f, 0.0f));
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
	}

	// Player 2
	scoreP2 = p2Score;
	// Convert to string
	string score2 = to_string(scoreP2);
	// HUD mesh positions
	float pos2 = 1 - (ratio.x / 4.0f);
	for (int i = 1; i < score2.length(); i++)
	{
		pos2 -= (ratio.x / 4.0f);
	}
	usedMeshesP2 = score2.length();
	// For each character in the score string
	for (int c = 0; c < score2.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = score2[c] - 48;

		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetPos(vec3(pos2 + ((ratio.x / 4.0f) * c), -0.30f, 0.0f));
		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
	}

	//BUTTON TO GO TO MAIN MENU
	windowMgr::getInstance()->meshes.at(16)->SetScale(2.8f, 0.4f);
	windowMgr::getInstance()->meshes.at(16)->SetPos(vec3(0.0f, -1.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(16)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnSelected"]);

	//SCORE SCREEN HUD
	//Multiplayer
	//Background p1 wins
	windowMgr::getInstance()->winConditionsMeshes.at(1)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->winConditionsMeshes.at(1)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->winConditionsMeshes.at(1)->SetTexture(windowMgr::getInstance()->textures["MultPlayerP1Win"]);
	//Background p2 wins
	windowMgr::getInstance()->winConditionsMeshes.at(2)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->winConditionsMeshes.at(2)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->winConditionsMeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["MultPlayerP2Win"]);
	//Background draw
	windowMgr::getInstance()->winConditionsMeshes.at(3)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->winConditionsMeshes.at(3)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->winConditionsMeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["MultPlayerDraw"]);

}



// Sets up basic HUD layout for 1 player game
void UI::p1Setup()
{

	// Stroke labels
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Timer seconds digit
	windowMgr::getInstance()->meshes.at(5)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(2.8f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer tens digit
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(2.95f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer minutes digit
	windowMgr::getInstance()->meshes.at(3)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(3.15f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer tens of minutes digit
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(3.3f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer semi colon
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(3.05f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
    // Power bar
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetScale(0.8f, 0.8f);
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetPos(vec3(3.0f, -1.0f, -0.1f));
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);
	// Power indicator
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetScale(0.2f, 0.2f);
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);

  
	windowMgr::getInstance()->meshes.at(9)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);

	windowMgr::getInstance()->meshes.at(10)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);

	windowMgr::getInstance()->meshes.at(11)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);

	windowMgr::getInstance()->meshes.at(12)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);
  

	// Resume
	windowMgr::getInstance()->meshes.at(9)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(0.0f, 1.2f, 0.0f));

	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
	// Save
	windowMgr::getInstance()->meshes.at(10)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.6f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
	// Controls
	windowMgr::getInstance()->meshes.at(11)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["controlsBtnUnselected"]);
	// Main menu
	windowMgr::getInstance()->meshes.at(12)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -0.6f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
	// Exit
	windowMgr::getInstance()->meshes.at(13)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(0.0f, -1.2f, 0.0f));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);
 
}

// Sets up basic HUD layout for 2 player game
void UI::p2Setup()
{
	// P1 Stroke labels
	windowMgr::getInstance()->meshes.at(0)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->meshes.at(1)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
		
	// Power bar
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.8f, 0.8f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(3.0f, -1.0f, -0.1f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);

	// Power indicator
	windowMgr::getInstance()->meshes.at(3)->SetScale(0.2f, 0.2f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);

	// World clock setup - appear behind end hole
	// P2 Stroke Labels
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->meshes.at(5)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Power bar
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.8f, 0.8f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(3.0f, -1.0f, -0.1f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);

	// Power indicator
	windowMgr::getInstance()->meshes.at(7)->SetScale(0.2f, 0.2f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);
  

	// Resume
	windowMgr::getInstance()->meshes.at(8)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(0.0f, 1.2f, 0.0f));

	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
	// Save
	windowMgr::getInstance()->meshes.at(9)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(0.0f, 0.6f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
	// Controls
	windowMgr::getInstance()->meshes.at(10)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["controlsBtnUnselected"]);
	// Main menu
	windowMgr::getInstance()->meshes.at(11)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, -0.6f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
	// Exit
	windowMgr::getInstance()->meshes.at(12)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -1.2f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);;

	// World clock setup - appear behind end hole. Set initial textures: 
	for (int i = 0; i <  windowMgr::getInstance()->worldClock.size(); i++)
	{
		if (i == 2)
			windowMgr::getInstance()->worldClock.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
		else
			windowMgr::getInstance()->worldClock.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	}
}

// Update game clock - only applies to 1 player mode
// Input: total elapsed time this game
void UI::UpdateHUDClock(int time)
{


	// Time given is elapsed time since start in seconds
	//	// Get the time in minutes, tenths and seconds - 0M:TS
	int	minutes = time / 60;
	int	tensSeconds = (time - (minutes * 60)) / 10;
	int	seconds = time - (minutes * 60) - (tensSeconds * 10);
	
	// Update HUD meshes accordingly


	// Minutes 
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(minutes)));
	// Tens of seconds
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(tensSeconds)));
	// Seconds
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(seconds)));
}

// Update world clock - only applied in 2 player mode
void UI::UpdateWorldClock(int time)
{
	// Time given is elapsed time since start in seconds
	//	// Get the time in minutes, tenths and seconds - 0M:TS
	int	minutes = time / 60;
	int	tensSeconds = (time - (minutes * 60)) / 10;
	int	seconds = time - (minutes * 60) - (tensSeconds * 10);

	windowMgr::getInstance()->worldClock.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(seconds));
	windowMgr::getInstance()->worldClock.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(tensSeconds));
	windowMgr::getInstance()->worldClock.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(minutes));
}

// Update ui to reflect increase to stroke counter
void UI::UpdateStrokeCounter(int playerIndex, int strokeCounter)
{
	// Update texture for given player HUD element
	// Split stroke counter into 10s and 1s
	int tens, ones;
	string scString = to_string(strokeCounter);
	
	// Deal with when stroke counter is below ten
	if (strokeCounter < 10)
	{
		char num = scString[0];
		ones = num - 48;
		tens = 0;
	}
	else
	{
		char tensChar = scString[0];
		tens = tensChar - 48;
		char onesChar = scString[1];
		ones = onesChar - 48;
	}

	// P1
	if (playerIndex == 0)
	{
		// Update 10s
		windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(tens));
		// Update 1s
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(ones));
	}
	// P2
	else if (playerIndex == 1)
	{
		// Update 10s
		windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(tens));
		// Update 1s
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(ones));
	}

}







