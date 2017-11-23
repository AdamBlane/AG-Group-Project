

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
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.0f, 1.8f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["actionLbl"]);
	// Set button label
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 1.8f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["buttonLbl"]);
	// Select Fire
	// Set selectfire label
	windowMgr::getInstance()->meshes.at(3)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(-2.0f, 1.45f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["selectfireLbl"]);
	// Set selectfire button label
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, 1.45f, 0.0f));
	// Back Reset
	// Set backreset label
	windowMgr::getInstance()->meshes.at(5)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-2.0f, 1.1f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["backresetLbl"]);
	// Set backreset button label
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(0.0f, 1.1f, 0.0f));
	// Pause
	// Set pause label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(-2.0f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["pauseLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.28f, 0.28f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(0.0f, 0.75f, 0.0f));
	// Arrows
	// Up
	windowMgr::getInstance()->meshes.at(9)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(-2.0f, 0.4f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["upLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(10)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.4f, 0.0f));
	// Left
	windowMgr::getInstance()->meshes.at(11)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(-2.0f, 0.05f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(12)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, 0.05f, 0.0f));
	// Down 
	windowMgr::getInstance()->meshes.at(13)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(-2.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["downLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(14)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(14)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	// Right
	windowMgr::getInstance()->meshes.at(15)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(15)->SetPos(vec3(-2.0f, -0.65f, 0.0f));
	windowMgr::getInstance()->meshes.at(15)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(16)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(16)->SetPos(vec3(0.0f, -0.65f, 0.0f));
	// Jump
	windowMgr::getInstance()->meshes.at(17)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(17)->SetPos(vec3(-2.0f, -1.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(17)->SetTexture(windowMgr::getInstance()->textures["jumpLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(18)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(18)->SetPos(vec3(0.0f, -1.0f, 0.0f));
	// Zoom In
	windowMgr::getInstance()->meshes.at(19)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(19)->SetPos(vec3(-2.0f, -1.35f, 0.0f));
	windowMgr::getInstance()->meshes.at(19)->SetTexture(windowMgr::getInstance()->textures["zoomInLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(20)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(20)->SetPos(vec3(0.0f, -1.35f, 0.0f));
	// Zoom Out
	windowMgr::getInstance()->meshes.at(21)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(21)->SetPos(vec3(-2.0f, -1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(21)->SetTexture(windowMgr::getInstance()->textures["zoomOutLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(22)->SetScale(0.35f, 0.35f);
	windowMgr::getInstance()->meshes.at(22)->SetPos(vec3(0.0f, -1.7f, 0.0f));
	// Main Menu
	windowMgr::getInstance()->meshes.at(23)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(23)->SetPos(vec3(2.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(23)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);

	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// If controller is connected 
	if (1 == present)
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
	// Calculate dt
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	dt = (float)(thisFrame - lastFrame);

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

void highscoreScene::Input(GLFWwindow* win)
{
	// Create a variable to check if the joy stick is present - 1 means true
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	// Dected how many buttons the controller has
	int buttonCount;
	const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	// If controller is connected 
	if (1 == present)
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
						// Loop through all the different functions
						for (int functionNumber = 0; functionNumber < 10; functionNumber++)
						{
							// Find the empty function which will be equal to 99
							if (windowMgr::getInstance()->gameFunctions[functionNumber] == 99)
							{
								// Loop through all the functions once more
								for (int functionNumber = 0; functionNumber < 10; functionNumber++)
								{
									// Check if button just pressed has a function assigned to it
									if (buttonNumber == windowMgr::getInstance()->gameFunctions[functionNumber])
									{
										// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
										windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
										windowMgr::getInstance()->gameFunctions[functionNumber] = 99;
										// Break out of the for loop
										break;
									}
								}

								// Make the original empty function equal to the button
								windowMgr::getInstance()->gameFunctions[functionNumber] = buttonNumber;
								windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->buttonsPS[buttonNumber]);

								// Check if a function is equal to 99
								if (windowMgr::getInstance()->gameFunctions[0] == 99 || windowMgr::getInstance()->gameFunctions[1] == 99 || windowMgr::getInstance()->gameFunctions[2] == 99||
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
								// Break out the for loop
								break;
							}
						}
					}
					else
					{
						// Loop through all the entries in the buttonVlaues map - j functions
						for (int functionNumber = 0; functionNumber < 10; functionNumber++)
						{
							// If function is assigned to a button then
							if (windowMgr::getInstance()->gameFunctions[functionNumber] == buttonNumber)
							{
								// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
								windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
								windowMgr::getInstance()->gameFunctions[functionNumber] = 99;
								// Set is Function Empty to true
								isFunctionEmpty = true;
								// Break out of for loop
								break;
							}
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
						// Loop through all the different functions
						for (int functionNumber = 0; functionNumber < 10; functionNumber++)
						{
							// Find the empty function which will be equal to 99
							if (windowMgr::getInstance()->gameFunctions[functionNumber] == 99)
							{
								// Loop through all the functions once more
								for (int functionNumber = 0; functionNumber < 10; functionNumber++)
								{
									// Check if button just pressed has a function assigned to it
									if (buttonNumber == windowMgr::getInstance()->gameFunctions[functionNumber])
									{
										// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
										windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
										windowMgr::getInstance()->gameFunctions[functionNumber] = 99;
										// Break out of the for loop
										break;
									}
								}

								// Make the original empty function equal to the button
								windowMgr::getInstance()->gameFunctions[functionNumber] = buttonNumber;
								windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->buttonsXB[buttonNumber]);

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
								// Break out the for loop
								break;
							}
						}
					}
					else 
					{
						// Loop through all the entries in the buttonVlaues map - j functions
						for (int functionNumber = 0; functionNumber < 10; functionNumber++)
						{
							// If function is assigned to a button then
							if (windowMgr::getInstance()->gameFunctions[functionNumber] == buttonNumber)
							{
								// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
								windowMgr::getInstance()->meshes.at(4 + (functionNumber * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
								windowMgr::getInstance()->gameFunctions[functionNumber] = 99;
								// Set is Function Empty to true
								isFunctionEmpty = true;
								// Break out of for loop
								break;
							}
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


