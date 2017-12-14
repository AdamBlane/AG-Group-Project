#include <fstream>
#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }

// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow* win)
{
	// MONDAY DEMO PRINT COMMANDS
	//cout << "\nLOAD GAME SCREEN CONTROLS:" << endl;
	//cout << "Up & Down arrows move through images" << endl;
	//cout << "Left & Right arrows move through pages of images" << endl;
	//cout << "Enter loads selected level" << endl;
	//cout << "B goes back to main menu" << endl;

	// Set initial button press bools to false
	upPressed = downPressed = leftPressed = rightPressed = enterPressed = mouseLpressed = false;
	// Set initial values for navigation variables
	lastImageSelected = currentImageSelected = savesImagesIndex = enterCooldown =  0;
	// Set initial current image page value
	currentPage = 1;
	
	// Set background mesh properties
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["playerSelectBackground"]);
	// Set mesh properties for left and right arrows
	windowMgr::getInstance()->meshes.at(1)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-3.0f, 0.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
	// Right
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(3.0f, 0.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);

	// Set up players label
	windowMgr::getInstance()->meshes.at(3)->SetScale(2.625f, 0.375f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(-1.0f, -1.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["playersLabel"]);

	////// Set up one players label/button
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.375f, 0.375f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.4f, -1.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);

	////// Set up two players label/button
	windowMgr::getInstance()->meshes.at(5)->SetScale(1.5f, 0.375f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(0.8f, -1.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);

	windowMgr::getInstance()->meshes.at(6)->SetScale(0.375f, 0.375f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(1.2f, -1.3f, 0.0));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);

	//// Set up main menu label
	windowMgr::getInstance()->meshes.at(7)->SetScale(2.625f, 0.375f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(1.50f, -1.8f, 0.0));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);

	//// Set up main menu label
	windowMgr::getInstance()->meshes.at(8)->SetScale(2.625f, 0.375f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(-1.5f, -1.8f, 0.0));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
	// Set image viewer properties
	// Create image meshes
	int imCount = 0;
	// Setup meshes
	for (int x = -1; x < 2; ++x)
	{
		for (int y = 1; y > -2; --y)
		{
			float xPos, yPos;
			xPos = (x*w);
			yPos = (y*h) + 0.3f;
			windowMgr::getInstance()->imagePanelMeshes.at(imCount)->SetPos(vec3(xPos, yPos + 0.2f, 0));
			//cout << yPos << endl;
			windowMgr::getInstance()->imagePanelMeshes.at(imCount)->SetScale(w, h);
			imCount++;
		}
	}

	// Calculate total number images, and number of pages required
	totalImages = (float)windowMgr::getInstance()->savesImages.size();
	pageCount = ceil(totalImages / 9);
	// Set image meshes with saved image textures - up to limit of 9 per 'page'
	int limit = (int)totalImages;
	maxImagetoSelect = limit - 1; // Limit is count, maxImage... is index
	if (totalImages > 9)
	{
		limit = 9; // Limit is for the next loop which draws textures
		maxImagetoSelect = 8; // This prevents users from selecting image meshes without save image
	}
		
	// Draw the saved image textures onto image meshes
	for (int i = 0; i < limit; i++)
	{
		windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->savesImages.at(i));
	}
	// give clear texture to any left over
	for (int i = limit; i < 9; ++i)
	{
		windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->textures["transBackground"]);
	}
	// Show first image as selected
	windowMgr::getInstance()->imagePanelMeshes.at(0)->SetScale(selectedW, selectedH);


	// Read all saved seeds
	ifstream saves("saves.csv");

	// Read all saved games as strings
	while (!saves.eof())
	{
		string line;
		getline(saves, line);
		if(line != "") // if not whitespace cell read
			seeds.push_back(line); // store in seeds list
	}

}


void loadGameScene::Track_Mouse(GLFWwindow* win) 
{
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	// If mouse pos falls within button area...
	// Using hardcoded values since we can't match up coord systems (meshes origin is window centre measured in floats, cursor pos origin it top left measured in pixels)
	// Left column
	prevselection = Menuselection;
	if (OtherSelection != 8 || OtherSelection != 15)
	{
		otherprevselection = OtherSelection;
	}
	if(windowMgr::getInstance()->mouse_x >= 214 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 1385 * windowMgr::getInstance()->windowScale 
		&& windowMgr::getInstance()->mouse_y >= 14 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y <= 666 * windowMgr::getInstance()->windowScale)
	{
		if (windowMgr::getInstance()->mouse_x >= 214 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 604 * windowMgr::getInstance()->windowScale)
		{
			if (windowMgr::getInstance()->mouse_y <= 231 * windowMgr::getInstance()->windowScale)
			{
				selection = 0;
			}
			// Middle 
			else if (windowMgr::getInstance()->mouse_y <= 450 * windowMgr::getInstance()->windowScale)
			{
				selection = 1;
			}
			// Bottom
			else if (windowMgr::getInstance()->mouse_y <= 666 * windowMgr::getInstance()->windowScale)
			{
				selection = 2;
			}
		}
		else if (windowMgr::getInstance()->mouse_x >= 604 * windowMgr::getInstance()->windowScale && (windowMgr::getInstance()->mouse_x <= 995 * windowMgr::getInstance()->windowScale))
		{
			// Top image mesh
			if (windowMgr::getInstance()->mouse_y <= 231 * windowMgr::getInstance()->windowScale )
			{
				selection = 3;
			}
			// Middle 
			else if (windowMgr::getInstance()->mouse_y <= 450 * windowMgr::getInstance()->windowScale)
			{
				selection = 4;
			}
			// Bottom
			else if (windowMgr::getInstance()->mouse_y <= 666 * windowMgr::getInstance()->windowScale)
			{
				selection = 5;
			}
		} // end for loop middle column
		  // Right column
		else if ((windowMgr::getInstance()->mouse_x >= 996 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1385 * windowMgr::getInstance()->windowScale))
		{
			// Top image mesh
			if (windowMgr::getInstance()->mouse_y >= 14 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y <= 231 * windowMgr::getInstance()->windowScale)
			{
				selection = 6;
			}
			// Middle 
			else if (windowMgr::getInstance()->mouse_y <= 450 * windowMgr::getInstance()->windowScale)
			{
				selection = 7;
			}
			// Bottom
			else if (windowMgr::getInstance()->mouse_y <= 666 * windowMgr::getInstance()->windowScale)
			{
				selection = 8;
			}
		} // end for loop right column
	}
	else if ((windowMgr::getInstance()->mouse_y >= 303 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y <= 375 * windowMgr::getInstance()->windowScale))
	{
		// Left Arrow
		if ((windowMgr::getInstance()->mouse_x >= 98 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 192 * windowMgr::getInstance()->windowScale))
		{
			selection = 9;
		}
		// Right Arrow
		else if (windowMgr::getInstance()->mouse_x >= 1407 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 1502 * windowMgr::getInstance()->windowScale)
		{
			selection = 10;
		}
	}
	else if ((windowMgr::getInstance()->mouse_y >= 704 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y <= 757 * windowMgr::getInstance()->windowScale))
	{
		// Top image mesh
		if ((windowMgr::getInstance()->mouse_x >= 853 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 919 * windowMgr::getInstance()->windowScale))
		{
			selection = 11;
		}
		// Middle 
		else if (windowMgr::getInstance()->mouse_x >= 1027 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 1099 * windowMgr::getInstance()->windowScale)
		{
			selection = 12;
		}
	}
	else if ((windowMgr::getInstance()->mouse_y >= 811 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_y <= 864 * windowMgr::getInstance()->windowScale))
	{
		// Top image mesh
		if ((windowMgr::getInstance()->mouse_x >=222 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 721 * windowMgr::getInstance()->windowScale))
		{
			selection = 13;
		}
		// Middle 
		else if (windowMgr::getInstance()->mouse_x >= 867 * windowMgr::getInstance()->windowScale && windowMgr::getInstance()->mouse_x <= 1380 * windowMgr::getInstance()->windowScale)
		{
			selection = 14;
		}
	}
	if (selection <= 8)
	{
		Menuselection = selection;
	}
	else 
	{
		Menuselection = 9;
	}
	if (selection >= 9)
	{
		OtherSelection = selection;
	}
	else
	{
		OtherSelection = 8;
	}
}

void loadGameScene::Click_or_Enter(GLFWwindow* win)
{
	if (selection <= 8)
	{
		lastImageSelected = currentImageSelected;
		currentImageSelected = selection;
		savesImagesIndex = (currentPage - 1) * 9 + currentImageSelected;
		// Resize this and last choice
		windowMgr::getInstance()->imagePanelMeshes.at(lastImageSelected)->SetScale(w, h);
		windowMgr::getInstance()->imagePanelMeshes.at(currentImageSelected)->SetScale(selectedW, selectedH);
		//cout << "Current: " << currentImageSelected << " Last: " << lastImageSelected << endl;
	}
	else 
	{
		switch (selection)
		{
			case 10:
				if (currentPage < (int)pageCount)
				{
					// Show last page
					NextPage();
				}
				break;
			case 9:
				if (currentPage > 1)
				{
					// Show last page
					LastPage();
					// Resize this and last choice
				}
				break;
			case 11:
				// If button selected is button 4 - main menu - then wrap around to button 1
				if (playerCount == 1)
				{
					playerCount = 2;
				}
				// else keep going down
				else
				{
					playerCount--;
				}
				break;
			case 12:
				// If button selected is button 4 - main menu - then wrap around to button 1
				if (playerCount == 2)
				{
					playerCount = 1;
				}
				// else keep going down
				else
				{
					playerCount++;
				}
				break;
			case 13:	
				// Access singleton instance to update it's sceneManager's state
				windowMgr::getInstance()->sceneManager.changeScene(1);
				break;
			case 14:
				enterPressed = false; // Suspect this is unnecessary
									  // Current seed is index of seeds list, send as optional param
									  // 6 is game scene
									  // first number is course length (number of digits in seed)
				if (seeds.size() > savesImagesIndex)
				{
					int courseLength = seeds.at(savesImagesIndex).length();

					// playerCount is number of players
					// 1 is number of levels this game
					windowMgr::getInstance()->sceneManager.changeScene(6, courseLength, playerCount, 1, seeds.at(savesImagesIndex)); // 12 is mandatory course lenght (to be disregarded dw)	

				}
				break;
		}
	}

	// Play sound on enter button
	windowMgr::getInstance()->PlayThisSound("confirmSound");
}

// Main loop
void loadGameScene::Loop(GLFWwindow* win)
{
	// Scene background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);
	//upadate
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
// Redraws next/last page of images onto image viewer meshes
void loadGameScene::NextPage()
{
	// Set last image mesh selected
	lastImageSelected = currentImageSelected;
	// Reset currentImageSelected to start
	currentImageSelected = 0;
	// We're on next page
	currentPage++;
	// Set saves image index
	savesImagesIndex = (currentPage - 1) * 9;


	// Find limit for this page - difference between savesImagesIndex and total images
	int limit = totalImages - savesImagesIndex;
	maxImagetoSelect = limit - 1;
	// Imposed limit of 9 image meshes
	if (limit > 9)
	{
		limit = 9;
		maxImagetoSelect = 8;
	}
		

	// Draw the next set of saves image textures
	for (int i = 0; i < limit; ++i)
	{
		// 1 + since background is taken, at 0
		windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->savesImages.at(savesImagesIndex + i));
	}

	// Clear the rest from previous page
	for (int i = limit; i < 9; ++i)
	{
		windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->textures["transBackground"]);
	}
}

// Load previous page of images
void loadGameScene::LastPage()
{
	// Set last image mesh selected
	lastImageSelected = currentImageSelected;
	// Reset current image mesh value to end
	currentImageSelected = 8;
	// Were on the previous page
	currentPage--;
	// Set the images index
	savesImagesIndex = ((currentPage - 1) * 9) + 8;


	// We know there is a full page of images to show, from curIndex - 8 to curIndex 
	int startIndex = savesImagesIndex - 8;
	int endIndex = savesImagesIndex + 1;
	for (int i = 0; i < 9; i++)
	{
		windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->savesImages.at(startIndex));
		startIndex++;
	}
	//for (int i = savesImagesIndex - 8; i < savesImagesIndex + 1; ++i)
	//{
	//	windowMgr::getInstance()->imagePanelMeshes.at(i)->SetTexture(windowMgr::getInstance()->savesImages.at(i));
	//}
}

// Resizes the current and last selected image mesh
void loadGameScene::ResizeCurLastSelected()
{
	if (Menuselection != currentImageSelected)
	{
		if (Menuselection != 9)
		{
			// Resize this and last choice
			windowMgr::getInstance()->imagePanelMeshes.at(Menuselection)->SetScale(hoverW, hoverH);
		}
	}
	//windowMgr::getInstance()->imagePanelMeshes.at(lastImageSelected)->SetScale(w, h);
	// Resize this and last choice]
	if (prevselection != currentImageSelected)
	{
		if (prevselection == 9) 
		{

		}
		else if (prevselection != Menuselection)
		{
			windowMgr::getInstance()->imagePanelMeshes.at(prevselection)->SetScale(w, h);
		}
	}
	switch (playerCount) 
	{
		case 1:
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["twoBtnUnselected"]);
			break;
	}
	switch (OtherSelection) 
	{
		case 8:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["playersLabel"]);
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
			break;
		case 9:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["highleftLbl"]);
			break;
		case 10:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["highrightLbl"]);
			break;
		 case 15:
			 windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["playersSelected"]);
			 break;
		 case 14:
			 windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);
			 break;
		 case 13:
			 windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnSelected"]);
			 break;

	}
	switch (otherprevselection)
	{
		case 9:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["leftLbl"]);
			break;
		case 10:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["rightLbl"]);
			break;
		case 15:
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["playersLabel"]);
			break;
		case 13:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			break;
		case 14:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
			break;

	}

}
void loadGameScene::Left()
{
	prevselection = Menuselection;
	if (OtherSelection != 8)
	{
		otherprevselection = OtherSelection;
	}
	if (selection == 0 || selection == 1 || selection == 2)
	{
		selection = 9;
	}
	else if (selection == 9)
	{
		selection = 10;
	}
	else if (selection == 10)
	{
		selection = 7;
	}
	else if (selection == 14)
	{
		selection = 13;
	}
	else if (selection == 13)
	{
		selection = 14;
	}
	else if (selection == 15)
	{
		// Play sound on enter button
		windowMgr::getInstance()->PlayThisSound("confirmSound");

		// If button selected is button 4 - main menu - then wrap around to button 1
		if (playerCount == 1)
		{
			playerCount = 2;
		}
		// else keep going down
		else
		{
			playerCount--;
		}
	}
	else
	{
		selection -= 3;
	}
	if (selection <= 8)
	{
		Menuselection = selection;
	}
	else
	{
		Menuselection = 9;
	}
	if (selection >= 9)
	{
		OtherSelection = selection;
	}
	else
	{
		OtherSelection = 8;
	}
}
void loadGameScene::Right()
{
	prevselection = Menuselection;
	if (OtherSelection != 8)
	{
		otherprevselection = OtherSelection;
	}
	if (selection == 8 || selection == 7 || selection == 6)
	{
		selection = 10;
	}
	else if (selection == 10 )
	{
		selection = 9;
	}
	else if (selection == 9)
	{
		selection = 1;
	}
	else if (selection == 15)
	{
		// Play sound on enter button
		windowMgr::getInstance()->PlayThisSound("confirmSound");

		// If button selected is button 4 - main menu - then wrap around to button 1
		if (playerCount == 2)
		{
			playerCount = 1;
		}
		// else keep going down
		else
		{
			playerCount++;
		}
	}
	else if (selection == 14)
	{
		selection = 13;
	}
	else if (selection == 13)
	{
		selection = 14;
	}
	else
	{
		selection += 3;
	}
	if (selection <= 8)
	{
		Menuselection = selection;
	}
	else
	{
		Menuselection = 9;
	}
	if (selection >= 9)
	{
		OtherSelection = selection;
	}
	else
	{
		OtherSelection = 8;
	}
}
void loadGameScene::Down() 
{
	prevselection = Menuselection;
	if (OtherSelection != 8)
	{
		otherprevselection = OtherSelection;
	}
	if (selection == 8 || selection == 5 || selection == 2)
	{
		selection = 15;
	}
	else if (selection == 13 || selection == 14)
	{
		selection = 0;
	}
	else if (selection == 15)
	{
		selection = 13;
	}
	else if (selection == 9)
	{
		selection = 2;
	}
	else if (selection == 10)
	{
		selection = 8;
	}
	else
	{
		selection++;
	}
	if (selection <= 8)
	{
		Menuselection = selection;
	}
	else
	{
		Menuselection = 9;
	}
	if (selection >= 9)
	{
		OtherSelection = selection;
	}
	else
	{
		OtherSelection = 8;
	}
}
void loadGameScene::Up()
{
	prevselection = Menuselection;
	if (OtherSelection != 8)
	{
		otherprevselection = OtherSelection;
	}
	if (selection == 0 || selection == 3 || selection == 6)
	{
		selection = 13;
	}
	else if (selection == 13 || selection == 14)
	{
		selection = 15;
	}
	else if (selection == 15)
	{
		selection = 2;
	}
	else if (selection == 9)
	{
		selection = 0;
	}
	else if (selection == 10)
	{
		selection = 6;
	}
	else
	{
		selection--;
	}
	if (selection <= 8)
	{
		Menuselection = selection;
	}
	else
	{
		Menuselection = 9;
	}
	if (selection >= 9)
	{
		OtherSelection = selection;
	}
	else
	{
		OtherSelection = 8;
	}
}
// Act on input
void loadGameScene::Input(GLFWwindow* win)
{
	// Get the state of controller one
	controllerOne = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &controllerOneButtonCount);
	// If controller 1 is connected, run controller input loop for p1 only
	if (controllerOne != NULL)
	{
		// Get axes details
		controllerOneAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &controllerOneAxisCount);

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

		// If right key is pressed set keyLeft to true
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][4]])
		{
			windowMgr::getInstance()->leftCotn = true;
		}
		// If leftKey is true and left key is not pressed then
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][4]] && windowMgr::getInstance()->leftCotn)
		{
			Left();
			// Reset keyLeft to false
			windowMgr::getInstance()->leftCotn = false;
		}

		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][6]])
		{
			windowMgr::getInstance()->rightCotn = true;
		}
		// If leftKey is true and left key is not pressed then
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][6]] && windowMgr::getInstance()->rightCotn)
		{
			Right();
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
				Up();
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
				Down();
				windowMgr::getInstance()->downCotn = false;
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
				Click_or_Enter(win);
				windowMgr::getInstance()->enterCotn = false;
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

	// B goes back to main menu screen
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][1]))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}
	// Mouse input
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		mouseLpressed = true;
	}
	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (mouseLpressed)
		{
			Click_or_Enter(win);
			mouseLpressed = false;
		}

	}
	// IMAGE MESH NAVIGATION
	// Go back/up an image mesh
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][3]))
	{
		upPressed = true;
	}
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][3]))
	{
		// Only if left was just released...
		if (upPressed)
		{	
			Up();
			upPressed = false;
		}
	}

	// Go along/down an image mesh
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][5]))
	{
		downPressed = true;
	}
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][5]))
	{
		if (downPressed)
		{
			Down();
			downPressed = false;
		}

	}
	// View next page
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][6]))
	{
		rightPressed = true;
	}
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][6]))
	{
		if (rightPressed)
		{
			Right();
			rightPressed = false;
		}
		
	}
	// View last page
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][4]))
	{
		leftPressed = true;
	}
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][4]))
	{
		if (leftPressed)
		{
			Left();
			leftPressed = false;
		}		
	}	
	// Select this level to load
	if (glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][0]) && enterCooldown > enterCooldownMax)
	{
		enterPressed = true;
	}
	if (!glfwGetKey(win, windowMgr::getInstance()->playerKeyboardControls[0][0]))
	{
		if (enterPressed)
		{
			enterPressed = false; // Suspect this is unnecessary
			// Current seed is index of seeds list, send as optional param
			// 6 is game scene
			// 12 is course length
			// playerCount is number of players
			// 1 is number of levels this game
			Click_or_Enter(win); // 12 is mandatory course lenght (to be disregarded dw)		
		}
	}
	
}

// Update 
void loadGameScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
	
	// To ensure enter doesn't trigger just after loading this scene
	if (enterCooldown < enterCooldownMax + 5) // 5 is epsilon 
	{
		enterCooldown++;
	}
	
	ResizeCurLastSelected();
}

// Draw stuff
void loadGameScene::Render(GLFWwindow* win)
{
	// Calculate hud view*projection
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();
	// Set depth range, for HUD style rendering effect
	glDepthRange(0, 0.01);
	// Render all meshes & their textures
	// iter limit is slightly magic - number of meshes this scene requires
	for (int i = 0; i <= 8; i++)
	{
		windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(i)->Draw();
	}
	for (auto &m : windowMgr::getInstance()->imagePanelMeshes)
	{
		m->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		m->Draw();
	}

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
