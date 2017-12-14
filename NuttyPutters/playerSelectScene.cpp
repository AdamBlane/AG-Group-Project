#include "playerSelectScene.h"
#include "windowMgr.h"

// Constructor
playerSelectScene::playerSelectScene() { }
// Deconstructor
playerSelectScene::~playerSelectScene() { }

void playerSelectScene::Track_Mouse(GLFWwindow *window)
{
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if (windowMgr::getInstance()->mouse_y <= 114 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y >= 45 * windowMgr::getInstance()->windowScale)
	{
		selection = 1;
	}
	else if (windowMgr::getInstance()->mouse_y <= 267 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y >= 196 * windowMgr::getInstance()->windowScale)
	{
		selection = 2;
	}
	else if (windowMgr::getInstance()->mouse_y <= 419 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y >= 347 * windowMgr::getInstance()->windowScale)
	{
		selection = 3;
	}
	if ((windowMgr::getInstance()->mouse_x >= 922 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1018 * windowMgr::getInstance()->windowScale))
	{
		leftbutton = true;
	}
	else if ((windowMgr::getInstance()->mouse_x >= 1320 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1415 * windowMgr::getInstance()->windowScale))
	{
		rightbutton = true;
	}
	else 
	{
		leftbutton = false;
		rightbutton = false;
	}
	if ((windowMgr::getInstance()->mouse_x >= 134 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 814 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 367 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 560 * windowMgr::getInstance()->windowScale))
	{
		selection = 4;
	}
	else if ((windowMgr::getInstance()->mouse_x >= 148 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 814 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 650 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 721 * windowMgr::getInstance()->windowScale))
	{
		selection = 5;
	}
}
// Setup meshes, textures, member vars
void playerSelectScene::Init(GLFWwindow * win)
{
	// MONDAY DEMO PRINT COMMANDS
	//cout << "\nPLAYER SELECT SCREEN CONTROLS:" << endl;
	//cout << "Up/Down arrows moves to last/next row of buttons" << endl;
	//cout << "Left/Right arrows changes that rows options (player count/difficulty)" << endl;
	//cout << "Easy/Med/Hard chooses to play 2/4/6 levels" << endl;
	//cout << "Enter selects highlighted button" << endl;

	// Reset button navigation to first item
	currentMenuItem = 1;
	// Set the HUDs and labels - all have unique positions and scales so all lines below are required
	// Set the background
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["playerSelectBackground"]);

	// Set up players label
	windowMgr::getInstance()->meshes.at(1)->SetScale(3.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-1.0f, 1.7, 0.0));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playersSelected"]);

	////// Set up one players label/button
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.8, 1.7, 0.0));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);

	////// Set up two players label/button
	windowMgr::getInstance()->meshes.at(3)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(1.7, 1.7, 0.0));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);

	windowMgr::getInstance()->meshes.at(4)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(2.6, 1.7, 0.0));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);

	//// Set up difficulty label
	windowMgr::getInstance()->meshes.at(5)->SetScale(3.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-1.30f, 1.0, 0.0));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["difficultyLabel"]);

	////// Set up med label
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(0.8f, 1.0f, 0.0));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);

	////// Set up hard label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.6f, 0.4f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(1.7, 1.0f, 0.0));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["easyBtnUnselected"]);

	////// Set up easy label
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(2.6f, 1.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);

	//// Set up number of levels label
	windowMgr::getInstance()->meshes.at(9)->SetScale(3.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(-1.45f, 0.3, 0.0));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["numberOfLevels"]);

	////// Set left arrow label
	windowMgr::getInstance()->meshes.at(10)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.8f, 0.3, 0.0));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);

	////// Set up number of levels label
	windowMgr::getInstance()->meshes.at(11)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(1.7, 0.3, 0.0));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);

	////// Set right arrow label
	windowMgr::getInstance()->meshes.at(12)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(2.6f, 0.3, 0.0));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);

	//// Set up start label
	windowMgr::getInstance()->meshes.at(13)->SetScale(3.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(-1.5f, -0.4, 0.0));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["startgameUnselected"]);

	//// Set up main menu label
	windowMgr::getInstance()->meshes.at(14)->SetScale(3.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(14)->SetPos(vec3(-1.45f, -1.1, 0.0));
	windowMgr::getInstance()->meshes.at(14)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);

	// Reset all the variables on init 
	playerSelect = 1;
	difficultySelect = 1;
	numberOfHoles = 1;
}

// Draw stuff for this scene
void playerSelectScene::Loop(GLFWwindow * win)
{
	// Scene background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);

	// Update
	Update(win);

	//code to disable mouse
	windowMgr::getInstance()->previous_mouse_x = windowMgr::getInstance()->mouse_x;
	windowMgr::getInstance()->previous_mouse_y = windowMgr::getInstance()->mouse_y;
	glfwGetCursorPos(win, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//tracks mouse
	if (windowMgr::getInstance()->previous_mouse_x != windowMgr::getInstance()->mouse_x || windowMgr::getInstance()->previous_mouse_y != windowMgr::getInstance()->mouse_y)
	{
		Track_Mouse(win);
	}
	// Render
	Render(win);
}

void playerSelectScene::Click_Right(GLFWwindow *win)
{
	// Play sound on enter button
	windowMgr::getInstance()->PlayThisSound("confirmSound");

	switch (currentMenuItem)
	{
		// Case 1 is player select
	case 1:
		// If button selected is button 4 - main menu - then wrap around to button 1
		if (playerSelect == 2)
		{
			playerSelect = 1;
		}
		// else keep going down
		else
		{
			playerSelect++;
		}
		break;
		// Case 2 is difficulty select 
	case 2:
		// If button selected is button 3 - main menu - then wrap around to button 1
		if (difficultySelect == 3)
		{
			difficultySelect = 1;
		}
		// else keep going down
		else
		{
			difficultySelect++;
		}
		break;
	case 3:// If button selected is button 4 - main menu - then wrap around to button 1
		if (numberOfHoles == 9)
		{
			numberOfHoles = 1;
		}
		// else keep going down
		else
		{
			numberOfHoles++;
		}
		break;
	}
	ChangeTexutes(win);
}

void playerSelectScene::Click_Left(GLFWwindow *win)
{
	// Play sound on enter button
	windowMgr::getInstance()->PlayThisSound("confirmSound");

	switch (currentMenuItem)
	{
		// Case 1 is player select
	case 1:
		// If button selected is button 4 - main menu - then wrap around to button 1
		if (playerSelect == 1)
		{
			playerSelect = 2;
		}
		// else keep going down
		else
		{
			playerSelect--;
		}
		break;
		// Case 2 is difficulty select 
	case 2:
		// If button selected is button 4 - main menu - then wrap around to button 1
		if (difficultySelect == 1)
		{
			difficultySelect = 3;
		}
		// else keep going down
		else
		{
			difficultySelect--;
		}
		break;
	case 3:// If button selected is button 4 - main menu - then wrap around to button 1
		if (numberOfHoles == 1)
		{
			numberOfHoles = 9;
		}
		// else keep going down
		else
		{
			numberOfHoles--;
		}
		break;
	}
	ChangeTexutes(win);
}

void playerSelectScene::ChangeTexutes(GLFWwindow *win)
{
	switch (playerSelect)
	{
		//Update textures based on what number is selected
	case 1:
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["twoBtnUnselected"]);
		break;
	}
	switch (numberOfHoles)
	{
		// Update the necessary textures based on the users input
	case 1:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[1]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[2]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[3]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[4]);
		break;
	case 5:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[5]);
		break;
	case 6:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[6]);
		break;
	case 7:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[7]);
		break;
	case 8:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[8]);
		break;
	case 9:
		windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->numberTextures[9]);
		break;
	}
	// Switch statements to select different difficulty - Easy, Medium, Hard
	switch (difficultySelect)
	{
		// Update the necessary textures based on the users input
	case 1:
		windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["easyBtnUnselected"]);
		selectedDifficulty = 8; // Selecteddifficulty is used in the game scene
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["medBtnUnselected"]);
		selectedDifficulty = 12;
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["hardBtnUnselected"]);
		selectedDifficulty = 16;
		break;
	}
	switch (previousMenuItem)
	{
	case 1:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playersLabel"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["difficultyLabel"]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["numberOfLevels"]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["startgameUnselected"]);
		break;
	case 5:
		windowMgr::getInstance()->meshes.at(14)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
		break;
	}
	switch (currentMenuItem)
	{
		//cases for the buttons to switch to each screen
	case 1:
		windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playersSelected"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["difficultySelected"]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["numberOfLevelsSelected"]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["startgameSelected"]);
		break;
	case 5:
		windowMgr::getInstance()->meshes.at(14)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnSelected"]);
		break;
	}
}
/// Act on user input 
void playerSelectScene::Input(GLFWwindow* win)
{
	// Get the state of controller one
	controllerOne = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &controllerOneButtonCount);
	// If controller 1 is connected, run controller input loop for p1 only
	if (controllerOne != NULL)
	{
		// Get axes details
		controllerOneAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &controllerOneAxisCount);
		// If right key is pressed set keyLeft to true
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][4]])
		{
			windowMgr::getInstance()->leftCotn = true;
		}
		// If leftKey is true and left key is not pressed then
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][4]] && windowMgr::getInstance()->leftCotn)
		{
			Click_Left(win);
			// Reset keyLeft to false
			windowMgr::getInstance()->leftCotn = false;
		}

		// If the back button is pressed then go back to the previous screen 
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][1]])
		{
			backButtonPressedController = true;
		}
		// If back button is realised and boolean is true then 
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][1]] && backButtonPressedController)
		{
			// Reset the boolean to false
			backButtonPressedController = false;
			// Return to the main menu screen
			windowMgr::getInstance()->sceneManager.changeScene(1);
		}
		
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][6]])
		{
			windowMgr::getInstance()->rightCotn = true;
		}
		// If leftKey is true and left key is not pressed then
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][6]] && windowMgr::getInstance()->rightCotn)
		{
			Click_Right(win);
			// Reset keyLeft to false
			windowMgr::getInstance()->rightCotn = false;
		}
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][3]])
		{
			windowMgr::getInstance()->upCotn = true;
		}

		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][3]])
		{
			if (windowMgr::getInstance()->upCotn)
			{
				previousMenuItem = currentMenuItem;
				if (currentMenuItem == 1)
				{
					currentMenuItem = 5;
				}
				else if (currentMenuItem == 0)
				{
					currentMenuItem = 5;
				}
				else
				{
					currentMenuItem--;
				}
				ChangeTexutes(win);
				windowMgr::getInstance()->upCotn = false;
			}
		}
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][5]])
		{
			windowMgr::getInstance()->downCotn = true;
		}

		if ((GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][5]]))
		{
			if (windowMgr::getInstance()->downCotn)
			{
				previousMenuItem = currentMenuItem;
				if (currentMenuItem == 5)
				{
					currentMenuItem = 1;
				}
				else
				{
					currentMenuItem++;
				}

				windowMgr::getInstance()->downCotn = false;
				ChangeTexutes(win);
			}
		}

		// When Fire is realesed
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]])
		{
			windowMgr::getInstance()->enterCotn = true;
		}
		if ((GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]]))
		{
			if (windowMgr::getInstance()->enterCotn)
			{
				// Play sound on enter button
				windowMgr::getInstance()->PlayThisSound("confirmSound");

				// If button select is 3 then start the game
				if (currentMenuItem == 4)
				{
					windowMgr::getInstance()->sceneManager.changeScene(6, selectedDifficulty, playerSelect, numberOfHoles);
				}
				// If button select is 4 then return to main menu
				else if (currentMenuItem == 5)
				{
					windowMgr::getInstance()->sceneManager.changeScene(1);
				}
				windowMgr::getInstance()->enterCotn = false;
				ChangeTexutes(win);
			}
		}
	}

	// If the back button is pressed then go back to the previous screen 
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][1]))
	{
		backButtonPressedKeyboard = true;
	}
	// If back button is realised and boolean is true then 
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][1]) && backButtonPressedKeyboard)
	{
		// Reset the boolean to false
		backButtonPressedKeyboard = false;
		// Return to the main menu screen
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

	// If right key is pressed set keyLeft to true
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][4]))
	{
		keyLeft = true;
	}
	// If leftKey is true and left key is not pressed then
	if (keyLeft && !glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][4]))
	{
		Click_Left(win);
		// Reset keyLeft to false
		keyLeft = false;
	}

	// If right key is pressed set keyRight to true
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][6]))
	{
		keyRight = true;
	}
	// If keyRight is true and right is not pressed then
	if (keyRight && !glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][6]))
	{
		Click_Right(win);
		// Reset keyRight
		keyRight = false;
	}

	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][0]))
	{
		keyEnter = true;
	}
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) && total_time >= 5.0f)
	{
		windowMgr::getInstance()->mouseLpressed = true;
	}
	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (windowMgr::getInstance()->mouseLpressed && leftbutton == true && selection != 0)
		{
			previousMenuItem = currentMenuItem;
			currentMenuItem = selection;
			Click_Left(win);
			windowMgr::getInstance()->mouseLpressed = false;
		}
		else if(windowMgr::getInstance()->mouseLpressed && rightbutton == true && selection != 0)
		{
			previousMenuItem = currentMenuItem;
			currentMenuItem = selection;
			Click_Right(win);
			windowMgr::getInstance()->mouseLpressed = false;
		}
		else if (windowMgr::getInstance()->mouseLpressed && selection != 0)
		{
			// Play sound on enter button
			windowMgr::getInstance()->PlayThisSound("confirmSound");
			previousMenuItem = currentMenuItem;
			currentMenuItem = selection;
			ChangeTexutes(win);
			// If button select is 3 then start the game
			if (currentMenuItem == 4)
			{
				windowMgr::getInstance()->sceneManager.changeScene(6, selectedDifficulty, playerSelect, numberOfHoles);
			}
			// If button select is 4 then return to main menu
			else if (currentMenuItem == 5)
			{
				windowMgr::getInstance()->sceneManager.changeScene(1);
			}
			windowMgr::getInstance()->mouseLpressed = false;
		}
	}
	// If key enter equals true and enter is not pressed then
	if (keyEnter && !glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][0]))
	{
		// If button select is 3 then start the game
		if (currentMenuItem == 4)
		{
			windowMgr::getInstance()->sceneManager.changeScene(6, selectedDifficulty, playerSelect, numberOfHoles);
		}
		// If button select is 4 then return to main menu
		else if (currentMenuItem == 5)
		{
			windowMgr::getInstance()->sceneManager.changeScene(1);
		}
		// Reset keyEnter
		keyEnter = false;
	}

	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][3]))
	{
		windowMgr::getInstance()->upPressed = true;
	}

	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][3]))
	{
		if (windowMgr::getInstance()->upPressed)
		{
			previousMenuItem = currentMenuItem;
			if (currentMenuItem == 1)
			{
				currentMenuItem = 5;
			}
			else if (currentMenuItem == 0)
			{
				currentMenuItem = 5;
			}
			else
			{
				currentMenuItem--;
			}
			ChangeTexutes(win);
			windowMgr::getInstance()->upPressed = false;
		}
	}
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][5]))
	{
		windowMgr::getInstance()->downPressed = true;
	}

	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][5]))
	{
		previousMenuItem = currentMenuItem;
		if (windowMgr::getInstance()->downPressed)
		{
			if (currentMenuItem == 5)
			{
				currentMenuItem = 1;
			}
			else
			{
				currentMenuItem++;
			}

			windowMgr::getInstance()->downPressed = false;
			ChangeTexutes(win);
		}
	}

	// Increase time delay tracker (prevents enter/Lclick reoccuring from last scene)
	if (total_time <= 5.0f)
	{
		total_time += 1.0f;
	}
}
// Update cameras
void playerSelectScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
}

// Draw scene
void playerSelectScene::Render(GLFWwindow* win)
{
	// Calculate hud view*projection
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// For loop which goes through all 10 HUD elements and binds, updates anbd draws the meshes.
	for (int i = 0; i <= 14; i++)
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}