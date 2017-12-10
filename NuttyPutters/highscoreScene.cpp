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
	//Tracks Mouse 
	Track_Mouse(win);
	// Render
	Render(win);
}

//tracks mouse
void highscoreScene::Track_Mouse(GLFWwindow * win)
{
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

	for (int i = 0; i < 42; i++)
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
