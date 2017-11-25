// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton



// Default constructor
startScene::startScene() { }

// Deconstructor
startScene::~startScene() { }

// Function which gets mouse position, sets button manager value based on which 
// button is hovered over
void startScene::Track_Mouse(GLFWwindow *window)
{
	glfwGetCursorPos(window, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//this mess plots out where the buttons are for start scene
	if ((windowMgr::getInstance()->mouse_x >= 604 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 995 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 59 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 840 * windowMgr::getInstance()->windowScale))
	{
		if (windowMgr::getInstance()->mouse_y <= 200 * windowMgr::getInstance()->windowScale)
		{
			//highlights start game button
			windowMgr::getInstance()->button_manager = 1;
		}
		else if (windowMgr::getInstance()->mouse_y <= 332 * windowMgr::getInstance()->windowScale)
		{
			//highlights load game button
			windowMgr::getInstance()->button_manager = 2;
		}
		else if (windowMgr::getInstance()->mouse_y <= 456 * windowMgr::getInstance()->windowScale)
		{
			//highlights highscore button
			windowMgr::getInstance()->button_manager = 3;
		}
		else if (windowMgr::getInstance()->mouse_y <= 580 * windowMgr::getInstance()->windowScale)
		{
			//highlights highscore button
			windowMgr::getInstance()->button_manager = 4;
		}
		else if (windowMgr::getInstance()->mouse_y <= 710 * windowMgr::getInstance()->windowScale)
		{
			//highlights options button
			windowMgr::getInstance()->button_manager = 5;
		}
		else if (windowMgr::getInstance()->mouse_y <= 840 * windowMgr::getInstance()->windowScale)
		{
			//ghighlights exit button
			windowMgr::getInstance()->button_manager = 6;
		}
	}
}
// Setup; does nothing atm
void startScene::Init(GLFWwindow* win)
{
	// Set initial button press bools to false
	windowMgr::getInstance()->upPressed = windowMgr::getInstance()->downPressed = windowMgr::getInstance()->leftPressed = windowMgr::getInstance()->rightPressed = windowMgr::getInstance()->enterPressed = windowMgr::getInstance()->mouseLpressed = false;
	// Background image will never change so setup here
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["startBackground"]);
	windowMgr::getInstance()->button_manager = 0;

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

	cout << "Textures after start: " << windowMgr::getInstance()->textures.size() << endl;
	
}

void startScene::Loop(GLFWwindow* win)
{
	// Calculate dt
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	dt = (float)(thisFrame - lastFrame);

	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//tracks mouse
	Track_Mouse(win);

	// Input
	Input(win);

	// Update
	Update(win);

	// Render
	Render(win);
}

void startScene::Action(GLFWwindow* win) 
{
	if (windowMgr::getInstance()->button_manager == 6)
	{
		windowMgr::getInstance()->sceneManager.changeScene(0);

	}
	else if (windowMgr::getInstance()->button_manager == 5)
	{
		ShellExecute(NULL, "open", "http://www.calumtempleton.com", NULL, NULL, SW_SHOWNORMAL);
	}
	else
	{
		windowMgr::getInstance()->sceneManager.changeScene(windowMgr::getInstance()->button_manager + 1);
	}
}
// Act on input
void startScene::Input(GLFWwindow * win)
{
	switch (windowMgr::getInstance()->button_manager)
	{
		//cases for the buttons to switch to each screen
		case 0:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["loadGameBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["highscoresBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["optionsBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["internetBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			break;
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
	if (glfwGetKey(win, GLFW_KEY_ENTER))
	{
		windowMgr::getInstance()->enterPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 5.0f)
	{
		if (windowMgr::getInstance()->enterPressed)
		{
			Action(win);
			windowMgr::getInstance()->enterPressed = false;
		}
	}
	if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) && total_time >= 5.0f)
	{
		windowMgr::getInstance()->mouseLpressed = true;
	}
	if (!glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT))
	{
		if (windowMgr::getInstance()->mouseLpressed)
		{
			Action(win);
			windowMgr::getInstance()->mouseLpressed = false;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_UP))
	{
			windowMgr::getInstance()->upPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_UP))
	{
		if (windowMgr::getInstance()->upPressed)
		{
			total_time = 0.0f;
			if (windowMgr::getInstance()->button_manager == 1)
			{
				windowMgr::getInstance()->button_manager = 6;
			}
			else
			{
				windowMgr::getInstance()->button_manager--;
			}
			windowMgr::getInstance()->upPressed = false;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		windowMgr::getInstance()->downPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		if (windowMgr::getInstance()->downPressed)
		{
			if (windowMgr::getInstance()->button_manager == 6)
			{
				windowMgr::getInstance()->button_manager = 1;
			}
			else if (windowMgr::getInstance()->button_manager == 0)
			{
				windowMgr::getInstance()->button_manager = 6;
			}
			else
			{
				windowMgr::getInstance()->button_manager++;
			}

			windowMgr::getInstance()->downPressed = false;
		}
	}

	while (total_time <= 5.0f) 
	{
		total_time += 1.0f;
	}
	
}

void startScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
}

void startScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// Bind, update and draw HUD elements

	for (int a = 0; a < 7; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(startSceneTransform, hudVP);
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