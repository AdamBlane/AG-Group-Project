#include "highscoreScene.h"
#include "windowMgr.h" // to access singleton

// Constructor
highscoreScene::highscoreScene() { }
// Deconstructor
highscoreScene::~highscoreScene() { }

void highscoreScene::Init(GLFWwindow * win)
{
	// Setup the initial textures
	//windowMgr::getInstance()->ControlsTextureSetup();

	// Default load player one controls
	//windowMgr::getInstance()->ControlsButtonsSetup();
}

// Draw stuff
void highscoreScene::Loop(GLFWwindow * win)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	InputKeyboard(win);
	InputController(win);

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

//tracks mouse
void highscoreScene::Track_Mouse(GLFWwindow * win)
{
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
	windowMgr::getInstance()->ControlsTrackMouse();
}

//whenever a click occurs
void highscoreScene::Click(GLFWwindow * win)
{

}

// Input 
void highscoreScene::InputKeyboard(GLFWwindow* win)
{
	windowMgr::getInstance()->ControlsInputKeyboard();
}

void highscoreScene::InputController(GLFWwindow* win)
{
	windowMgr::getInstance()->ControlsInputController();
}

// Updates the keyboard function array
void highscoreScene::updateKeyboardFunctionsList(int keyboardButtonNumber, int additionalNumber)
{
	//windowMgr::getInstance()->ControlsUpdateKeyboard();
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

	for (int i = 0; i < 38; i++)
	{
		windowMgr::getInstance()->controllerMeshes.at(i)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->controllerMeshes.at(i)->Draw();
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
