#include "playerSelectScene.h"
#include "windowMgr.h"

// Constructor
playerSelectScene::playerSelectScene() { }
// Deconstructor
playerSelectScene::~playerSelectScene() { }

// Setup scene; does nothing atm
void playerSelectScene::Init(GLFWwindow * win)
{
	// Setup texture shader
	textureShader = new Shader("..\\NuttyPutters\\textureShader");

	// Setup target camera
	tarCam = new target_camera();
	tarCam->set_Posistion(vec3(0, 0, 5.0f));
	tarCam->set_Target(vec3(0, 0, 0));
	tarCam->set_projection(quarter_pi<float>(), (float)1600 / (float)900, 0.414f, 1000.0f);

	cout << "Textures before all: " << windowMgr::getInstance()->textures.size() << endl;
	// Background image will never change so setup here
	// Doesn't matter which mesh we use so pick first in list - set its scale, pos and texture
	windowMgr::getInstance()->meshes.at(0)->SetScale(9.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(0.0f, 0.0f, -1.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["playerSelectBackground"]);

	// Set up players label
	windowMgr::getInstance()->meshes.at(1)->SetScale(2.8f, 0.7f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-0.4, 1.4, 0.0));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playersLabel"]);

	// Set up one players label/button
	windowMgr::getInstance()->meshes.at(2)->SetScale(0.6f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.9, 1.4, 0.0));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["oneBtnSelected"]);

	// Set up two players label/button
	windowMgr::getInstance()->meshes.at(3)->SetScale(0.6f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(1.3, 1.4, 0.0));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["twoBtnUnselected"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(4)->SetScale(2.8f, 0.7f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0, 0.7, 0.0));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["difficultyLabel"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(5)->SetScale(1.4f, 0.7f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(-1.4, 0.0, 0.0));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["easyBtnSelected"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(6)->SetScale(1.4f, 0.7f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(0.0, 0.0, 0.0));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["medBtnUnselected"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(7)->SetScale(1.4f, 0.7f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(1.4, 0.0f, 0.0));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["hardBtnUnselected"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(8)->SetScale(2.8f, 0.7f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(0, -1.0, 0.0));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["startGameBtnUnselected"]);

	// Set up difficulty label
	windowMgr::getInstance()->meshes.at(9)->SetScale(2.8f, 0.7f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(0, -1.7, 0.0));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);

	cout << "Textures after start: " << windowMgr::getInstance()->textures.size() << endl;
}

// Draw stuff for this scene
void playerSelectScene::Loop(GLFWwindow * win)
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

// Act on user input 
void playerSelectScene::Input(GLFWwindow* win)
{
	//cout << "Button Select " << buttonSelect << endl;
	//cout << "Player Select " << playerSelect << endl;
	//cout << "Difficulty Select " << difficultySelect << endl;

	switch (buttonSelect)
	{
		//cases for the buttons to switch to each screen
	case 1:
		switch (playerSelect)
		{
		case 1:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["oneBtnSelected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["twoBtnUnselected"]);
			//numberOneLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\noneU.png", vec3(0.9, 1.4, 0.0), 0.6f, 0.6f);
			//numberTwoLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ntwo.png", vec3(1.3, 1.4, 0.0), 0.6f, 0.6f);
			selectedPlayers = 1;
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["oneBtnUnselected"]);
			windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["twoBtnSelected"]);
			//numberOneLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\none.png", vec3(0.9, 1.4, 0.0), 0.6f, 0.6f);
			//numberTwoLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ntwoU.png", vec3(1.3, 1.4, 0.0), 0.6f, 0.6f);
			selectedPlayers = 2;
			break;
		}
		// If the player presses down and 5 total_time has passed then
		if (glfwGetKey(win, GLFW_KEY_LEFT) && total_time >= 5.0f)
		{
			// Reset total time
			total_time = 0.0f;
			// If button selected is button 4 - main menu - then wrap around to button 1
			if (playerSelect == 1)
			{
				playerSelect = 2;
			}
			// else keep going down
			else
			{
				playerSelect--;
			}
		}
		// If the player presses down and 5 total_time has passed then
		if (glfwGetKey(win, GLFW_KEY_RIGHT) && total_time >= 5.0f)
		{
			// Reset total time
			total_time = 0.0f;
			// If button selected is button 4 - main menu - then wrap around to button 1
			if (playerSelect == 2)
			{
				playerSelect = 1;
			}
			// else keep going down
			else
			{
				playerSelect++;
			}
		}

		//startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\startgame.png", vec3(0, -1.0, 0.0), 2.8f, 0.7f);
		//returnLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\mainmenu.png", vec3(0, -1.7, 0.0), 2.8f, 0.7f);

		break;
	case 2:
		switch (difficultySelect)
		{
		case 1:
			/*easyLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\easyU.png", vec3(-1.4, 0.0f, 0.0), 1.4f, 0.7f);
			mediumLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\med.png", vec3(0, 0.0f, 0.0), 1.4f, 0.7f);
			hardLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\hard.png", vec3(1.4, 0.0f, 0.0), 1.4f, 0.7f);*/
			selectedDifficulty = 1;
			break;
		case 2:
			//easyLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\easy.png", vec3(-1.4, 0.0f, 0.0), 1.4f, 0.7f);
			//mediumLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\medU.png", vec3(0, 0.0f, 0.0), 1.4f, 0.7f);
			//hardLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\hard.png", vec3(1.4, 0.0f, 0.0), 1.4f, 0.7f);
			selectedDifficulty = 2;
			break;
		case 3:
			/*	easyLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\easy.png", vec3(-1.4, 0.0f, 0.0), 1.4f, 0.7f);
			mediumLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\med.png", vec3(0, 0.0f, 0.0), 1.4f, 0.7f);
			hardLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\hardU.png", vec3(1.4, 0.0f, 0.0), 1.4f, 0.7f);*/
			selectedDifficulty = 3;
			break;
		}

		// If the player presses down and 5 total_time has passed then
		if (glfwGetKey(win, GLFW_KEY_LEFT) && total_time >= 5.0f)
		{
			// Reset total time
			total_time = 0.0f;
			// If button selected is button 4 - main menu - then wrap around to button 1
			if (difficultySelect == 1)
			{
				difficultySelect = 3;
			}
			// else keep going down
			else
			{
				difficultySelect--;
			}
		}
		// If the player presses down and 5 total_time has passed then
		if (glfwGetKey(win, GLFW_KEY_RIGHT) && total_time >= 5.0f)
		{
			// Reset total time
			total_time = 0.0f;
			// If button selected is button 4 - main menu - then wrap around to button 1
			if (difficultySelect == 3)
			{
				difficultySelect = 1;
			}
			// else keep going down
			else
			{
				difficultySelect++;
			}
		}

		//	startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\startgame.png", vec3(0, -1.0, 0.0), 2.8f, 0.7f);
		//	returnLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\mainmenu.png", vec3(0, -1.7, 0.0), 2.8f, 0.7f);

		break;
	case 3:
		//	startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\startgameU.png", vec3(0, -1.0, 0.0), 2.8f, 0.7f);
		//	returnLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\mainmenu.png", vec3(0, -1.7, 0.0), 2.8f, 0.7f);
		break;
	case 4:
		//	startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\startgame.png", vec3(0, -1.0, 0.0), 2.8f, 0.7f);
		//	returnLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\mainmenuU.png", vec3(0, -1.7, 0.0), 2.8f, 0.7f);
		break;
	}

	// If enter is pressed and certain amount of time has passed
	if (glfwGetKey(win, GLFW_KEY_ENTER) && total_time >= 5.0f)
	{
		total_time = 0.0f;
		// If button select is 3 then start the game
		if (buttonSelect == 3)
		{
			windowMgr::getInstance()->sceneManager.changeScene(6, courseLength);
		}
		// If button select is 4 then return to main menu
		if (buttonSelect == 4)
		{
			windowMgr::getInstance()->sceneManager.changeScene(1);
		}
	}

	// Conditions which wrap when going from the bottom of the list back to the top
	if (glfwGetKey(win, GLFW_KEY_UP) && total_time >= 5.0f)
	{
		// Reset total time
		total_time = 0.0f;
		// If button selected is buttons 1 - player amount selection - then wrap around to button 4
		if (buttonSelect == 1)
		{
			buttonSelect = 4;
		}
		// else keep going up
		else
		{
			buttonSelect--;
		}
	}
	// If the player presses down and 5 total_time has passed then
	if (glfwGetKey(win, GLFW_KEY_DOWN) && total_time >= 5.0f)
	{
		// Reset total time
		total_time = 0.0f;
		// If button selected is button 4 - main menu - then wrap around to button 1
		if (buttonSelect == 4)
		{
			buttonSelect = 1;
		}
		// else keep going down
		else
		{
			buttonSelect++;
		}
	}

	// Increase the total time - used to make sure user doesnt go through options too fast
	total_time += 1.0f;
}

void playerSelectScene::Update(GLFWwindow* win)
{
	// Update target camera
	tarCam->update(0.00001);
}

void playerSelectScene::Render(GLFWwindow* win)
{
	// If camera type is target camera - used for HUD elements - then
	glm::mat4 hudVP = tarCam->get_Projection() * tarCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	windowMgr::getInstance()->meshes.at(0)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(0)->Draw();

	windowMgr::getInstance()->meshes.at(1)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(1)->Draw();

	windowMgr::getInstance()->meshes.at(2)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(2)->Draw();

	windowMgr::getInstance()->meshes.at(3)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(3)->Draw();

	windowMgr::getInstance()->meshes.at(4)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(4)->Draw();

	windowMgr::getInstance()->meshes.at(5)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(5)->Draw();

	windowMgr::getInstance()->meshes.at(6)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(6)->Draw();

	windowMgr::getInstance()->meshes.at(7)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(7)->Draw();

	windowMgr::getInstance()->meshes.at(8)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(8)->Draw();

	windowMgr::getInstance()->meshes.at(9)->thisTexture.Bind(0);
	textureShader->Update(playerSelectTransform, hudVP);
	windowMgr::getInstance()->meshes.at(9)->Draw();

	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY

	// Render any background stuff if required here

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	// Bind texture shader
	textureShader->Bind();

	glfwSwapBuffers(win);
	glfwPollEvents();
}