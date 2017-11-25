

#include "highscoreScene.h"
#include "windowMgr.h" // to access singleton

// Constructor
highscoreScene::highscoreScene() { }
// Deconstructor
highscoreScene::~highscoreScene() { }

void highscoreScene::Init(GLFWwindow * win)
{
	// Set scale, position and size of various meshes - all unique
	// Set background
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["loadGameBackground"]);
	// Set action label
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.7f, 1.39f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["actionLbl"]);
	// Set button label
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(-1.1f, 1.39f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["buttonLbl"]);
	// Select Fire
	// Set selectfire label
	windowMgr::getInstance()->meshes.at(3)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(-2.7f, 1.07f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["selectfireLbl"]);
	// Set selectfire button label controller button
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(-1.1f, 1.07f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
	// Back Reset
	// Set backreset label
	windowMgr::getInstance()->meshes.at(5)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-2.7f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["backresetLbl"]);
	// Set backreset button label controller button
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(-1.1f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
	// Pause
	// Set pause label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(-2.7f, 0.43f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["pauseLbl"]);
	// Set pause button label controller button
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(-1.1f, 0.43f, 0.0f));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
	// Arrows
	// Up
	windowMgr::getInstance()->meshes.at(9)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(-2.7f, 0.11f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["upLbl"]);
	// Set up controller button
	windowMgr::getInstance()->meshes.at(10)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(-1.1f, 0.11f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
	// Left
	windowMgr::getInstance()->meshes.at(11)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(-2.7f, -0.21f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Set left controller button
	windowMgr::getInstance()->meshes.at(12)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(-1.1f, -0.21f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
	// Down 
	windowMgr::getInstance()->meshes.at(13)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(-2.7f, -0.53f, 0.0f));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["downLbl"]);
	// Set down controller button
	windowMgr::getInstance()->meshes.at(14)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(14)->SetPos(vec3(-1.1f, -0.53f, 0.0f));
	windowMgr::getInstance()->meshes.at(14)->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
	// Right
	windowMgr::getInstance()->meshes.at(15)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(15)->SetPos(vec3(-2.7f, -0.85f, 0.0f));
	windowMgr::getInstance()->meshes.at(15)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
	// Set right controller button
	windowMgr::getInstance()->meshes.at(16)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(16)->SetPos(vec3(-1.1f, -0.85f, 0.0f));
	windowMgr::getInstance()->meshes.at(16)->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
	// Jump
	windowMgr::getInstance()->meshes.at(17)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(17)->SetPos(vec3(-2.7f, -1.17f, 0.0f));
	windowMgr::getInstance()->meshes.at(17)->SetTexture(windowMgr::getInstance()->textures["jumpLbl"]);
	// Set jump controller button
	windowMgr::getInstance()->meshes.at(18)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(18)->SetPos(vec3(-1.1f, -1.17f, 0.0f));
	windowMgr::getInstance()->meshes.at(18)->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
	// Zoom In
	windowMgr::getInstance()->meshes.at(19)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(19)->SetPos(vec3(-2.7f, -1.50f, 0.0f));
	windowMgr::getInstance()->meshes.at(19)->SetTexture(windowMgr::getInstance()->textures["zoomInLbl"]);
	// Set zoom in controller button
	windowMgr::getInstance()->meshes.at(20)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(20)->SetPos(vec3(-1.1f, -1.50f, 0.0f));
	windowMgr::getInstance()->meshes.at(20)->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
	// Zoom Out
	windowMgr::getInstance()->meshes.at(21)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(21)->SetPos(vec3(-2.7f, -1.82f, 0.0f));
	windowMgr::getInstance()->meshes.at(21)->SetTexture(windowMgr::getInstance()->textures["zoomOutLbl"]);
	// Set zoom out controller button
	windowMgr::getInstance()->meshes.at(22)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(22)->SetPos(vec3(-1.1f, -1.82f, 0.0f));
	windowMgr::getInstance()->meshes.at(22)->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
	// Main Menu
	windowMgr::getInstance()->meshes.at(23)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(23)->SetPos(vec3(2.5f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(23)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
	// Set the player one and player two lbls
	// P1
	windowMgr::getInstance()->meshes.at(24)->SetScale(1.8f, 0.45f);
	windowMgr::getInstance()->meshes.at(24)->SetPos(vec3(-2.0f, 1.81f, 0.0f));
	windowMgr::getInstance()->meshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLbl"]);
	// P2
	windowMgr::getInstance()->meshes.at(25)->SetScale(1.8f, 0.45f);
	windowMgr::getInstance()->meshes.at(25)->SetPos(vec3(0.0f, 1.81f, 0.0f));
	windowMgr::getInstance()->meshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLbl"]);
	// Keyboard Label
	windowMgr::getInstance()->meshes.at(26)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(26)->SetPos(vec3(0.5f, 1.39f, 0.0f));
	windowMgr::getInstance()->meshes.at(26)->SetTexture(windowMgr::getInstance()->textures["keyLbl"]);
	// Select fire keyboard 
	windowMgr::getInstance()->meshes.at(27)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(27)->SetPos(vec3(0.5f, 1.07f, 0.0f));
	//windowMgr::getInstance()->meshes.at(27)->SetTexture(windowMgr::getInstance()->textures["aLbl"]);
	// Back reset keyboard
	windowMgr::getInstance()->meshes.at(28)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(28)->SetPos(vec3(0.5f, 0.75f, 0.0f));
	//windowMgr::getInstance()->meshes.at(28)->SetTexture(windowMgr::getInstance()->textures["bLbl"]);
	// Pause keyboard
	windowMgr::getInstance()->meshes.at(29)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(29)->SetPos(vec3(0.5f, 0.43f, 0.0f));
	//windowMgr::getInstance()->meshes.at(29)->SetTexture(windowMgr::getInstance()->textures["cLbl"]);
	// Up keyboard
	windowMgr::getInstance()->meshes.at(30)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(30)->SetPos(vec3(0.5f, 0.11f, 0.0f));
	//windowMgr::getInstance()->meshes.at(30)->SetTexture(windowMgr::getInstance()->textures["dLbl"]);
	// Left keyboard
	windowMgr::getInstance()->meshes.at(31)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(31)->SetPos(vec3(0.5f, -0.21f, 0.0f));
	//windowMgr::getInstance()->meshes.at(31)->SetTexture(windowMgr::getInstance()->textures["eLbl"]);
	// Down keyboard
	windowMgr::getInstance()->meshes.at(32)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(32)->SetPos(vec3(0.5f, -0.53f, 0.0f));
	//windowMgr::getInstance()->meshes.at(32)->SetTexture(windowMgr::getInstance()->textures["fLbl"]);
	// Right keyboard
	windowMgr::getInstance()->meshes.at(33)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(33)->SetPos(vec3(0.5f, -0.85f, 0.0f));
	//windowMgr::getInstance()->meshes.at(33)->SetTexture(windowMgr::getInstance()->textures["gLbl"]);
	// Jump keyboard
	windowMgr::getInstance()->meshes.at(34)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(34)->SetPos(vec3(0.5f, -1.17f, 0.0f));
	//windowMgr::getInstance()->meshes.at(34)->SetTexture(windowMgr::getInstance()->textures["hLbl"]);
	// Zoom in keyboard
	windowMgr::getInstance()->meshes.at(35)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(35)->SetPos(vec3(0.5f, -1.49, 0.0f));
	//windowMgr::getInstance()->meshes.at(35)->SetTexture(windowMgr::getInstance()->textures["iLbl"]);
	// Zoom out keyboard
	windowMgr::getInstance()->meshes.at(36)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(36)->SetPos(vec3(0.5f, -1.81, 0.0f));
	//windowMgr::getInstance()->meshes.at(36)->SetTexture(windowMgr::getInstance()->textures["jLbl"]);

	//**********KEYBOARD SETUP**************//
	windowMgr::getInstance()->gameKeyboardFunctions[0] = 81;
	windowMgr::getInstance()->gameKeyboardFunctions[1] = 69;
	windowMgr::getInstance()->gameKeyboardFunctions[2] = 80;
	windowMgr::getInstance()->gameKeyboardFunctions[3] = 87;
	windowMgr::getInstance()->gameKeyboardFunctions[4] = 68;
	windowMgr::getInstance()->gameKeyboardFunctions[5] = 83;
	windowMgr::getInstance()->gameKeyboardFunctions[6] = 65;
	windowMgr::getInstance()->gameKeyboardFunctions[7] = 90;
	windowMgr::getInstance()->gameKeyboardFunctions[8] = 82;
	windowMgr::getInstance()->gameKeyboardFunctions[9] = 70;

	// For all the functions
	for (int allKeyboardFunctions = 0; allKeyboardFunctions < 10; allKeyboardFunctions++)
	{
		// If keyboard function is equal to A then change texture to A
		if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 65)
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["aLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 66) // B
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["bLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 67) // C
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["cLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 68) // D
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["dLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 69) // E
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["eLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 70) // F
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["fLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 71) // G
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["gLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 72) // H
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["hLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 73) // I
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["iLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 74) // J
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["jLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 75) // K
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["kLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 76) // L
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["lLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 77) // M
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["mLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 78) // N
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["nLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 79) // O
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["oLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 80) // P
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["pLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 81) // Q
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["qLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 82) // R
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["rLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 83) // S
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["sLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 84) // T
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["tLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 85) // U
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["uLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 86) // V
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["vLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 87) // W
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["wLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 88) // X
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["xLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 89) // Y
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["yLbl"]);
		}
		else if (windowMgr::getInstance()->gameKeyboardFunctions[allKeyboardFunctions] == 90) // Z
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->textures["zLbl"]);
		}
	}
	
	//******CONTROLLER SETUP*************//
	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// If controller is connected 
	if (present == 1)
	{
		// Dected how many buttons the controller has
		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		// If the amount of buttons detected is equal to 18 then 
		if (buttonCount == 18)
		{
			cout << "Controller type = PS4! " << endl;
			// Setup the functions/buttons for ps4 controller - the function being the index and button being the equal value
			// FUNCTION/BUTTONS
			windowMgr::getInstance()->gameFunctions[0] = 2;
			windowMgr::getInstance()->gameFunctions[1] = 3;
			windowMgr::getInstance()->gameFunctions[2] = 0;
			windowMgr::getInstance()->gameFunctions[3] = 14;
			windowMgr::getInstance()->gameFunctions[4] = 15;
			windowMgr::getInstance()->gameFunctions[5] = 16;
			windowMgr::getInstance()->gameFunctions[6] = 17;
			windowMgr::getInstance()->gameFunctions[7] = 1;
			windowMgr::getInstance()->gameFunctions[8] = 4;
			windowMgr::getInstance()->gameFunctions[9] = 5;
			// For all the fucntions 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If the button is 0 then 
				if (windowMgr::getInstance()->gameFunctions[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[0]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[1]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[2]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[3]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[4]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[5]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[6]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[7]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[8]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[9]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[10]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[11]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[12]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 13)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[13]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 14)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[14]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 15)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[15]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 16)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[16]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 17)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[17]);
				}
			}
		}
		else
		{
			cout << "Controller type = XBOX360 OR OTHER! " << endl;
			// Setup the functions/buttons for xbox controller - the function being the index and button being the equal value
			// FUNCTION/BUTTONS
			windowMgr::getInstance()->gameFunctions[0] = 2;
			windowMgr::getInstance()->gameFunctions[1] = 3;
			windowMgr::getInstance()->gameFunctions[2] = 7;
			windowMgr::getInstance()->gameFunctions[3] = 10;
			windowMgr::getInstance()->gameFunctions[4] = 11;
			windowMgr::getInstance()->gameFunctions[5] = 12;
			windowMgr::getInstance()->gameFunctions[6] = 13;
			windowMgr::getInstance()->gameFunctions[7] = 1;
			windowMgr::getInstance()->gameFunctions[8] = 4;
			windowMgr::getInstance()->gameFunctions[9] = 5;
			// For all the buttons in the game 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If gamefunction equals button 0 then
				if (windowMgr::getInstance()->gameFunctions[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[0]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[6]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[8]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[9]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
				}
				else if (windowMgr::getInstance()->gameFunctions[allFunctions] == 13)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
				}
			}
		}
	}
}

// Draw stuff
void highscoreScene::Loop(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);

	// Update
	Update(win);

	// Render
	Render(win);
}

// Input 
void highscoreScene::Input(GLFWwindow* win)
{
	// If A is pressed and boolean equals false
	if (glfwGetKey(win, GLFW_KEY_A) && !aPressed)
	{
		aPressed = true;
		cout << "a PRESSED" << endl;
	}

	if (!glfwGetKey(win, GLFW_KEY_A) && aPressed) // If A is realised
	{
		cout << "A realised" << endl;
		// If a function is empty then
		if (isFunctionEmptyKeyboard) // Check if A is assigned to a function 
		{
			// Find the index of the gameFunction which has a value of 99
			indexAt99 = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 99));
			// Find the index of the game function whih is assigned to the button that has just been pressed
			indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 65));
			// Check if button just pressed has a function assigned to it
			if (65 == windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey])
			{
				// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
				windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
				windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 99;
			}

			// Make the original empty function equal to the button
			windowMgr::getInstance()->gameKeyboardFunctions[indexAt99] = 65;
			windowMgr::getInstance()->meshes.at(27 + indexAt99)->SetTexture(windowMgr::getInstance()->textures["aLbl"]);

			// Check if a function is equal to 99
			if (windowMgr::getInstance()->gameKeyboardFunctions[0] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[1] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[2] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[3] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[4] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[5] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[6] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[7] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[8] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[9] == 99)
			{
				isFunctionEmptyKeyboard = true; // Set bool to true if a function is empty
			}
			else
			{
				isFunctionEmptyKeyboard = false; // Set bool to false if no function is empty
			}
		}
		else
		{
			// Find the function index where the button has been pressed
			indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 65));
			// If function is assigned to a button then
			if (windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] == 65)
			{
				// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
				windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
				windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 99;
				// Set is Function Empty to true
				isFunctionEmptyKeyboard = true;
			}
		}

		aPressed = false;
	}

	// If A is pressed and boolean equals false
	if (glfwGetKey(win, GLFW_KEY_B) && !bPressed)
	{
		bPressed = true;
		cout << "b PRESSED" << endl;
	}

	if (!glfwGetKey(win, GLFW_KEY_B) && bPressed) // If A is realised
	{
		cout << "B realised" << endl;
		// If a function is empty then
		if (isFunctionEmptyKeyboard) // Check if A is assigned to a function 
		{
			// Find the index of the gameFunction which has a value of 99
			indexAt99 = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 99));
			// Find the index of the game function which is assigned to the button that has just been pressed
			indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 66));
			// Check if button just pressed has a function assigned to it
			if (66 == windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey])
			{
				// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
				windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
				windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 99;
			}

			// Make the original empty function equal to the button
			windowMgr::getInstance()->gameKeyboardFunctions[indexAt99] = 66;
			windowMgr::getInstance()->meshes.at(27 + indexAt99)->SetTexture(windowMgr::getInstance()->textures["bLbl"]);

			// Check if a function is equal to 99
			if (windowMgr::getInstance()->gameKeyboardFunctions[0] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[1] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[2] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[3] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[4] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[5] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[6] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[7] == 99 || windowMgr::getInstance()->gameKeyboardFunctions[8] == 99 ||
				windowMgr::getInstance()->gameKeyboardFunctions[9] == 99)
			{
				isFunctionEmptyKeyboard = true; // Set bool to true if a function is empty
			}
			else
			{
				isFunctionEmptyKeyboard = false; // Set bool to false if no function is empty
			}
		}
		else
		{
			// Find the function index where the button has been pressed
			indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 66));
			// If function is assigned to a button then
			if (windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] == 66)
			{
				// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
				windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
				windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 99;
				// Set is Function Empty to true
				isFunctionEmptyKeyboard = true;
			}
		}

		bPressed = false;
	}

	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// Dected how many buttons the controller has
	int buttonCount;
	const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	// If controller is connected 
	if (present == 1)
	{
		// If the amount of buttons detected is equal to 18 then - ps4 configurations
		if (buttonCount == 18)
		{
			// For loop which checks to see if buttons are pressed - i buttons
			for (int buttonNumber = 0; buttonNumber < 18; buttonNumber++)
			{
				// If button i is pressed then set corresponding boolean to true
				if (GLFW_PRESS == buttons[buttonNumber] && !buttonPressed[buttonNumber])
				{
					buttonPressed[buttonNumber] = true;
					cout << "Button Pressed: " << buttonNumber << endl;
				}

				// If a button has just been pressed and is longer being pressed then
				if (buttonPressed[buttonNumber] && !GLFW_PRESS == buttons[buttonNumber])
				{
					// If there is an empty function then
					if (isFunctionEmpty)
					{
						// Find the index of the gameFunction which has a value of 99
						indexAt99 = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, 99));
						// Find the index of the game function whih is assigned to the button that has just been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, buttonNumber));
						// Check if button just pressed has a function assigned to it
						if (buttonNumber == windowMgr::getInstance()->gameFunctions[indexAtButton])
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->meshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->gameFunctions[indexAtButton] = 99;
						}

						// Make the original empty function equal to the button
						windowMgr::getInstance()->gameFunctions[indexAt99] = buttonNumber;
						windowMgr::getInstance()->meshes.at(4 + (indexAt99 * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[buttonNumber]);

						// Check if a function is equal to 99
						if (windowMgr::getInstance()->gameFunctions[0] == 99 || windowMgr::getInstance()->gameFunctions[1] == 99 || windowMgr::getInstance()->gameFunctions[2] == 99 ||
							windowMgr::getInstance()->gameFunctions[3] == 99 || windowMgr::getInstance()->gameFunctions[4] == 99 || windowMgr::getInstance()->gameFunctions[5] == 99 ||
							windowMgr::getInstance()->gameFunctions[6] == 99 || windowMgr::getInstance()->gameFunctions[7] == 99 || windowMgr::getInstance()->gameFunctions[8] == 99 ||
							windowMgr::getInstance()->gameFunctions[9] == 99)
						{
							isFunctionEmpty = true; // Set bool to true if a function is empty
						}
						else
						{
							isFunctionEmpty = false; // Set bool to false if no function is empty
						}
					}
					else
					{
						// Find the function index where the button has been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, buttonNumber));
						// If function is assigned to a button then
						if (windowMgr::getInstance()->gameFunctions[indexAtButton] == buttonNumber)
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->meshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->gameFunctions[indexAtButton] = 99;
							// Set is Function Empty to true
							isFunctionEmpty = true;
						}
					}
					// Reset button pressed
					buttonPressed[buttonNumber] = false;
				}
			}
		}
		else
		{
			// For loop which checks to see if buttons are pressed
			for (int buttonNumber = 0; buttonNumber < 14; buttonNumber++)
			{
				// If button is pressed then set corresponding boolean to true
				if (GLFW_PRESS == buttons[buttonNumber] && !buttonPressed[buttonNumber])
				{
					buttonPressed[buttonNumber] = true;
					cout << "Button Pressed: " << buttonNumber << endl;
				}

				// If a button has just been pressed and is longer being pressed then
				if (buttonPressed[buttonNumber] && !GLFW_PRESS == buttons[buttonNumber])
				{
					// If there is an empty function then
					if (isFunctionEmpty)
					{
						// Find the index of the gameFunction which has a value of 99
						indexAt99 = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, 99));
						// Find the index of the game function whih is assigned to the button that has just been pressed
						indexAtButton = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, buttonNumber));
						// Check if button just pressed has a function assigned to it
						if (buttonNumber == windowMgr::getInstance()->gameFunctions[indexAtButton])
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->meshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->gameFunctions[indexAtButton] = 99;
						}

						// Make the original empty function equal to the button
						windowMgr::getInstance()->gameFunctions[indexAt99] = buttonNumber;
						windowMgr::getInstance()->meshes.at(4 + (indexAt99 * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[buttonNumber]);

						// Check if a function is equal to 99
						if (windowMgr::getInstance()->gameFunctions[0] == 99 || windowMgr::getInstance()->gameFunctions[1] == 99 || windowMgr::getInstance()->gameFunctions[2] == 99 ||
							windowMgr::getInstance()->gameFunctions[3] == 99 || windowMgr::getInstance()->gameFunctions[4] == 99 || windowMgr::getInstance()->gameFunctions[5] == 99 ||
							windowMgr::getInstance()->gameFunctions[6] == 99 || windowMgr::getInstance()->gameFunctions[7] == 99 || windowMgr::getInstance()->gameFunctions[8] == 99 ||
							windowMgr::getInstance()->gameFunctions[9] == 99)
						{
							isFunctionEmpty = true; // Set bool to true if a function is empty
						}
						else
						{
							isFunctionEmpty = false; // Set bool to false if no function is empty
						}
					}
					else
					{
						indexAtButton = std::distance(windowMgr::getInstance()->gameFunctions, std::find(windowMgr::getInstance()->gameFunctions, windowMgr::getInstance()->gameFunctions + 10, buttonNumber));
						// If function is assigned to a button then
						if (windowMgr::getInstance()->gameFunctions[indexAtButton] == buttonNumber)
						{
							// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
							windowMgr::getInstance()->meshes.at(4 + (indexAtButton * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
							windowMgr::getInstance()->gameFunctions[indexAtButton] = 99;
							// Set is Function Empty to true
							isFunctionEmpty = true;
						}
					}

					// Reset button pressed
					buttonPressed[buttonNumber] = false;
				}
			}
		}
	}
}

void highscoreScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
}

void highscoreScene::Render(GLFWwindow* win)
{
	// Calculate hud view*projection
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	for (int i = 0; i < meshesInScene; i++)
	{
		windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(i)->Draw();
	}

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY

	// Render any background stuff if required here

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
