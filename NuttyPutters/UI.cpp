#include "UI.h"
#include "windowMgr.h"



// Sets up basic HUD layout for 1 player game
void UI::p1Setup()
{

	// Stroke labels
	windowMgr::getInstance()->meshes.at(0)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->meshes.at(1)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	// Timer seconds digit
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(2.8f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer tens digit
	windowMgr::getInstance()->meshes.at(3)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(2.95f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer minutes digit
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(3.15f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer tens of minutes digit
	windowMgr::getInstance()->meshes.at(5)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(3.3f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));
	// Timer semi colon
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(3.05f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));

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
		
	// P2 Stroke Labels
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

	windowMgr::getInstance()->meshes.at(3)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(-2.5f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));


	// World clock setup - appear behind end hole


	// Set initial textures
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




























//#include "windowMgr.h"
//
////void UI::Init()
////{
////	// Stroke HUD Label setup
////	windowMgr::getInstance()->meshes.at(0)->SetScale(0.5f, 0.5f);
////	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
////	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["zeroStrokeLbl"]);
////	// Player HUD Labelsetup
////	windowMgr::getInstance()->meshes.at(1)->SetScale(1.0f, 0.25f);
////	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.75f, 1.5f, 0.0f));
////	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playerOneLbl"]);
////	// Power HUD Label setup
////	windowMgr::getInstance()->meshes.at(2)->SetScale(1.0f, 0.25f);
////	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(3.0f, -1.375f, 0.0f));
////	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);
////	// Power Bar HUD setup
////	windowMgr::getInstance()->meshes.at(3)->SetScale(0.1f, 0.15f);
////	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(1.6f, -1.625f, 0.0f));
////	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["playerBlueTexture"]);
////	// Power Bar Outline HUD setup
////	windowMgr::getInstance()->meshes.at(4)->SetScale(2.0f, 0.25f);
////	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(2.5f, -1.625f, 0.0f));
////	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["powerOutlineLbl"]);
////	// Setup timer values 
////	// Timer first unit
////	windowMgr::getInstance()->meshes.at(5)->SetScale(0.25f, 0.25f);
////	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(2.8f, 1.7f, 0.0f));
////	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
////	// Timer second unit
////	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
////	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(2.95f, 1.7f, 0.0f));
////	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
////	// Timer third unit
////	windowMgr::getInstance()->meshes.at(7)->SetScale(0.25f, 0.25f);
////	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(3.15f, 1.7f, 0.0f));
////	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
////	// Timer forth unit
////	windowMgr::getInstance()->meshes.at(8)->SetScale(0.25f, 0.25f);
////	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(3.3f, 1.7f, 0.0f));
////	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
////	// Timer semi colon
////	windowMgr::getInstance()->meshes.at(9)->SetScale(0.25f, 0.25f);
////	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(3.05f, 1.725f, 0.0f));
////	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["semiColonLbl"]);
////	// End Game HUDs
////	// Centre Header one 
////	windowMgr::getInstance()->meshes.at(10)->SetScale(2.0f, 0.5f);
////	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.75f, 0.0f));
////	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["parFourLbl"]);
////	// Centre Header two 
////	windowMgr::getInstance()->meshes.at(11)->SetScale(2.0f, 0.5f);
////	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, 0.25f, 0.0f));
////	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["timeTwoLbl"]);
////	// Centre Footer one 
////	windowMgr::getInstance()->meshes.at(12)->SetScale(2.0f, 0.5f);
////	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -0.25f, 0.0f));
////	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["semiColonLbl"]);
////	// Centre Footer two 
////	windowMgr::getInstance()->meshes.at(13)->SetScale(2.0f, 0.5f);
////	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(0.0f, -0.75f, 0.0f));
////	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["xContinueLbl"]);
////
////	// Splash Screen
////	windowMgr::getInstance()->meshes.at(19)->SetScale(8.0f, 5.0f);
////	windowMgr::getInstance()->meshes.at(19)->SetPos(vec3(0.0f, 0.0f, 0.0f));
////	windowMgr::getInstance()->meshes.at(19)->SetTexture(windowMgr::getInstance()->textures["gameSplashScreen"]);
////}

	// Stroke counter end
//		// If more than 13 strokes have been taken then update necessary textures and set boolean to true
//		windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["outOfLbl"]);
//		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["outOfStrokesLbl"]);
//		windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["saveGameLbl"]);
//		windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
//		return true;
//		break;
//	}
//}
//
//// Update the game timer 
//bool UI::updateTimer(int timeSinceContinueWasPressed, int timeToThisMethod, int holeTimer)
//{
//	// Get the time since continue was pressed by taking away the time to this method
//	timeSinceContinueWasPressed = glfwGetTime() - timeToThisMethod;
//
//	// Get the time remaining in seconds by taking away the time the user has to complete the hole 
//	timeRemainingInSeconds = holeTimer - timeSinceContinueWasPressed;
//	// Get the time in minutes, tenths and seconds - 0M:TS
//	timeRemainingInMinutes = timeRemainingInSeconds / 60;
//	timeRemainingInTenths = (timeRemainingInSeconds - (timeRemainingInMinutes * 60)) / 10;
//	timeRemainingInSeconds = timeRemainingInSeconds - (timeRemainingInMinutes * 60) - (timeRemainingInTenths * 10);
//	// Cast each above timer variable into a string eg 1, 3, 0
//	minutesAsString = std::to_string(timeRemainingInMinutes);
//	tenthsAsString = std::to_string(timeRemainingInTenths);
//	secondsAsString = std::to_string(timeRemainingInSeconds);
//	// Create a new empty string time - append each above var to it eg time = 130
//	timeCombined = minutesAsString + tenthsAsString + secondsAsString;
//
//	// for loop that runs 3 times
//	for (int i = 0; i < 3; i++)
//	{
//		// Get the timecombined at index i and make it equal to temp
//		temp = timeCombined[i];
//		// Convert temp to int
//		tempInt = atoi(temp.c_str());
//		// Switch using tempInt value
//		switch (tempInt)
//		{
//		case 0:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
//			break;
//		case 1:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["oneLbl"]);
//			break;
//		case 2:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
//			break;
//		case 3:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["threeLbl"]);
//			break;
//		case 4:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["fourLbl"]);
//			break;
//		case 5:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["fiveLbl"]);
//			break;
//		case 6:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["sixLbl"]);
//			break;
//		case 7:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["sevenLbl"]);
//			break;
//		case 8:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["eightLbl"]);
//			break;
//		case 9:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["nineLbl"]);
//			break;
//		default:
//			windowMgr::getInstance()->meshes.at(i + 6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
//			break;
//		}
//	}
//
//	// If user has no time remaining then
//	if (timeRemainingInSeconds < 0)
//	{
//		// Update necessary textures
//		windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["outOfLbl"]);
//		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["outOfTimeLbl"]);
//		windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["saveGameLbl"]);
//		windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
//		// Update boolean - used for rendering
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
