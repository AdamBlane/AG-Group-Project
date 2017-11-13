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

	// Load HUD information - NOTE TO KEEP ASPECT RATIO, 2.0f = 250 pixels - calulate based on image size
	// Stroke HUD Label setup - Object, Texture, position, X scale, Y scale
	//playersLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\players.png", vec3(-0.4, 1.4, 0.0), 2.8f, 0.7f);
	////numberThreeLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\nthree.png", vec3(1.5, 1.725, 0.0), 0.5f, 0.5f);
	////numberFourLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\nfour.png", vec3(2.0, 1.725, 0.0), 0.5f, 0.5f);
	//difficultyLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\difficulty.png", vec3(0.0, 0.7, 0.0), 2.8f, 0.7f);
	//playerSelectBackgroundMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\grass.png", vec3(0, 0.0, 0.0), 10.0f, 10.0f);

	//numberOneLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\noneU.png", vec3(0.9, 1.4, 0.0), 0.6f, 0.6f);
	//numberTwoLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ntwo.png", vec3(1.3, 1.4, 0.0), 0.6f, 0.6f);
	//easyLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\easyU.png", vec3(-1.4, 0.0f, 0.0), 1.4f, 0.7f);
	//mediumLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\med.png", vec3(0, 0.0f, 0.0), 1.4f, 0.7f);
	//hardLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\hard.png", vec3(1.4, 0.0f, 0.0), 1.4f, 0.7f);
	//startGameLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\startgame.png", vec3(0, -1.0, 0.0), 2.8f, 0.7f);
	//returnLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\mainmenu.png", vec3(0, -1.7, 0.0), 2.8f, 0.7f);
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
	cout << "Button Select " << buttonSelect << endl;
	cout << "Player Select " << playerSelect << endl;
	cout << "Difficulty Select " << difficultySelect << endl;

	switch (buttonSelect)
	{
		//cases for the buttons to switch to each screen
		case 1:
			switch (playerSelect)
			{
				case 1:
					//numberOneLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\noneU.png", vec3(0.9, 1.4, 0.0), 0.6f, 0.6f);
					//numberTwoLabelMesh = new Mesh(Mesh::RECTANGLE, "..\\NuttyPutters\\ntwo.png", vec3(1.3, 1.4, 0.0), 0.6f, 0.6f);
					selectedPlayers = 1;
					break;
				case 2:
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
		else if (buttonSelect == 4)
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

	// Bind, update and draw the background
	//playerSelectBackgroundMesh->thisTexture->Bind(0);
	//textureShader->Update(playerSelectBackgroundTrans, hudVP);
	//playerSelectBackgroundMesh->Draw();
	//// Bind, update and draw the number label HUDs
	//playersLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(playersLabelTrans, hudVP);
	//playersLabelMesh->Draw();
	//numberOneLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(numberOneLabelTrans, hudVP);
	//numberOneLabelMesh->Draw();
	//numberTwoLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(numberTwoLabelTrans, hudVP);
	//numberTwoLabelMesh->Draw();
	//// Bind, update and draw the difficulty HUDs
	//difficultyLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(difficultyLabelTrans, hudVP);
	//difficultyLabelMesh->Draw();
	//easyLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(easyLabelTrans, hudVP);
	//easyLabelMesh->Draw();
	//mediumLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(mediumLabelTrans, hudVP);
	//mediumLabelMesh->Draw();
	//hardLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(hardLabelTrans, hudVP);
	//hardLabelMesh->Draw();
	//// Bind, update and draw option HUDs
	//startGameLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(startGameLabelTrans, hudVP);
	//startGameLabelMesh->Draw();
	//returnLabelMesh->thisTexture->Bind(0);
	//textureShader->Update(returnLabelTrans, hudVP);
	//returnLabelMesh->Draw();

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