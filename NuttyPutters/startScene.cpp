// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton




// Setup start scene meshes and textures, set navigation member vars
void startScene::Init(GLFWwindow* win)
{
	// Reset navigation member variables
	upPressed = downPressed = selectPressed = false;
	// Reset select delay counter
	selectCooldown = 0;

	// Background image will never change so setup here
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["startBackground"]);

	// Perform setup of initial button configs - (un)selected textures
	// Pick next item in meshes list (increment the number by 1 each time)
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(0.0f, -1.5f, 0.0f));
	
}

// Main loop for this scene
void startScene::Loop(GLFWwindow* win)
{
	// Clear buffers every frame
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(win);

	// Update
	Update(win);

	// Render
	Render(win);
}

// Act on input
void startScene::Input(GLFWwindow * win)
{
	// TODO - refactor to avoid using brute force
	switch (button_manager)
	{
		//cases for the buttons to switch to each screen
		case 1:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 2:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnSelected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 3:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnSelected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 4:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnSelected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 5:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnSelected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;

		case 6:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnSelected"]);	
			break;

	}

	// On select press
	if (glfwGetKey(win, GLFW_KEY_ENTER) && selectCooldown > selectCooldownMax)
	{
		// Flip flag
		selectPressed = true;
	} 
	// On select release
	if (!glfwGetKey(win, GLFW_KEY_ENTER))
	{
		// If recently pressed (this is a release action)
		if (selectPressed)
		{
			// If exit button selected
			if (button_manager == 6)
			{
				// Change to exit scene
				windowMgr::getInstance()->sceneManager.changeScene(0);
			}
			// If internet button selected
			else if (button_manager == 5)
			{
				// This opens a browser window at the given url
				ShellExecute(NULL, "open", "http://www.calumtempleton.com", NULL, NULL, SW_SHOWNORMAL);
			}
			// If another button selected
			else
			{
				// Go to that scene
				windowMgr::getInstance()->sceneManager.changeScene(button_manager + 1);
			}

			// Flip flag
			selectPressed = false;
		} // end if select pressed
	} // end on select release

	// On up press
	if (glfwGetKey(win, GLFW_KEY_UP))
	{
		// Flip flag
		upPressed = true;
	}
	// On up release
	if (!glfwGetKey(win, GLFW_KEY_UP))
	{
		// If recently pressed
		if (upPressed)
		{
			// If at top button
			if (button_manager == 1)
			{
				// Go to bottom button
				button_manager = 6;
			}
			else
			{
				// Otherwise decrease current button id
				button_manager--;
			}
			// Flip flag
			upPressed = false;
		}
	}
	
	// On down press
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		downPressed = true;
	}
	// On down release
	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		// If recently pressed
		if (downPressed)
		{
			// If on last button
			if (button_manager == 6)
			{
				// Move to first
				button_manager = 1;
			}
			else
			{
				// Otherwise increase current selected button id
				button_manager++;
			}
			// Flip flag
			downPressed = false;
		}
	}

}

// Update camera, select cooldown 
void startScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);

	// To ensure enter doesn't trigger just after loading this scene
	if (selectCooldown < selectCooldownMax + 5) // 5 is epsilon
	{
		selectCooldown++;
	}
}

// Draw stuff
void startScene::Render(GLFWwindow* win)
{
	// Ensure correct viewport size (in case coming from 2P game)
	glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// Bind, update and draw HUD elements
	for (int a = 0; a < 7; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(a)->Draw();
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