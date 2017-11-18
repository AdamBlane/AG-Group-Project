#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }

// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow* win)
{







	// Set background mesh properties
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["loadGameBackground"]);

	// Set image viewer properties
	// Create image meshes
	// 1600 / 3 = 533.33rec     900 / 3 = 300
	// 533.33 / 168 = 3.175	    300 / 168 = 1.786
	// Width and height of image meshes
	float w = 2.0f;
	float h = 1.2f;
	int images = seeds.size(); // Total number of saves images to show
	int imCount = 1;

	// Setup meshes
	for (int x = -1; x < 2; ++x)
		// This will be -1, 0, 1
	{
		for (int y = -1; y < 2; ++y)
		{
			float xPos, yPos;
			xPos = (x*w);
			yPos = (y*h);
			windowMgr::getInstance()->meshes.at(imCount)->SetPos(vec3(xPos, yPos, 0));
			windowMgr::getInstance()->meshes.at(imCount)->SetScale(w, h);
			//windowMgr::getInstance()->meshes.at(imCount)->SetTexture(windowMgr::getInstance()->textures["startBackground"]);
			imCount++;
		}
	}
	
	// Test
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->savesImages.at(0));
	cout << windowMgr::getInstance()->savesImages.size() << endl;
	// Read all saved seeds
	ifstream saves("saves.csv");

	// Read all saved games as strings
	while (!saves.eof())
	{
		string line;
		getline(saves, line);
		seeds.push_back(line); // store in seeds list
	}

}

// Main loop
void loadGameScene::Loop(GLFWwindow* win)
{
	// Input
	Input(win);
	//upadate
	Update(win);
	// Render
	Render(win);


}

// Act on input
void loadGameScene::Input(GLFWwindow* win)
{
	// B goes back to main menu screen
	if (glfwGetKey(win, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

	// TESTING SOUND
	if (glfwGetKey(win, GLFW_KEY_S))
	{
		windowMgr::getInstance()->PlayThisSound("menuSelect");
	}

	// MENU NAVIGATION
	// Go back/down an item
	if (glfwGetKey(win, GLFW_KEY_LEFT))
	{
		leftPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_LEFT))
	{
		// Only if left was just released...
		if (leftPressed)
		{
			// Reduce current seed count if not at min
			if (currentSeed > 0)
			{
				currentSeed--;
				cout << "Choice " << currentSeed << ": " << seeds.at(currentSeed) << endl;
			}
			leftPressed = false;
		}
	}

	// Go up/forward an item
	if (glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		rightPressed = true;
	}
	if (!glfwGetKey(win, GLFW_KEY_RIGHT))
	{
		if (rightPressed)
		{
			// Increment current seed count if not at max
			if (currentSeed < seeds.size() - 1)
			{
				currentSeed++;
				cout << "Choice " << currentSeed << ": " << seeds.at(currentSeed) << endl;
			}
			rightPressed = false;
		}

	}
	// Select this level to load
	if (glfwGetKey(win, GLFW_KEY_R))
	{
		enterPressed = true;
	}

	if (!glfwGetKey(win, GLFW_KEY_R))
	{
		if (enterPressed)
		{
			// Current seed is index of seeds list, send as optional param
			windowMgr::getInstance()->sceneManager.changeScene(6, 12, seeds.at(currentSeed)); // 12 is mandatory course lenght (to be disregarded dw)
		
			enterPressed = false;
		}
	}
	
}

// Update 
void loadGameScene::Update(GLFWwindow* win)
{
	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);
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
	for (int i = 0; i < 10; i++)
	{
		windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(i)->Draw();
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
