#include "highscoreScene.h"
#include "windowMgr.h" // to access singleton

// Constructor
highscoreScene::highscoreScene() { }
// Deconstructor
highscoreScene::~highscoreScene() { }

void highscoreScene::Init(GLFWwindow * win)
{
	windowMgr::getInstance()->button_manager = 0;
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
	// Back Reset
	// Set backreset label
	windowMgr::getInstance()->meshes.at(5)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-2.7f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["backresetLbl"]);
	// Pause
	// Set pause label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(-2.7f, 0.43f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["pauseLbl"]);
	// Arrows
	// Up
	windowMgr::getInstance()->meshes.at(9)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(-2.7f, 0.11f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["upLbl"]);
	// Left
	windowMgr::getInstance()->meshes.at(11)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(-2.7f, -0.21f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Down 
	windowMgr::getInstance()->meshes.at(13)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(-2.7f, -0.53f, 0.0f));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["downLbl"]);
	// Right
	windowMgr::getInstance()->meshes.at(15)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(15)->SetPos(vec3(-2.7f, -0.85f, 0.0f));
	windowMgr::getInstance()->meshes.at(15)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
	// Jump
	windowMgr::getInstance()->meshes.at(17)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(17)->SetPos(vec3(-2.7f, -1.17f, 0.0f));
	windowMgr::getInstance()->meshes.at(17)->SetTexture(windowMgr::getInstance()->textures["jumpLbl"]);
	// Zoom In
	windowMgr::getInstance()->meshes.at(19)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(19)->SetPos(vec3(-2.7f, -1.50f, 0.0f));
	windowMgr::getInstance()->meshes.at(19)->SetTexture(windowMgr::getInstance()->textures["zoomInLbl"]);
	// Zoom Out
	windowMgr::getInstance()->meshes.at(21)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(21)->SetPos(vec3(-2.7f, -1.82f, 0.0f));
	windowMgr::getInstance()->meshes.at(21)->SetTexture(windowMgr::getInstance()->textures["zoomOutLbl"]);
	// Main Menu
	windowMgr::getInstance()->meshes.at(23)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(23)->SetPos(vec3(2.2f, -1.8f, 0.0f));
	windowMgr::getInstance()->meshes.at(23)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
	// Set the player one and player two lbls
	// P1
	windowMgr::getInstance()->meshes.at(24)->SetScale(1.8f, 0.45f);
	windowMgr::getInstance()->meshes.at(24)->SetPos(vec3(-2.0f, 1.81f, 0.0f));
	windowMgr::getInstance()->meshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblGreen"]);
	// P2
	windowMgr::getInstance()->meshes.at(25)->SetScale(1.8f, 0.45f);
	windowMgr::getInstance()->meshes.at(25)->SetPos(vec3(0.0f, 1.81f, 0.0f));
	windowMgr::getInstance()->meshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblRed"]);
	// Keyboard Label
	windowMgr::getInstance()->meshes.at(26)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(26)->SetPos(vec3(0.5f, 1.39f, 0.0f));
	windowMgr::getInstance()->meshes.at(26)->SetTexture(windowMgr::getInstance()->textures["keyLbl"]);
	// Set selectfire button label controller button
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(-1.1f, 1.07f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
	// Set backreset button label controller button
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(-1.1f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
	// Set pause button label controller button
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(-1.1f, 0.43f, 0.0f));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
	// Set up controller button
	windowMgr::getInstance()->meshes.at(10)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(-1.1f, 0.11f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
	// Set left controller button
	windowMgr::getInstance()->meshes.at(12)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(-1.1f, -0.21f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
	// Set down controller button
	windowMgr::getInstance()->meshes.at(14)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(14)->SetPos(vec3(-1.1f, -0.53f, 0.0f));
	windowMgr::getInstance()->meshes.at(14)->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
	// Set right controller button
	windowMgr::getInstance()->meshes.at(16)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(16)->SetPos(vec3(-1.1f, -0.85f, 0.0f));
	windowMgr::getInstance()->meshes.at(16)->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
	// Set jump controller button
	windowMgr::getInstance()->meshes.at(18)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(18)->SetPos(vec3(-1.1f, -1.17f, 0.0f));
	windowMgr::getInstance()->meshes.at(18)->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
	// Set zoom in controller button
	windowMgr::getInstance()->meshes.at(20)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(20)->SetPos(vec3(-1.1f, -1.50f, 0.0f));
	windowMgr::getInstance()->meshes.at(20)->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
	// Set zoom out controller button
	windowMgr::getInstance()->meshes.at(22)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(22)->SetPos(vec3(-1.1f, -1.82f, 0.0f));
	windowMgr::getInstance()->meshes.at(22)->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
	// Select fire keyboard 
	windowMgr::getInstance()->meshes.at(27)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(27)->SetPos(vec3(0.5f, 1.07f, 0.0f));
	// Back reset keyboard
	windowMgr::getInstance()->meshes.at(28)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(28)->SetPos(vec3(0.5f, 0.75f, 0.0f));
	// Pause keyboard
	windowMgr::getInstance()->meshes.at(29)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(29)->SetPos(vec3(0.5f, 0.43f, 0.0f));
	// Up keyboard
	windowMgr::getInstance()->meshes.at(30)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(30)->SetPos(vec3(0.5f, 0.11f, 0.0f));
	// Left keyboard
	windowMgr::getInstance()->meshes.at(31)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(31)->SetPos(vec3(0.5f, -0.21f, 0.0f));
	// Down keyboard
	windowMgr::getInstance()->meshes.at(32)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(32)->SetPos(vec3(0.5f, -0.53f, 0.0f));
	// Right keyboard
	windowMgr::getInstance()->meshes.at(33)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(33)->SetPos(vec3(0.5f, -0.85f, 0.0f));
	// Jump keyboard
	windowMgr::getInstance()->meshes.at(34)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(34)->SetPos(vec3(0.5f, -1.17f, 0.0f));
	// Zoom in keyboard
	windowMgr::getInstance()->meshes.at(35)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(35)->SetPos(vec3(0.5f, -1.49, 0.0f));
	// Zoom out keyboard
	windowMgr::getInstance()->meshes.at(36)->SetScale(0.7f, 0.35f);
	windowMgr::getInstance()->meshes.at(36)->SetPos(vec3(0.5f, -1.81, 0.0f));
	// Player using controller one
	windowMgr::getInstance()->meshes.at(37)->SetScale(2.0f, 1.0f);
	windowMgr::getInstance()->meshes.at(37)->SetPos(vec3(2.2f, -0.71f, 0.0f));
	windowMgr::getInstance()->meshes.at(37)->SetTexture(windowMgr::getInstance()->textures["playerUsingLbl"]);
	// Set up number of levels label
	windowMgr::getInstance()->meshes.at(38)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(38)->SetPos(vec3(2.2f, -1.3, 0.0));
	windowMgr::getInstance()->meshes.at(38)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);
	// Set left arrow label
	windowMgr::getInstance()->meshes.at(39)->SetScale(0.4f, 0.4f);
	windowMgr::getInstance()->meshes.at(39)->SetPos(vec3(1.7f, -1.3, 0.0));
	windowMgr::getInstance()->meshes.at(39)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
	// Set right arrow label
	windowMgr::getInstance()->meshes.at(40)->SetScale(0.4f, 0.4f);
	windowMgr::getInstance()->meshes.at(40)->SetPos(vec3(2.7f, -1.3, 0.0));
	windowMgr::getInstance()->meshes.at(40)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Select an option label 
	windowMgr::getInstance()->meshes.at(41)->SetScale(2.0f, 1.6f);
	windowMgr::getInstance()->meshes.at(41)->SetPos(vec3(2.2f, 0.7, 0.0));
	windowMgr::getInstance()->meshes.at(41)->SetTexture(windowMgr::getInstance()->textures["selectOptionLbl"]);

	// Default load player one controls
	InitPlayerButtonsPlayerOne(win);

}

void highscoreScene::InitPlayerButtonsPlayerOne(GLFWwindow * win)
{
	// For all the functions
	for (int allKeyboardFunctions = 0; allKeyboardFunctions < 10; allKeyboardFunctions++)
	{
		// If keyboard function is equal to A then change texture to A
		
		if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 65)
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[16]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 66) // B
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[17]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 67) // C
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[18]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 68) // D
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[19]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 69) // E
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[20]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 70) // F
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[21]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 71) // G
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[22]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 72) // H
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[23]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 73) // I
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[24]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 74) // J
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[25]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 75) // K
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[26]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 76) // L
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[27]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 77) // M
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[28]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 78) // N
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[29]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 79) // O
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[30]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 80) // P
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[31]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 81) // Q
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[32]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 82) // R
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[33]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 83) // S
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[34]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 84) // T
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[35]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 85) // U
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[36]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 86) // V
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[37]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 87) // W
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[38]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 88) // X
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[39]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 89) // Y
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[40]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPOne[allKeyboardFunctions] == 90) // Z
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[41]);
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
			// For all the fucntions 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If the button is 0 then 
				if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[0]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[1]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[2]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[3]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[4]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[5]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[6]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[7]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[8]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[9]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[10]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[11]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[12]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 13)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[13]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 14)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[14]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 15)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[15]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 16)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[16]);
				}
				else if (windowMgr::getInstance()->controllerPSPOne[allFunctions] == 17)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[17]);
				}
			}
		}
		else
		{
			cout << "Controller type = XBOX360 OR OTHER! " << endl;
			// Setup the functions/buttons for xbox controller - the function being the index and button being the equal value
			// For all the buttons in the game 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If gamefunction equals button 0 then
				if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[0]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[6]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[8]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[9]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
				}
				else if (windowMgr::getInstance()->controllerXboxPOne[allFunctions] == 13)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[13]);
				}
			}
		}
	}
}

void highscoreScene::InitPlayerButtonsPlayerTwo(GLFWwindow * win)
{
	// For all the functions
	for (int allKeyboardFunctions = 0; allKeyboardFunctions < 10; allKeyboardFunctions++)
	{
		// If keyboard function is equal to A then change texture to A

		if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 65)
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[16]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 66) // B
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[17]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 67) // C
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[18]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 68) // D
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[19]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 69) // E
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[20]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 70) // F
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[21]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 71) // G
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[22]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 72) // H
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[23]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 73) // I
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[24]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 74) // J
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[25]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 75) // K
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[26]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 76) // L
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[27]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 77) // M
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[28]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 78) // N
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[29]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 79) // O
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[30]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 80) // P
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[31]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 81) // Q
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[32]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 82) // R
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[33]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 83) // S
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[34]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 84) // T
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[35]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 85) // U
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[36]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 86) // V
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[37]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 87) // W
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[38]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 88) // X
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[39]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 89) // Y
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[40]);
		}
		else if (windowMgr::getInstance()->keyboardFunctionsPTwo[allKeyboardFunctions] == 90) // Z
		{
			windowMgr::getInstance()->meshes.at(27 + allKeyboardFunctions)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[41]);
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
			// For all the fucntions 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If the button is 0 then 
				if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[0]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[1]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[2]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[3]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[4]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[5]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[6]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[7]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[8]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[9]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[10]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[11]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[12]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 13)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[13]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 14)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[14]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 15)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[15]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 16)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[16]);
				}
				else if (windowMgr::getInstance()->controllerPSPTwo[allFunctions] == 17)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[17]);
				}
			}
		}
		else
		{
			cout << "Controller type = XBOX360 OR OTHER! " << endl;
			// Setup the functions/buttons for xbox controller - the function being the index and button being the equal value
			// For all the buttons in the game 
			for (int allFunctions = 0; allFunctions < 10; allFunctions++)
			{
				// If gamefunction equals button 0 then
				if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 0)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[0]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 1)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[1]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 2)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[2]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 3)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[3]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 4)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[4]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 5)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[5]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 6)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[6]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 7)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[7]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 8)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[8]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 9)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[9]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 10)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[10]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 11)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[11]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 12)
				{
					windowMgr::getInstance()->meshes.at(4 + (allFunctions * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[12]);
				}
				else if (windowMgr::getInstance()->controllerXboxPTwo[allFunctions] == 13)
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
	//Tracks Mouse 
	Track_Mouse(win);
	// Render
	Render(win);
}

//tracks mouse
void highscoreScene::Track_Mouse(GLFWwindow * win)
{
	glfwGetCursorPos(win, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if ((windowMgr::getInstance()->mouse_y >= 13 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 94 * windowMgr::getInstance()->windowScale))
	{
		//this is to highlightplayer 1
		if (windowMgr::getInstance()->mouse_x <= 524 && windowMgr::getInstance()->mouse_x >= 203)
		{
			windowMgr::getInstance()->button_manager = 1;
		}
		//this is to highlight player 2
		else if (windowMgr::getInstance()->mouse_x <= 965 && windowMgr::getInstance()->mouse_x >= 631)
		{
			windowMgr::getInstance()->button_manager = 2;
		}
	}
	//this is for main menu button
	else if ((windowMgr::getInstance()->mouse_x >= 1086 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1469 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 809 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 877 * windowMgr::getInstance()->windowScale))
	{
		windowMgr::getInstance()->button_manager = 3;
	}
	//this is for main menu button
	else if ((windowMgr::getInstance()->mouse_y >= 703 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 758 * windowMgr::getInstance()->windowScale))
	{	
		//this is to highlights left arrow
		if (windowMgr::getInstance()->mouse_x >= 1127 && windowMgr::getInstance()->mouse_x <= 1203)
		{
			windowMgr::getInstance()->button_manager = 4;
		}
		//this is to highlight right arrow
		else if (windowMgr::getInstance()->mouse_x >= 1351 && windowMgr::getInstance()->mouse_x <= 1429)
		{
			windowMgr::getInstance()->button_manager = 5;
		}
	}
}

//whenever a click occurs
void highscoreScene::Click(GLFWwindow * win)
{
	// Create the outputFile object
	ofstream outputFile;
	switch (windowMgr::getInstance()->button_manager)
	{
		case 1:
			windowMgr::getInstance()->meshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblGreen"]);
			windowMgr::getInstance()->meshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblRed"]);
			//put in code here for player 1
			InitPlayerButtonsPlayerOne(win);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(24)->SetTexture(windowMgr::getInstance()->textures["playerOneLblRed"]);
			windowMgr::getInstance()->meshes.at(25)->SetTexture(windowMgr::getInstance()->textures["playerTwoLblGreen"]);
			//put in code here for player 2
			InitPlayerButtonsPlayerTwo(win);
			break;
		//to go back to main menu
		case 3:
			// Set the output file
			outputFile.open("..\\NuttyPutters\\input\\p1XboxController.txt");
			// Loop through total number of entries 
			for (int l = 0; l < 10; l++)
			{
				// Output the values to the output file
				outputFile << windowMgr::getInstance()->gameFunctions[l] << endl;
			}
			windowMgr::getInstance()->sceneManager.changeScene(1);
			break;
		//left arrow function
		case 4:
			///
			cout << "oui" << endl;
			///put stuff here 
			///
			break;
		//right arrow functio
		case 5:
			///
			cout << "si" << endl;
			///put stuff here 
			///
			break;
	}
}

// Input 
void highscoreScene::Input(GLFWwindow* win)
{
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		windowMgr::getInstance()->mouseLpressed = true;
	}

	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (windowMgr::getInstance()->mouseLpressed)
		{
			Click(win);
			windowMgr::getInstance()->mouseLpressed = false;
		}
	}

	// If key is pressed and boolean equals false then set bool to true
	if (glfwGetKey(win, GLFW_KEY_COMMA) && !keyboardButtonPressed[0])
	{
		keyboardButtonPressed[0] = true;
	}

	// If key is no longer pressed and bool is true then
	if (!glfwGetKey(win, GLFW_KEY_COMMA) && keyboardButtonPressed[0])
	{
		updateKeyboardFunctionsList(0, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_MINUS) && !keyboardButtonPressed[1])
	{
		keyboardButtonPressed[1] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_MINUS) && keyboardButtonPressed[1])
	{
		updateKeyboardFunctionsList(1, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_PERIOD) && !keyboardButtonPressed[2])
	{
		keyboardButtonPressed[2] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PERIOD) && keyboardButtonPressed[2])
	{
		updateKeyboardFunctionsList(2, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_SLASH) && !keyboardButtonPressed[3])
	{
		keyboardButtonPressed[3] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SLASH) && keyboardButtonPressed[3])
	{
		updateKeyboardFunctionsList(3, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_0) && !keyboardButtonPressed[4])
	{
		keyboardButtonPressed[4] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_0) && keyboardButtonPressed[4])
	{
		updateKeyboardFunctionsList(4, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_1) && !keyboardButtonPressed[5])
	{
		keyboardButtonPressed[5] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_1) && keyboardButtonPressed[5])
	{
		updateKeyboardFunctionsList(5, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_2) && !keyboardButtonPressed[6])
	{
		keyboardButtonPressed[6] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_2) && keyboardButtonPressed[6])
	{
		updateKeyboardFunctionsList(6, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_3) && !keyboardButtonPressed[7])
	{
		keyboardButtonPressed[7] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_3) && keyboardButtonPressed[7])
	{
		updateKeyboardFunctionsList(7, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_4) && !keyboardButtonPressed[8])
	{
		keyboardButtonPressed[8] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_4) && keyboardButtonPressed[8])
	{
		updateKeyboardFunctionsList(8, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_5) && !keyboardButtonPressed[9])
	{
		keyboardButtonPressed[9] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_5) && keyboardButtonPressed[9])
	{
		updateKeyboardFunctionsList(9, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_6) && !keyboardButtonPressed[10])
	{
		keyboardButtonPressed[10] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_6) && keyboardButtonPressed[10])
	{
		updateKeyboardFunctionsList(10, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_7) && !keyboardButtonPressed[11])
	{
		keyboardButtonPressed[11] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_7) && keyboardButtonPressed[11])
	{
		updateKeyboardFunctionsList(11, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_8) && !keyboardButtonPressed[12])
	{
		keyboardButtonPressed[12] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_8) && keyboardButtonPressed[12])
	{
		updateKeyboardFunctionsList(12, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_9) && !keyboardButtonPressed[13])
	{
		keyboardButtonPressed[13] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_9) && keyboardButtonPressed[13])
	{
		updateKeyboardFunctionsList(13, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_SEMICOLON) && !keyboardButtonPressed[14])
	{
		keyboardButtonPressed[14] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SEMICOLON) && keyboardButtonPressed[14])
	{
		updateKeyboardFunctionsList(14, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_EQUAL) && !keyboardButtonPressed[15])
	{
		keyboardButtonPressed[15] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_EQUAL) && keyboardButtonPressed[15])
	{
		updateKeyboardFunctionsList(15, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_A) && !keyboardButtonPressed[16])
	{
		keyboardButtonPressed[16] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_A) && keyboardButtonPressed[16])
	{
		updateKeyboardFunctionsList(16, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_B) && !keyboardButtonPressed[17])
	{
		keyboardButtonPressed[17] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_B) && keyboardButtonPressed[17])
	{
		updateKeyboardFunctionsList(17, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_C) && !keyboardButtonPressed[18])
	{
		keyboardButtonPressed[18] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_C) && keyboardButtonPressed[18])
	{
		updateKeyboardFunctionsList(18, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_D) && !keyboardButtonPressed[19])
	{
		keyboardButtonPressed[19] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_D) && keyboardButtonPressed[19])
	{
		updateKeyboardFunctionsList(19, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_E) && !keyboardButtonPressed[20])
	{
		keyboardButtonPressed[20] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_E) && keyboardButtonPressed[20])
	{
		updateKeyboardFunctionsList(20, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_F) && !keyboardButtonPressed[21])
	{
		keyboardButtonPressed[21] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F) && keyboardButtonPressed[21])
	{
		updateKeyboardFunctionsList(21, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_G) && !keyboardButtonPressed[22])
	{
		keyboardButtonPressed[22] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_G) && keyboardButtonPressed[22])
	{
		updateKeyboardFunctionsList(22, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_H) && !keyboardButtonPressed[23])
	{
		keyboardButtonPressed[23] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_H) && keyboardButtonPressed[23])
	{
		updateKeyboardFunctionsList(23, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_I) && !keyboardButtonPressed[24])
	{
		keyboardButtonPressed[24] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_I) && keyboardButtonPressed[24])
	{
		updateKeyboardFunctionsList(24, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_J) && !keyboardButtonPressed[25])
	{
		keyboardButtonPressed[25] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_J) && keyboardButtonPressed[25])
	{
		updateKeyboardFunctionsList(25, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_K) && !keyboardButtonPressed[26])
	{
		keyboardButtonPressed[26] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_K) && keyboardButtonPressed[26])
	{
		updateKeyboardFunctionsList(26, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_L) && !keyboardButtonPressed[27])
	{
		keyboardButtonPressed[27] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_L) && keyboardButtonPressed[27])
	{
		updateKeyboardFunctionsList(27, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_M) && !keyboardButtonPressed[28])
	{
		keyboardButtonPressed[28] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_M) && keyboardButtonPressed[28])
	{
		updateKeyboardFunctionsList(28, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_N) && !keyboardButtonPressed[29])
	{
		keyboardButtonPressed[29] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_N) && keyboardButtonPressed[29])
	{
		updateKeyboardFunctionsList(29, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_O) && !keyboardButtonPressed[30])
	{
		keyboardButtonPressed[30] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_O) && keyboardButtonPressed[30])
	{
		updateKeyboardFunctionsList(30, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_P) && !keyboardButtonPressed[31])
	{
		keyboardButtonPressed[31] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_P) && keyboardButtonPressed[31])
	{
		updateKeyboardFunctionsList(31, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Q) && !keyboardButtonPressed[32])
	{
		keyboardButtonPressed[32] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Q) && keyboardButtonPressed[32])
	{
		updateKeyboardFunctionsList(32, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_R) && !keyboardButtonPressed[33])
	{
		keyboardButtonPressed[33] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_R) && keyboardButtonPressed[33])
	{
		updateKeyboardFunctionsList(33, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_S) && !keyboardButtonPressed[34])
	{
		keyboardButtonPressed[34] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_S) && keyboardButtonPressed[34])
	{
		updateKeyboardFunctionsList(34, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_T) && !keyboardButtonPressed[35])
	{
		keyboardButtonPressed[35] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_T) && keyboardButtonPressed[35])
	{
		updateKeyboardFunctionsList(35, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_U) && !keyboardButtonPressed[36])
	{
		keyboardButtonPressed[36] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_U) && keyboardButtonPressed[36])
	{
		updateKeyboardFunctionsList(36, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_V) && !keyboardButtonPressed[37])
	{
		keyboardButtonPressed[37] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_V) && keyboardButtonPressed[37])
	{
		updateKeyboardFunctionsList(37, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_W) && !keyboardButtonPressed[38])
	{
		keyboardButtonPressed[38] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_W) && keyboardButtonPressed[38])
	{
		updateKeyboardFunctionsList(38, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_X) && !keyboardButtonPressed[39])
	{
		keyboardButtonPressed[39] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_X) && keyboardButtonPressed[39])
	{
		updateKeyboardFunctionsList(39, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Y) && !keyboardButtonPressed[40])
	{
		keyboardButtonPressed[40] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Y) && keyboardButtonPressed[40])
	{
		updateKeyboardFunctionsList(40, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_Z) && !keyboardButtonPressed[41])
	{
		keyboardButtonPressed[41] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_Z) && keyboardButtonPressed[41])
	{
		updateKeyboardFunctionsList(41, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_BRACKET) && !keyboardButtonPressed[42])
	{
		keyboardButtonPressed[42] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_BRACKET) && keyboardButtonPressed[42])
	{
		updateKeyboardFunctionsList(42, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_BACKSLASH) && !keyboardButtonPressed[43])
	{
		keyboardButtonPressed[43] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_BACKSLASH) && keyboardButtonPressed[43])
	{
		updateKeyboardFunctionsList(43, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_BRACKET) && !keyboardButtonPressed[44])
	{
		keyboardButtonPressed[44] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_BRACKET) && keyboardButtonPressed[44])
	{
		updateKeyboardFunctionsList(44, 49);
	}

	if (glfwGetKey(win, GLFW_KEY_ESCAPE) && !keyboardButtonPressed[45])
	{
		keyboardButtonPressed[45] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ESCAPE) && keyboardButtonPressed[45])
	{
		updateKeyboardFunctionsList(45, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_ENTER) && !keyboardButtonPressed[46])
	{
		keyboardButtonPressed[46] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ENTER) && keyboardButtonPressed[46])
	{
		updateKeyboardFunctionsList(46, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_TAB) && !keyboardButtonPressed[47])
	{
		keyboardButtonPressed[47] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_TAB) && keyboardButtonPressed[47])
	{
		updateKeyboardFunctionsList(47, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_BACKSPACE) && !keyboardButtonPressed[48])
	{
		keyboardButtonPressed[48] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_BACKSPACE) && keyboardButtonPressed[48])
	{
		updateKeyboardFunctionsList(48, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_INSERT) && !keyboardButtonPressed[49])
	{
		keyboardButtonPressed[49] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_INSERT) && keyboardButtonPressed[49])
	{
		updateKeyboardFunctionsList(49, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_DELETE) && !keyboardButtonPressed[50])
	{
		keyboardButtonPressed[50] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DELETE) && keyboardButtonPressed[50])
	{
		updateKeyboardFunctionsList(50, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT) && !keyboardButtonPressed[51])
	{
		keyboardButtonPressed[51] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT) && keyboardButtonPressed[51])
	{
		updateKeyboardFunctionsList(51, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT) && !keyboardButtonPressed[52])
	{
		keyboardButtonPressed[52] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT) && keyboardButtonPressed[52])
	{
		updateKeyboardFunctionsList(52, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_DOWN) && !keyboardButtonPressed[53])
	{
		keyboardButtonPressed[53] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_DOWN) && keyboardButtonPressed[53])
	{
		updateKeyboardFunctionsList(53, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_UP) && !keyboardButtonPressed[54])
	{
		keyboardButtonPressed[54] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_UP) && keyboardButtonPressed[54])
	{
		updateKeyboardFunctionsList(54, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_PAGE_UP) && !keyboardButtonPressed[55])
	{
		keyboardButtonPressed[55] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAGE_UP) && keyboardButtonPressed[55])
	{
		updateKeyboardFunctionsList(55, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_PAGE_DOWN) && !keyboardButtonPressed[56])
	{
		keyboardButtonPressed[56] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAGE_DOWN) && keyboardButtonPressed[56])
	{
		updateKeyboardFunctionsList(56, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_HOME) && !keyboardButtonPressed[57])
	{
		keyboardButtonPressed[57] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_HOME) && keyboardButtonPressed[57])
	{
		updateKeyboardFunctionsList(57, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_END) && !keyboardButtonPressed[58])
	{
		keyboardButtonPressed[58] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_END) && keyboardButtonPressed[58])
	{
		updateKeyboardFunctionsList(58, 211);
	}

	if (glfwGetKey(win, GLFW_KEY_CAPS_LOCK) && !keyboardButtonPressed[59])
	{
		keyboardButtonPressed[59] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_CAPS_LOCK) && keyboardButtonPressed[59])
	{
		updateKeyboardFunctionsList(59, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_SCROLL_LOCK) && !keyboardButtonPressed[60])
	{
		keyboardButtonPressed[60] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_SCROLL_LOCK) && keyboardButtonPressed[60])
	{
		updateKeyboardFunctionsList(60, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_NUM_LOCK) && !keyboardButtonPressed[61])
	{
		keyboardButtonPressed[61] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_NUM_LOCK) && keyboardButtonPressed[61])
	{
		updateKeyboardFunctionsList(61, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_NUM_LOCK) && !keyboardButtonPressed[62])
	{
		keyboardButtonPressed[62] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_NUM_LOCK) && keyboardButtonPressed[62])
	{
		updateKeyboardFunctionsList(62, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_PAUSE) && !keyboardButtonPressed[63])
	{
		keyboardButtonPressed[63] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_PAUSE) && keyboardButtonPressed[63])
	{
		updateKeyboardFunctionsList(63, 221);
	}

	if (glfwGetKey(win, GLFW_KEY_F1) && !keyboardButtonPressed[64])
	{
		keyboardButtonPressed[64] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F1) && keyboardButtonPressed[64])
	{
		updateKeyboardFunctionsList(64, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F2) && !keyboardButtonPressed[65])
	{
		keyboardButtonPressed[65] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F2) && keyboardButtonPressed[65])
	{
		updateKeyboardFunctionsList(65, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F3) && !keyboardButtonPressed[66])
	{
		keyboardButtonPressed[66] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F3) && keyboardButtonPressed[66])
	{
		updateKeyboardFunctionsList(66, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F4) && !keyboardButtonPressed[67])
	{
		keyboardButtonPressed[67] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F4) && keyboardButtonPressed[67])
	{
		updateKeyboardFunctionsList(67, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F5) && !keyboardButtonPressed[68])
	{
		keyboardButtonPressed[68] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F5) && keyboardButtonPressed[68])
	{
		updateKeyboardFunctionsList(68, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F6) && !keyboardButtonPressed[69])
	{
		keyboardButtonPressed[69] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F6) && keyboardButtonPressed[69])
	{
		updateKeyboardFunctionsList(69, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F7) && !keyboardButtonPressed[70])
	{
		keyboardButtonPressed[70] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F7) && keyboardButtonPressed[70])
	{
		updateKeyboardFunctionsList(70, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F8) && !keyboardButtonPressed[71])
	{
		keyboardButtonPressed[71] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F8) && keyboardButtonPressed[71])
	{
		updateKeyboardFunctionsList(71, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F9) && !keyboardButtonPressed[72])
	{
		keyboardButtonPressed[72] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F9) && keyboardButtonPressed[72])
	{
		updateKeyboardFunctionsList(72, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F10) && !keyboardButtonPressed[73])
	{
		keyboardButtonPressed[73] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F10) && keyboardButtonPressed[73])
	{
		updateKeyboardFunctionsList(73, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F11) && !keyboardButtonPressed[74])
	{
		keyboardButtonPressed[74] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F11) && keyboardButtonPressed[74])
	{
		updateKeyboardFunctionsList(74, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_F12) && !keyboardButtonPressed[75])
	{
		keyboardButtonPressed[75] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_F12) && keyboardButtonPressed[75])
	{
		updateKeyboardFunctionsList(75, 226);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_0) && !keyboardButtonPressed[76])
	{
		keyboardButtonPressed[76] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_0) && keyboardButtonPressed[76])
	{
		updateKeyboardFunctionsList(76, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_1) && !keyboardButtonPressed[77])
	{
		keyboardButtonPressed[77] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_1) && keyboardButtonPressed[77])
	{
		updateKeyboardFunctionsList(77, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_2) && !keyboardButtonPressed[78])
	{
		keyboardButtonPressed[78] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_2) && keyboardButtonPressed[78])
	{
		updateKeyboardFunctionsList(78, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_3) && !keyboardButtonPressed[79])
	{
		keyboardButtonPressed[79] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_3) && keyboardButtonPressed[79])
	{
		updateKeyboardFunctionsList(79, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_4) && !keyboardButtonPressed[80])
	{
		keyboardButtonPressed[80] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_4) && keyboardButtonPressed[80])
	{
		updateKeyboardFunctionsList(80, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_5) && !keyboardButtonPressed[81])
	{
		keyboardButtonPressed[81] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_5) && keyboardButtonPressed[81])
	{
		updateKeyboardFunctionsList(81, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_6) && !keyboardButtonPressed[82])
	{
		keyboardButtonPressed[82] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_6) && keyboardButtonPressed[82])
	{
		updateKeyboardFunctionsList(82, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_7) && !keyboardButtonPressed[83])
	{
		keyboardButtonPressed[83] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_7) && keyboardButtonPressed[83])
	{
		updateKeyboardFunctionsList(83, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_8) && !keyboardButtonPressed[84])
	{
		keyboardButtonPressed[84] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_8) && keyboardButtonPressed[84])
	{
		updateKeyboardFunctionsList(84, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_9) && !keyboardButtonPressed[85])
	{
		keyboardButtonPressed[85] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_9) && keyboardButtonPressed[85])
	{
		updateKeyboardFunctionsList(85, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_DECIMAL) && !keyboardButtonPressed[86])
	{
		keyboardButtonPressed[86] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_DECIMAL) && keyboardButtonPressed[86])
	{
		updateKeyboardFunctionsList(86, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_DIVIDE) && !keyboardButtonPressed[87])
	{
		keyboardButtonPressed[87] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_DIVIDE) && keyboardButtonPressed[87])
	{
		updateKeyboardFunctionsList(87, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_MULTIPLY) && !keyboardButtonPressed[88])
	{
		keyboardButtonPressed[88] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_MULTIPLY) && keyboardButtonPressed[88])
	{
		updateKeyboardFunctionsList(88, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_SUBTRACT) && !keyboardButtonPressed[89])
	{
		keyboardButtonPressed[89] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_SUBTRACT) && keyboardButtonPressed[89])
	{
		updateKeyboardFunctionsList(89, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_ADD) && !keyboardButtonPressed[90])
	{
		keyboardButtonPressed[90] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_ADD) && keyboardButtonPressed[90])
	{
		updateKeyboardFunctionsList(90, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_ENTER) && !keyboardButtonPressed[91])
	{
		keyboardButtonPressed[91] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_ENTER) && keyboardButtonPressed[91])
	{
		updateKeyboardFunctionsList(91, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_KP_EQUAL) && !keyboardButtonPressed[92])
	{
		keyboardButtonPressed[92] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_KP_EQUAL) && keyboardButtonPressed[92])
	{
		updateKeyboardFunctionsList(92, 244);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) && !keyboardButtonPressed[93])
	{
		keyboardButtonPressed[93] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) && keyboardButtonPressed[93])
	{
		updateKeyboardFunctionsList(93, 230);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) && !keyboardButtonPressed[94])
	{
		keyboardButtonPressed[94] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_CONTROL) && keyboardButtonPressed[94])
	{
		updateKeyboardFunctionsList(94, 230);
	}

	if (glfwGetKey(win, GLFW_KEY_LEFT_ALT) && !keyboardButtonPressed[95])
	{
		keyboardButtonPressed[95] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT_ALT) && keyboardButtonPressed[95])
	{
		updateKeyboardFunctionsList(95, 230);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) && !keyboardButtonPressed[96])
	{
		keyboardButtonPressed[96] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_SHIFT) && keyboardButtonPressed[96])
	{
		updateKeyboardFunctionsList(96, 230);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) && !keyboardButtonPressed[97])
	{
		keyboardButtonPressed[97] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_CONTROL) && keyboardButtonPressed[97])
	{
		updateKeyboardFunctionsList(97, 230);
	}

	if (glfwGetKey(win, GLFW_KEY_RIGHT_ALT) && !keyboardButtonPressed[98])
	{
		keyboardButtonPressed[98] = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT_ALT) && keyboardButtonPressed[98])
	{
		updateKeyboardFunctionsList(98, 230);
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

// Updates the keyboard function array
void highscoreScene::updateKeyboardFunctionsList(int keyboardButtonNumber, int additionalNumber)
{
	if (isFunctionEmptyKeyboard) // Check if there is an empty keyboard function
	{
		// Find the index of the gameKeyboardFunctions which has a value of 999
		indexAt99 = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, 999));
		// Find the index of the gameKeyboardFunctions which is assigned to the button that has just been pressed
		indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, keyboardButtonNumber + additionalNumber));
		// Check if button just pressed has a function assigned to it
		if (windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] == keyboardButtonNumber + additionalNumber)
		{
			// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
			windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
			windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 999;
		}

		// Make the original empty function equal to the button
		windowMgr::getInstance()->gameKeyboardFunctions[indexAt99] = keyboardButtonNumber + additionalNumber;
		windowMgr::getInstance()->meshes.at(27 + indexAt99)->SetTexture(windowMgr::getInstance()->buttonsKeyboardOne[keyboardButtonNumber]);

		// Check if a function is equal to 99
		if (windowMgr::getInstance()->gameKeyboardFunctions[0] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[1] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[2] == 999 ||
			windowMgr::getInstance()->gameKeyboardFunctions[3] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[4] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[5] == 999 ||
			windowMgr::getInstance()->gameKeyboardFunctions[6] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[7] == 999 || windowMgr::getInstance()->gameKeyboardFunctions[8] == 999 ||
			windowMgr::getInstance()->gameKeyboardFunctions[9] == 999)
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
		indexAtKey = std::distance(windowMgr::getInstance()->gameKeyboardFunctions, std::find(windowMgr::getInstance()->gameKeyboardFunctions, windowMgr::getInstance()->gameKeyboardFunctions + 10, keyboardButtonNumber + additionalNumber));
		// If function is assigned to a button then
		if (windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] == keyboardButtonNumber + additionalNumber)
		{
			// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
			windowMgr::getInstance()->meshes.at(27 + indexAtKey)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
			windowMgr::getInstance()->gameKeyboardFunctions[indexAtKey] = 999;
			// Set is Function Empty to true
			isFunctionEmptyKeyboard = true;
		}
	}

	keyboardButtonPressed[keyboardButtonNumber] = false;
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
