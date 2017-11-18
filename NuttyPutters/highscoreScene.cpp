

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
	// First int is button on the controller - Second int is mesh value
	windowMgr::getInstance()->buttonValues.insert(std::pair<int, int>(0, 4));
	windowMgr::getInstance()->buttonValues.insert(std::pair<int, int>(1, 6));
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
		const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		// 6 axis, both anaolgues left/right, up/down =4 then L2 = 5 AND R2 =6 
		std::cout << "Number of axis available: " << axesCount << endl;
		//Print a few blank lines to see results movement
		cout << endl;
		cout << endl;
		cout << endl;
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

		// If button is pressed - list Xbox/Playstation button
		// If A/Square is pressed then 
		if (GLFW_PRESS == buttons[0])
		{
			cout << "A/Square button pressed" << endl;
			// Get the current action that is set to that button
			cout << windowMgr::getInstance()->buttonValues.find(0)->second << endl;
			// Update the necessary texture of the button pressed to querstion marks
			windowMgr::getInstance()->meshes.at(windowMgr::getInstance()->buttonValues.find(0)->second)->SetTexture(windowMgr::getInstance()->textures["questionMarkLbl"]);
			// Set a button boolean to true
			aButtonPressed = true;
		}

		if (GLFW_PRESS == buttons[1])
		{
			cout << "B/X(Playstation) button pressed" << endl;
		}
		if (GLFW_PRESS == buttons[2])
		{
			cout << "X(Xbox)/Circle button pressed" << endl;
		}
		if (GLFW_PRESS == buttons[3])
		{
			cout << "Y/Triangle button pressed" << endl;
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


