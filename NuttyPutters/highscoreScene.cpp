

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
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-1.0f, 1.8f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["actionLbl"]);
	// Set button label
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(1.0f, 1.8f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["buttonLbl"]);
	// Select Fire
	// Set selectfire label
	windowMgr::getInstance()->meshes.at(3)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(-1.0f, 1.45f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["selectfireLbl"]);
	// Set selectfire button label
	windowMgr::getInstance()->meshes.at(4)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(1.0f, 1.45f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["aButtonLbl"]);
	// Back Reset
	// Set backreset label
	windowMgr::getInstance()->meshes.at(5)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-1.0f, 1.1f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["backresetLbl"]);
	// Set backreset button label
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(1.0f, 1.1f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["bButtonLbl"]);
	// Pause
	// Set pause label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(-1.0f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["pauseLbl"]);
	// Set pause button label
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.28f, 0.28f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(1.0f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["menuButtonLbl"]);

	// Setup the default controls for the xbox controller
	// BUTTONS
	// A/Sqaure = 0
	// B/X(PS) = 1
	// X(XB)/Circle = 2
	// Y/Triangle = 3
	// /L1 = 4
	// /R1 = 5
	// /L2 = 6
	// /R2 = 7
	// /Select = 8
	// /Start = 9
	// /Left Stick Push = 10
	// /Right Stick Push = 11
	// /PS Button =12
	// /Pad = 13
	// /DPAD UP = 14
	// /DPAD LEFT = 15 
	// /DPAD DOWN = 16
	// /DPAD RIGHT = 17

	// FUCTIONS
	// Select/fire = 0
	// Back/Reset = 1
	// Pause = 2
	// DPAD UP = 3
	// DPAD LEFT = 4
	// DPAD DOWN = 5
	// DPAD RIGHT = 6

	// FUNCTION/BUTTONS
	windowMgr::getInstance()->buttonValues.insert(std::pair<int, int>(0, 2)); 
	windowMgr::getInstance()->buttonValues.insert(std::pair<int, int>(1, 3)); 
	windowMgr::getInstance()->buttonValues.insert(std::pair<int, int>(2, 0));

	// For all the functions in the game 
	for (int functions = 0; functions < windowMgr::getInstance()->buttonValues.size(); functions++)
	{
		// If function is assigned to 0 then 
		if (windowMgr::getInstance()->buttonValues.find(functions)->second == 0)
		{
			// 4+function*2 is done below because the meshes we want to update go 4, 6, 8, 10 and that formula fits
			// Update texture at mesh position 4+function*2 - to A button
			windowMgr::getInstance()->meshes.at(4+(functions*2))->SetTexture(windowMgr::getInstance()->textures["aButtonLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 1)
		{
			// Update texture at mesh position 4+function*2 - to B button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["bButtonLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 2)
		{
			// Update texture at mesh position 4+function*2 - to X button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["xButtonLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 3)
		{
			// Update texture at mesh position 4+function*2 - to Y button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["yButtonLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 4)
		{
			// Update texture at mesh position 4+function*2 - to Left Bumber button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["lbLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 5)
		{
			// Update texture at mesh position 4+function*2 - to Right Bumber button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["rbLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 6)
		{
			// Update texture at mesh position 4+function*2 - to Left Trigger button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["ltLbl"]);
		}
		else if (windowMgr::getInstance()->buttonValues.find(functions)->second == 7)
		{
			// Update texture at mesh position 4+function*2 - to Right Trigger button
			windowMgr::getInstance()->meshes.at(4 + (functions * 2))->SetTexture(windowMgr::getInstance()->textures["rtLbl"]);
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
	//cout << "Joystick/Gamepad 1 status: " << present << endl;

	// If controller is connected 
	if (1 == present)
	{
		// Dected how many axis the controller has
		int axesCount;
// M - Will axes be used again? Get rid of it if not! 
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		// 6 axis, both anaolgues left/right, up/down =4 then L2 = 5 AND R2 =6 
		//cout << "Number of axis available: " << axesCount << endl;
		//Print a few blank lines to see results movement
		//cout << endl;
		// Print positions of analoges and triggers
		//cout << "Left Stick X Axis: " << axes[0] << endl;
		//cout << "Left Stick Y Axis: " << axes[1] << endl;
		//cout << "Right Stick X Axis: " << axes[2] << endl;
		//cout << "Right Stick Y Axis: " << axes[3] << endl;
		//cout << "Left Trigger/L2: " << axes[4] << endl;
		//cout << "Right Trigger/R2: " << axes[5] << endl;

		// Dected how many buttons the controller has
		int buttonCount;
		const unsigned char *buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

		// Print map - for testing
		for (int functions = 0; functions < windowMgr::getInstance()->buttonValues.size(); functions++)
		{
			cout << "Function: " << functions << " at: " << windowMgr::getInstance()->buttonValues.at(functions) << endl;
		}


		// Remappign controls
		// For loop which checks to see if buttons are pressed
// M - Just to check, is there no way of listening for input rather than checking each button every frame? 
// This would be similar to the input callbacks we were first using for keyboard commands
		for (int i = 0; i < 17; i++)
		{
			// If button i is pressed then set corresponding boolean to true
			if (GLFW_PRESS == buttons[i])
			{
				buttonPressed[i] = true;
			}
		}

// M - My immediate concern for the button code is the number of loops you're doing - 119 iterations every frame (including above loop), with at least one if statement
// ...for each loop. If it runs smoothly I suppose it's all good, but I have a suggestion for the way you're storing the buttons (which would require a lot of changes so up to you)
// I suggest just using an array to store the button values. The reason you're using a map is to explicity show the relationship between functions and buttons, but you could
// ...achieve the same thing with an implicit representation using an array; the index is the function value. Eg our first function 'select/fire' is given the value 0,
// ...so the corresponding button value is the first thing (0 index) in the array. You can use an array since it'll always be a fixed size of 6. The advantages of this are that
// ...arrays take less memory to store than maps and are easier to search. I might have missed a key reason of using the map to actually store the function value, but it should
// ...still be possible with index alone - let me know your thoughts!

// Finally, all of the logic you've written here needs to be ported over to windowMgr so that we can call these exact same functions from gameScene!


		// For all buttons 
		for (int i = 0; i < 17; i++)
		{
			// If i Button bool is true and i button is not being pressed then 
			if (buttonPressed[i] && !GLFW_PRESS == buttons[i])
			{
				// Loop through all the entries in the buttonVlaues map
				for (const auto& keyval : windowMgr::getInstance()->buttonValues) // Look at each key-value pair
				{
					// If i is assigned to a function then ie second value then
					if (keyval.second == i) 
					{
						// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
						windowMgr::getInstance()->meshes.at(4 + (keyval.first * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
						windowMgr::getInstance()->buttonValues.at(keyval.first) = 99;
						// Set is Function Empty to true
						isFunctionEmpty = true;
						// Break out of for loop
						break;
					}
					// If i is not assigned to a function then 
					else
					{
						// If there is an empty function then
						if (isFunctionEmpty)
						{
							// Find the empty function - equal to 99 means no button is assigned to the button
							if (keyval.second == 99)
							{
								// Set the second value to i
								windowMgr::getInstance()->buttonValues.at(keyval.first) = i;
								windowMgr::getInstance()->meshes.at(4 + (keyval.first * 2))->SetTexture(windowMgr::getInstance()->textures["aButtonLbl"]);
								// Reset the is Function Empty to false
								isFunctionEmpty = false;
							}
						}
					}
				}
				// Reset button pressed
				buttonPressed[i] = false;
			}

			// If B Button bool is true and A button is not being pressed then 
			//if (bButtonPressed && !GLFW_PRESS == buttons[1])
			//{
			//	// Loop through all the entries in the buttonVlaues map
			//	for (const auto& keyval : windowMgr::getInstance()->buttonValues) // Look at each key-value pair
			//	{
			//		// If B/X(PS) is assigned to a function then
			//		if (keyval.second == 1) // If the value is 0...
			//		{
			//			// Set picture to question marks and button to rogue value of 99 - 99 will mean the function now no longer has a button assigned
			//			windowMgr::getInstance()->meshes.at(4 + (keyval.first * 2))->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
			//			windowMgr::getInstance()->buttonValues.at(keyval.first) = 99;
			//			// Set is Function Empty to true
			//			isFunctionEmpty = true;
			//			// Break out of for loop
			//			break;
			//		}
			//		// If B/X(PS) is not assigned to a function then 
			//		else
			//		{
			//			// If there is an empty function then
			//			if (isFunctionEmpty)
			//			{
			//				// Find the empty function - equal to 99 means no button is assigned to the button
			//				if (keyval.second == 99)
			//				{
			//					// Set the second value to B/X(PS)
			//					windowMgr::getInstance()->buttonValues.at(keyval.first) = 1;
			//					windowMgr::getInstance()->meshes.at(4 + (keyval.first * 2))->SetTexture(windowMgr::getInstance()->textures["bButtonLbl"]);
			//					// Reset the is Function Empty to false
			//					isFunctionEmpty = false;
			//				}
			//			}
			//		}
			//	}
			//	bButtonPressed = false;
			//}
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

	for (int i = 0; i < 9; i++)
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


