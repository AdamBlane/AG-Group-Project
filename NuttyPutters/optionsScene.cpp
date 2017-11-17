
#include "optionsScene.h"
#include "windowMgr.h"

// Constructor
optionsScene::optionsScene() { }
// Deconstructor
optionsScene::~optionsScene() { }

void optionsScene::Init(GLFWwindow * win)
{
	//to reformat texutures
	glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);

	cout << "Textures before all: " << windowMgr::getInstance()->textures.size() << endl;
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
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(2.0f, -1.5f, 0.0f));
	cout << "Textures after start: " << windowMgr::getInstance()->textures.size() << endl;
}


// Draw stuff
void optionsScene::Loop(GLFWwindow * win)
{
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


void optionsScene::Input(GLFWwindow* win)
{
	switch (button_manager)
	{
		case 1:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["windowBtnSelected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnSelected"]);
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnUnselected"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["backBtnSelected"]);
			break;
	}
	if (glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 3.0f)
	{
		total_time = 0.0f;
		//cases for changing size of screen
		switch (button_manager)
		{
		case 1:
			windowMgr::getInstance()->width = 1600;
			windowMgr::getInstance()->height = 900;
			windowMgr::getInstance()->PosX = 100;
			windowMgr::getInstance()->PosY = 100;
			break;
		case 2:
			windowMgr::getInstance()->width = 1920;
			windowMgr::getInstance()->height = 1080;
			windowMgr::getInstance()->PosX = 0;
			windowMgr::getInstance()->PosY = 0;
			break;
		case 3:
			windowMgr::getInstance()->sceneManager.changeScene(1);
			break;
		}
		if (button_manager != 3)
		{
			glfwSetWindowSize(win, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
			glfwSetWindowPos(win, windowMgr::getInstance()->PosX, windowMgr::getInstance()->PosY);
			optionsScene::Init(win);
		}
	}
	if (glfwGetKey(win, GLFW_KEY_UP) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 1)
		{
			button_manager = 3;
		}
		else
		{
			button_manager--;
		}
	}
	if (glfwGetKey(win, GLFW_KEY_DOWN) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		if (button_manager == 3)
		{
			button_manager = 1;
		}
		else
		{
			button_manager++;
		}
	}
	total_time += 0.5f;
}

void optionsScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void optionsScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();
	glDepthRange(0, 0.01);

	for (int a = 0; a < 4; a++)
	{
		windowMgr::getInstance()->meshes.at(a)->thisTexture.Bind(0);
		textureShader->Update(optionSceneTransform, hudVP);
		windowMgr::getInstance()->meshes.at(a)->Draw();
	}


	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
