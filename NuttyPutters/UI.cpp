#include "UI.h"
#include "windowMgr.h"

// Sets up basic HUD layout for 1 player game
void UI::p1Setup()
{

	// Stroke labels
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Power bar
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetScale(2.4f, 0.4f);
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetPos(vec3(2.0f, -1.5f, -0.1f));
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);

	// Power indicator
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetScale(0.05f, 0.27f);
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(0.88f, -1.47f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);

}

// Sets up basic HUD layout for 2 player game
void UI::p2Setup()
{
	// P1 Stroke labels
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetScale(4.0f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetPos(vec3(-3.15f, -1.7f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetScale(4.0f, 0.5f);
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetPos(vec3(-2.45f, -1.7f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Power bar
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetScale(3.6f, 0.4f);
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetPos(vec3(1.5f, -1.7f, -0.1f));
	windowMgr::getInstance()->p1HUDmeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);

	// Power indicator
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetScale(0.1f, 0.27f);
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetPos(vec3(-0.12f, -1.67f, 0.0f));
	windowMgr::getInstance()->p1HUDmeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);

	// P2 Stroke Labels
	windowMgr::getInstance()->p2HUDmeshes.at(0)->SetScale(4.0f, 0.5f);
	windowMgr::getInstance()->p2HUDmeshes.at(0)->SetPos(vec3(-3.15f, -1.7f, 0.0f));
	windowMgr::getInstance()->p2HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->p2HUDmeshes.at(1)->SetScale(4.0f, 0.5f);
	windowMgr::getInstance()->p2HUDmeshes.at(1)->SetPos(vec3(-2.45f, -1.7f, 0.0f));
	windowMgr::getInstance()->p2HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Power bar
	windowMgr::getInstance()->p2HUDmeshes.at(2)->SetScale(3.6f, 0.4f);
	windowMgr::getInstance()->p2HUDmeshes.at(2)->SetPos(vec3(1.5f, -1.7f, -0.1f));
	windowMgr::getInstance()->p2HUDmeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);
	// Power indicator
	windowMgr::getInstance()->p2HUDmeshes.at(3)->SetScale(0.1f, 0.27f);
	windowMgr::getInstance()->p2HUDmeshes.at(3)->SetPos(vec3(-0.12f, -1.67f, 0.0f));
	windowMgr::getInstance()->p2HUDmeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["powerIndicator"]);


	//// Resume
	//windowMgr::getInstance()->meshes.at(8)->SetScale(4.2f, 0.7f);
	//windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(0.0f, 1.2f, 0.0f));

	//windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
	//// Save
	//windowMgr::getInstance()->meshes.at(9)->SetScale(4.2f, 0.7f);
	//windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(0.0f, 0.6f, 0.0f));
	//windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
	//// Controls
	//windowMgr::getInstance()->meshes.at(10)->SetScale(4.2f, 0.7f);
	//windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	//windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["controlsBtnUnselected"]);
	//// Main menu
	//windowMgr::getInstance()->meshes.at(11)->SetScale(4.2f, 0.7f);
	//windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, -0.6f, 0.0f));
	//windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
	//// Exit
	//windowMgr::getInstance()->meshes.at(12)->SetScale(4.2f, 0.7f);
	//windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -1.2f, 0.0f));
	//windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);;

}

// Sets up pause screen meshes
void UI::SetupPauseScreen()
{
	// Pause menu stuff
	//windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetScale(1.8f, 0.6f);
	//windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	//windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);

	//windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetScale(1.8f, 0.6f);
	//windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	//windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);

	//windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetScale(1.8f, 0.6f);
	//windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	//windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);

	//windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetScale(1.8f, 0.6f);
	//windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	//windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);


	// Resume
	windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetPos(vec3(0.0f, 1.2f, 0.0f));
	windowMgr::getInstance()->pauseScreenMeshes.at(0)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
	// Save
	windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetPos(vec3(0.0f, 0.6f, 0.0f));
	windowMgr::getInstance()->pauseScreenMeshes.at(1)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
	// Controls
	windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->pauseScreenMeshes.at(2)->SetTexture(windowMgr::getInstance()->textures["controlsBtnUnselected"]);
	// Main menu
	windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetPos(vec3(0.0f, -0.6f, 0.0f));
	windowMgr::getInstance()->pauseScreenMeshes.at(3)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
	// Exit
	windowMgr::getInstance()->pauseScreenMeshes.at(4)->SetScale(4.2f, 0.7f);
	windowMgr::getInstance()->pauseScreenMeshes.at(4)->SetPos(vec3(0.0f, -1.2f, 0.0f));
	windowMgr::getInstance()->pauseScreenMeshes.at(4)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);

}

// Set world clock initial properties
void UI::SetupClock()
{
	// Set initial textures:
	for (int i = 0; i < windowMgr::getInstance()->worldClockMeshes.size(); i++)
	{
		if (i == 2) // Put colon in middle
			windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
		else
			windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	}
}
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
void UI::p1GameScoreboard(string score)
{
	// Aspect ratio for scaling textures
	vec2 ratio = vec2(2.0f, 0.50f);

	//this is used to move position according to how many digits the score has --> to have it centered
	float pos = 0.0f;
	if (score.length() > 1)
	{
		for (int i = 1; i < score.length(); i++)
		{
			pos -= (ratio.x / 4.0f);
		}
	}

	//setting used meshes to score length to retrieve number of meshes to be rendered
	usedMeshesP1 = score.length();
	// For each character in the score string
	for (int c = 0; c < score.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = score[c] - 48;

		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetPos(vec3(pos, 0.0f, 0.0f));
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
		pos += (ratio.x / 4.0f);
	}

	//SCORE SCREEN HUD
	//Single player
	//BackGround
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->winConditionsMeshes.at(0)->SetTexture(windowMgr::getInstance()->textures["onePlayerScore"]);
}

// Sets endgame scoreboard for 2p game
void UI::p2GameScoreboard(string p1Score, string p2Score)
{
	// Aspect ratio for scaling textures
	vec2 ratio = vec2(1.0f, 0.25f);
	// Player 1

	// HUD mesh positions
	float pos1 = 1 - (ratio.x / 4.0f);
	for (int i = 1; i < p1Score.length(); i++)
	{
		pos1 -= (ratio.x / 4.0f);
	}
	usedMeshesP1 = p1Score.length();
	// For each character in the score string
	for (int c = 0; c < p1Score.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = p1Score[c] - 48;

		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetPos(vec3(pos1 + ((ratio.x / 4.0f) * c), 0.0f, 0.0f));
		windowMgr::getInstance()->player1ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
	}

	// Player 2
	// HUD mesh positions
	float pos2 = 1 - (ratio.x / 4.0f);
	for (int i = 1; i < p2Score.length(); i++)
	{
		pos2 -= (ratio.x / 4.0f);
	}
	usedMeshesP2 = p2Score.length();
	// For each character in the score string
	for (int c = 0; c < p2Score.length(); c++)
	{
		// Convert to int, set mesh as approrpiate
		int thisNum = p2Score[c] - 48;

		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetScale(ratio.x, ratio.y);
		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetPos(vec3(pos2 + ((ratio.x / 4.0f) * c), -0.30f, 0.0f));
		windowMgr::getInstance()->player2ScoreMeshes.at(c)->SetTexture(windowMgr::getInstance()->numberTextures.at(thisNum));
	}

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

// Update game clock - only applies to 1 player mode. Takes in total elapsed time this game
void UI::UpdateHUDClock(int time)
{


	// Time given is elapsed time since start in seconds
	//	// Get the time in minutes, tenths and seconds - 0M:TS
	int	minutes = time / 60;
	int	tensSeconds = (time - (minutes * 60)) / 10;
	int	seconds = time - (minutes * 60) - (tensSeconds * 10);
	
	// Update HUD meshes accordingly

	// Seconds
	windowMgr::getInstance()->HUDclockMeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(seconds)));
	// Tens of seconds
	windowMgr::getInstance()->HUDclockMeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(tensSeconds)));
	// Minutes 
	windowMgr::getInstance()->HUDclockMeshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(abs(minutes)));


}

// Update world clock - only applied in 2 player mode
void UI::UpdateWorldClock(int time)
{
	// Time given is elapsed time since start in seconds
	//	// Get the time in minutes, tenths and seconds - 0M:TS
	 // If time is 600 then it's 10 minutes...minutes index will be 10 - fix!
	int	minutes = time / 60;
	int tensMinutes = (time / 60) / 10;
	int	tensSeconds = (time - (minutes * 60)) / 10;
	int	seconds = time - (minutes * 60) - (tensSeconds * 10);

	// Seconds
	windowMgr::getInstance()->worldClockMeshes.at(4)->SetTexture(windowMgr::getInstance()->numberTextures.at(seconds));
	windowMgr::getInstance()->worldClockMeshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(tensSeconds));
	// Miss an index position (colon is at 2)
	windowMgr::getInstance()->worldClockMeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(minutes));
	windowMgr::getInstance()->worldClockMeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(tensMinutes));

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
		windowMgr::getInstance()->p1HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(tens));
		// Update 1s
		windowMgr::getInstance()->p1HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(ones));
	}
	// P2
	else if (playerIndex == 1)
	{
		// Update 10s
		windowMgr::getInstance()->p2HUDmeshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(tens));
		// Update 1s
		windowMgr::getInstance()->p2HUDmeshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(ones));
	}

}
