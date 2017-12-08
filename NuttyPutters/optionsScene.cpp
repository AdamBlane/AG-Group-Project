
#include "optionsScene.h"
#include "windowMgr.h"

// Constructor
optionsScene::optionsScene() { }
// Deconstructor
optionsScene::~optionsScene() { }

void optionsScene::Track_Mouse(GLFWwindow *window)
{
	glfwGetCursorPos(window, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if ((windowMgr::getInstance()->mouse_x >= 604 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 995 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 59 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 710 * windowMgr::getInstance()->windowScale))
	{
		previousMenuItem = currentMenuItem;
		if (windowMgr::getInstance()->mouse_y <= 200 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 1;
		}
		else if (windowMgr::getInstance()->mouse_y <= 332 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 2;
		}
		else if (windowMgr::getInstance()->mouse_y <= 456 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 3;
		}
		else if (windowMgr::getInstance()->mouse_y <= 580 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 4;
		}
		else if (windowMgr::getInstance()->mouse_y <= 710 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 5;
		}
			ChangeTexutes(window);
	}
	else if ((windowMgr::getInstance()->mouse_x >= 1039 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 1429 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 711 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 839 * windowMgr::getInstance()->windowScale))
	{
		previousMenuItem = currentMenuItem;
		//highlights the back button
		currentMenuItem = 6;
		ChangeTexutes(window);
	}
}

// Textures
void optionsScene::ChangeTexutes(GLFWwindow * win)
{
	windowMgr::getInstance()->button_manager = currentMenuItem;
	switch (previousMenuItem)
	{
		case 1:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
			break;
		case 4:
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["halfBtnUnselected"]);
			break;
		case 5:
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["thirdBtnUnselected"]);
			break;
		case 6:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
			break;
	}
	switch (currentMenuItem)
	{
		//cases for the buttons to switch to each screen
		case 1:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnSelected"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnSelected"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnSelected"]);
			break;
		case 4:
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["halfBtnSelected"]);
			break;
		case 5:
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["thirdBtnSelected"]);
			break;
		case 6:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["backBtnSelected"]);
			break;
	}

}

//for the 
void optionsScene::Click_or_Enter(GLFWwindow *win)
{
	//get monitor 
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	//get monitor size in pixels
	const GLFWvidmode *mode = glfwGetVideoMode(primary);
	//cases for changing size of screen
	switch (windowMgr::getInstance()->button_manager)
	{
		// Case 1 - fullscreen
		case 1:
			//Sets window size by calling open gl function
			windowMgr::getInstance()->width = mode->width;
			windowMgr::getInstance()->height = mode->height;
			windowMgr::getInstance()->PosX = 0;
			windowMgr::getInstance()->PosY = 0;	

			break;
		// Case 2 - windowed at 1600x900
		case 2:
			windowMgr::getInstance()->width = mode->width / 1.2;
			windowMgr::getInstance()->height = mode->height / 1.2;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
		//case 3 fullscreen at 1280 x 720
		case 3:
			windowMgr::getInstance()->width = mode->width / 1.5;
			windowMgr::getInstance()->height = mode->height / 1.5;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
			//case 3 fullscreen at 1280 x 720
		case 4:
			windowMgr::getInstance()->width = mode->width / 2;
			windowMgr::getInstance()->height = mode->height / 2;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
			//case 3 fullscreen at 1280 x 720
		case 5:
			windowMgr::getInstance()->width = mode->width /3;
			windowMgr::getInstance()->height = mode->height /3;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
		// Case 3 - Back button
		case 6:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["exitBtnUnselected"]);
			windowMgr::getInstance()->sceneManager.changeScene(1);
			break;
	}
	// If window has been re-scaled
	if (windowMgr::getInstance()->button_manager != 6)
	{
		glfwSetWindowSizeLimits(win, windowMgr::getInstance()->width, windowMgr::getInstance()->height, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
		glfwSetWindowSize(win, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
		//sets window postion by calling opengl function - posiotn needs updating as first funtion is just scale
		glfwSetWindowPos(win, windowMgr::getInstance()->PosX, windowMgr::getInstance()->PosY);
		//calls the initalise function again mainly for viewport 
		glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
		windowMgr::getInstance()->setWindowScale(windowMgr::getInstance()->width);
	}
}

void optionsScene::Init(GLFWwindow * win)
{
	//resets the button manager
	windowMgr::getInstance()->button_manager = 0;

	// Setup target camera
	windowMgr::getInstance()->HUDtargetCam->set_Posistion(vec3(0, 0, 5.0f));
	windowMgr::getInstance()->HUDtargetCam->set_Target(vec3(0, 0, 0));
	windowMgr::getInstance()->HUDtargetCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["optionsBackground"]);

	// Perform setup of initial button configs - (un)selected textures
	// Pick next item in meshes list (increment the number by 1 each time)
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(2.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(0.0f, -0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["halfBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["thirdBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);

	//Create_Button(win);

}
// Draw stuff
void optionsScene::Loop(GLFWwindow * win)
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
	if (windowMgr::getInstance()->previous_mouse_x != windowMgr::getInstance()->mouse_x && windowMgr::getInstance()->previous_mouse_y != windowMgr::getInstance()->mouse_y)
	{
		Track_Mouse(win);
	}
	// Render
	Render(win);
}

void optionsScene::Input(GLFWwindow* win)
{
	switch (windowMgr::getInstance()->button_manager)
	{
		case 0:
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["halfBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["thirdBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
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
			Click_or_Enter(win);
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
			Click_or_Enter(win);
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
			previousMenuItem = currentMenuItem;
			if (currentMenuItem == 1)
			{
				currentMenuItem = 6;
			}
			else if (currentMenuItem == 0)
			{
				currentMenuItem = 6;
			}
			else
			{
				currentMenuItem--;
			}
			ChangeTexutes(win);
			windowMgr::getInstance()->upPressed = false;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN))
	{
		windowMgr::getInstance()->downPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_DOWN))
	{
		previousMenuItem = currentMenuItem;
		if (windowMgr::getInstance()->downPressed)
		{
			if (currentMenuItem == 6)
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

void optionsScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
}

void optionsScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();
	glDepthRange(0, 0.01);

	for (int a = 0; a < 7; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(optionSceneTransform, hudVP);
		windowMgr::getInstance()->meshes.at(a)->Draw();
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
