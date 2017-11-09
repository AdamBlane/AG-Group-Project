#include "loadGameScene.h"
#include "windowMgr.h"


// Constructor
loadGameScene::loadGameScene() { }
// Deconstructor
loadGameScene::~loadGameScene() { }

// Setup scene; display choice saved games
void loadGameScene::Init(GLFWwindow* win)
{
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);

	// Load HUD information - NOTE TO KEEP ASPECT RATIO, 2.0f = 250 pixels - calulate based on image size
	// Stroke HUD Label setup - Object, Texture, position, X scale, Y scale
	background = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\highscore\\optbackground.png", vec3(0.0, 0.0, -1.0), 9.5f, 5.5f);

	// Load images into grid
	cout << "Load Game Screen" << endl;

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
	if (glfwGetKey(win, GLFW_KEY_ENTER))
	{
		// Current seed is index of seeds list, send as optional param
		windowMgr::getInstance()->sceneManager.changeScene(6, 12,seeds.at(currentSeed)); // 12 is mandatory course lenght (to be disregarded dw)
	}
	
}

void loadGameScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}
// Draw stuff
void loadGameScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();


	glDepthRange(0, 0.01);

	background->thisTexture->Bind(0);
	textureShader->Update(backgroundTrans, hudVP);
	background->Draw();

	/*backButton->thisTexture->Bind(0);
	textureShader->Update(backButtonTrans, hudVP);
	backButton->Draw();*/

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}
