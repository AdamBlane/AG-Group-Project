// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton
#include "courseGenV2.h"
#include "UI.h"
#include <thread>


// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene()
{

	// Delete everything in alg tiles since it was declared on heap
	for (auto &l : masterAlgTiles)
	{
		for (auto &t : l)
			delete(t);

		l.clear();
	}

	// Clear meshes in master tile
	// For every list
	for (auto &l : masterTiles)
	{
		// For every tile in list
		for (auto &t : l)
		{
			t.tileContent.clear();
			t.tileObstacle.clear();
		}
	}

	for (auto &l : masterObstacles)
	{
		l.clear();
	}
	// Clear all lists
	masterAlgTiles.clear();
	masterLevelSeeds.clear();
	masterTiles.clear();
	masterSceneryTiles.clear();
	pauseCamLevelProperties.clear();

	players.clear();

}

// Setup scene; seed is an optional param passed in by loadGameScene
void gameScene::Init(GLFWwindow* window, int courseLength, int playerCount, int levelCount, string seed)
{
	// MONDAY DEMO 
	continuePressed = true;

	// Set GL properties 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get initial cursor pos
	glfwSetCursorPos(window, cursor_x, cursor_y);
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);

	// DEMO ON MONDAY PRINT STATEMENTS
	cout << "\nGAME CONTROLS:" << endl;
	cout << "Pause - P" << endl;
	cout << "Reset Player 1 position - R" << endl;

	// LEVEL GEN
	//courseGenV2 cg(12);
	//algTiles = cg.run();

	// Record desired course size 
	courseSize = courseLength;

	// Record how many levels to load
	//numLevels = levelCount;
	numLevels = 3;
	//numLevels = 5;
	// TODO - above will only go to 3 levels - FIX

	// Save player count
	numPlayers = playerCount;

	// Pre-load all requried levels this game
	for (int i = 0; i < numLevels; ++i)
	{
		// Takes given seed, results in filled algTiles and levelSeed lists
		LoadGame(seed);
	}

	// Take all alg tiles list, turn into render tiles
	SetupTilesToBeDrawn();

	// Setup scenery tiles for all levels
	FillScenery();


	// Setup players 
	for (int p = 0; p < playerCount; ++p)
	{
		// Player setup
		// Create input config filename for this player
		string path = "..\\NuttyPutters\\input\\p" + to_string(p + 1) + "input.txt";
		Player player(path);
		player.transform.getScale() = vec3(0.5);
		player.transform.getPos() = vec3(-2.0 + p * 4, 1.0f, 0.0f);
		// Arrow setup	
		player.arrowTransform.getScale() = vec3(0.5);
		player.arrowTransform.getPos() = vec3(player.transform.getPos().x, player.transform.getPos().y - 1.6, player.transform.getPos().z);
		// Chase cam setup	
		windowMgr::getInstance()->chaseCams[p]->set_target_roation(vec3(0.0f, 0.0f, 0.0f));
		windowMgr::getInstance()->chaseCams[p]->set_target_pos(vec3(player.transform.getPos()));
		// 2 player?
		if (numPlayers == 2)
			windowMgr::getInstance()->chaseCams[p]->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / 2 / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
		else
			windowMgr::getInstance()->chaseCams[p]->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 1000.0f);
		// Set this player's id
		player.id = p + 1;
		// Add to players list
		players.push_back(player);
	}
	// Assign arrow textures for both player arrows
	windowMgr::getInstance()->p1ArrowMesh->SetTexture(windowMgr::getInstance()->textures["playerBlueTexture"]); //?
	windowMgr::getInstance()->p2ArrowMesh->SetTexture(windowMgr::getInstance()->textures["playerRedTexture"]);


	// Set camera startup properties
	cameraType = 1; // Want chase cam by default	
	windowMgr::getInstance()->freeCam->set_Posistion(vec3(0, 10, -10));
	windowMgr::getInstance()->freeCam->set_Target(vec3(0, 0, 0));
	// Pause cam initially takes the first two values (pos & target) from master list
	windowMgr::getInstance()->PAUSEtargetCam->set_Posistion(pauseCamLevelProperties[0]);
	windowMgr::getInstance()->PAUSEtargetCam->set_Target(pauseCamLevelProperties[1]);

	// Setup wormhole stuff for both players (regardless of player mode)
	Transform wormholeTransform;
	// Place under end hole
	//wormholeTransform.getPos() = masterAlgTiles[currentLevel].back()->thisCoords;
	wormholeTransform.getPos().y = -489;
	// To face upwards
	wormholeTransform.getRot().x = -1.5708;
	// Initially zero scale
	wormholeTransform.getScale() = vec3(0);
	wormholeTransforms.push_back(wormholeTransform);
	// Same again for second
	Transform wormholeTransform2;
	// Place under end hole

	wormholeTransform2.getPos().y = -489;
	// To face upwards
	wormholeTransform2.getRot().x = -1.5708;
	// Initially zero scale
	wormholeTransform2.getScale() = vec3(1);
	wormholeTransforms.push_back(wormholeTransform2);
	
	//wormholeTransform.getScale() = vec3(1);
	// Set pickup crate properties
	SetupPickupCrates();

	// Set dt based on player count
	//dt = (playerCount * 0.01) - 0.002;
	dt = 0.012;


	// Start game logic mgr
	// Pass in end hole position for two player mode
	gameLogicMgr.Setup(numPlayers, courseSize);



	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Loads either random level of certain size, or level by seed
void gameScene::LoadGame(string seed)
{
	// Create the course gen object that deals with seed and alg tile creation
	courseGenV2 cgSystem;
	// Setup the seed (either given or default)
	vector<int> levelSeed = cgSystem.SetupSeed(seed);
	// Add it to master seeds list
	masterLevelSeeds.push_back(levelSeed);
	// Use seed to generate the algorithm tiles list
	vector<BaseTile*> algTiles = cgSystem.SetupAlgTiles(levelSeed);
	// Add that to master algTiles list
	masterAlgTiles.push_back(algTiles);

}

// Takes in an algTiles list, spits out a sceneryTiles list
void gameScene::FillScenery()
{
	// Work on each algTiles list found in master list
	for (auto &l : masterAlgTiles)
	{
		// Get boundary positions of level tiles in x and z
		float xMax = 0;
		float xMin = 0;
		float zMax = 0;
		float zMin = 0;
		float yMin = 0;
		// For each tile in this list
		for (auto &t : l)
		{
			// Find min and max
			if (t->thisCoords.x > xMax)
				xMax = t->thisCoords.x;
			if (t->thisCoords.x < xMin)
				xMin = t->thisCoords.x;

			if (t->thisCoords.z > zMax)
				zMax = t->thisCoords.z;
			if (t->thisCoords.z < zMin)
				zMin = t->thisCoords.z;

			if (t->thisCoords.y < yMin)
				yMin = t->thisCoords.y;
		}
		// Add another tile's width to boundaries
		xMin -= 10; // To add another layer to the boundary, add 10 to each value
		zMin -= 20;
		xMax += 20;
		zMax += 10;
		// Set the pause target cam pos and target, now that we know level dimensions
		vec3 pauseCamPos, pauseCamTarget;
		pauseCamPos.x = xMin, pauseCamPos.y = 30.0f, pauseCamPos.z = zMin;
		pauseCamTarget.x = (xMax + xMin) / 2.0f, pauseCamTarget.y = 1.0f, pauseCamTarget.z = (zMax + zMin) / 2.0f;
		// Add these to pause cam properties list 
		pauseCamLevelProperties.push_back(pauseCamPos);
		pauseCamLevelProperties.push_back(pauseCamTarget);

		/*
		// Resulting scenery tiles list
		vector<Tile> sceneryTiles;
		// Starting in corner, fill with scenery tile if not already filled by level tile
		// Z
		for (int zPos = zMax; zPos > zMin; zPos -= 10) // 10 = tile size
		{
			// Work in rows; every x for a single z
			for (int xPos = xMin; xPos < xMax; xPos += 10)
			{
				vec3 thisPos = vec3(xPos, 0.0f, zPos); // Not dealing with ramps for now
				// Check if this pos is already taken by a level tile
				bool posTaken = false;
				// Contains search; there will only be one match
				for (int i = 0; i < l.size(); ++i)
				{
					if (l.at(i)->thisCoords == thisPos)
					{
						// We have a match
						posTaken = true;
					}
				}
				// If able to create a scenery tile...
				if (!posTaken)
				{
					// Create straight tile
					Tile tile(Tile::SCENERY, thisPos, 0);
					// Add to list of tiles to be rendered
					sceneryTiles.push_back(tile);
				}
			} // end x block
		} // end z block

		// Add fininshed scenery tiles list to master list
		masterSceneryTiles.push_back(sceneryTiles);

		*/
	}

}

// Creates tile classes to be drawn
void gameScene::SetupTilesToBeDrawn()
{
	// Go through each alg tile list
	for (int i = 0; i < masterAlgTiles.size(); i++)
	{
		// The list that will be generated, and added to master list at end
		vector<Tile> tiles;
		// The obstacle list that will be generated, and added to master list at end
		vector<int> obstacles;

		// Index of the current tile in current alg tiles list
		// Obstacles use this to know where in the list they are
		int index = 0;
		// TILE CREATION
		for (auto &t : masterAlgTiles[i])
		{
			// If this tile features an obstacle
			int obstacleID = 0;
			bool hasObstacle = false;

			// Ramp testing
			// Ramp up when dir is down
			if (t->id == 7)
			{
				Tile tile(Tile::BRIDGE, t->thisCoords, 0);
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			// Ramp down when dir is up
			if (t->id == 8)
			{
				// Create straight tile
				Tile tile(Tile::STRAIGHT, t->thisCoords, obstacleID);
				// Rotate on x
				tile.transform.getRot().x = -0.349066;
				tile.transform.getPos().y -= 1.8;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			if (t->id == 0) // Start
			{
				// Create start tile
				Tile tile(Tile::START, t->thisCoords, obstacleID);
				// Start tile needs rotating 180 (should always face down)
				tile.transform.getRot().y = 3.14159;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 1) // Straight V
			{
				// RNG between 0 and 1
				hasObstacle = Tile::randomNumber(0, 1);
				// If it randomed 1
				if (hasObstacle)
				{
					obstacleID = 2; // 2 is box obstacle
					//save this tile position in algTiles
					obstacles.push_back(index);
				}
				// Create straight tile
				Tile tile(Tile::STRAIGHT, t->thisCoords, obstacleID);
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 2) // Straight H
			{
				hasObstacle = Tile::randomNumber(0, 1);
				if (hasObstacle)
				{
					obstacleID = 2;
					//save this tile position in algTiles
					obstacles.push_back(index);
					obstacles.push_back(obstacleID);
				}
				// Create straight tile
				Tile tile(Tile::STRAIGHT, t->thisCoords, 0);
				// Straight needs rotating by 90, since it's vertical by default
				tile.transform.getRot().y = 1.5708;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 3) // Corner BL
			{
				// Create corner tile
				Tile tile(Tile::CORNER, t->thisCoords, obstacleID);
				// Corner needs rotating by 90
				tile.transform.getRot().y = 1.5708;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 4) // Corner BR
			{
				// Create corner tile
				Tile tile(Tile::CORNER, t->thisCoords, obstacleID);
				// Corner needs rotating by 90
				tile.transform.getRot().y = 3.14159;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 5) // Corner TL
			{
				// Create corner tile
				Tile tile(Tile::CORNER, t->thisCoords, obstacleID);
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 6) // Corner TR
			{
				// Create corner tile
				Tile tile(Tile::CORNER, t->thisCoords, obstacleID);
				// Corner needs rotating by 90
				tile.transform.getRot().y = -1.5708;
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 9) // end
			{
				// Create start tile
				Tile tile(Tile::END, t->thisCoords, obstacleID);
				// Consult direction to determine how much to rotate
				if (t->outDir.going_up)
				{
					tile.transform.getRot().y = 3.14159;
				}
				else if (t->outDir.going_down)
				{
					// No rotation needed
				}
				else if (t->outDir.going_left)
				{
					tile.transform.getRot().y = -1.5708;
				}
				else if (t->outDir.going_right)
				{
					tile.transform.getRot().y = 1.5708;
				}
				// Add to list of tiles to be rendered
				tiles.push_back(tile);

			}
			// Increase index for next tile
			index++;
		} // End for every tile this list

		// Add the populated tiles list to master
		masterTiles.push_back(tiles);
		// Add to master list of obstacles to be rendered
		masterObstacles.push_back(obstacles);
	} // end for every list in master list
}

// Sets up pickup crates for a level
void gameScene::SetupPickupCrates()
{
	// Clear from any previous level
	pickupPositionIndices.clear();
	// Setup the 5 crates
	// TODO - scale with difficulty
	for (int i = 0; i < (int)windowMgr::getInstance()->pickupCrateMeshes.size(); i++)
	{
		// Set texture of each crate
		// TODO - move this to init so we only do it once
		windowMgr::getInstance()->pickupCrateMeshes[i]->SetTexture(windowMgr::getInstance()->pickupCrateTexture);
		// Set position via pickup transforms list
		// Currently spaced 2 tiles apart, from start tile (index pos of 0)
		windowMgr::getInstance()->pickupCrateTransforms[i].setPos(vec3(masterAlgTiles[currentLevel].at(i * 2)->thisCoords.x, masterAlgTiles[currentLevel].at(i * 2)->thisCoords.y + 3.0f, masterAlgTiles[currentLevel].at(i * 2)->thisCoords.z));

		// Store tile position of algTiles for this level (to be matched with player.currentTile in collisions)
		pickupPositionIndices.push_back(i * 2);
	}
}

// Main game loop 
void gameScene::Loop(GLFWwindow* window)
{
	// Clear buffer bits (should this be done here?)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Input
	Input(window);

	// Update
	Update(window);

	// Collisions
	Collisions();

	// Render
	Render(window);
}

// Act on input
void gameScene::Input(GLFWwindow* window)
{

	// Loop around players and their inputs for both keyboard and controller
	int thisPlayer = 0;

	// REST POSITION FUNCTION
	if (glfwGetKey(window, GLFW_KEY_R))
	{
		resetPressed = true;
	}
	if (!glfwGetKey(window, GLFW_KEY_R))
	{
		if (resetPressed)
		{
			cout << "Player 1 position reset" << endl;
			// Move player 1 to center of tile
			players[0].transform.getPos() = (vec3(masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.x, masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.y + 0.5 + players[0].radius, masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.z));
			// Consider setting velocity to 0 

			// Flip flag
			resetPressed = false;
		}
	}


	// For every player
	for (auto &p : players)
	{
		// Jump
		if (glfwGetKey(window, p.jumpButton) && p.jumpCounter < 4) //AND player hasn't jumped thrice
		{
			// Increase player jump count
			p.jumpCounter++;
			p.jumpPressed = true;
		}
		if (!glfwGetKey(window, p.jumpButton))
		{
			// If jump button recently pressed 
			if (p.jumpPressed)
			{
				// SFX
				windowMgr::getInstance()->PlayThisSound("golfBallJump");
				// Tell physics system to add upwards impulse
				physicsSystem.Jump(p, 5.0f); // Arbitrary jump value
				// Ball is moving!
				p.isMoving = true;

				// Flip
				p.jumpPressed = false;
			}
		}

		// Pause
		if (glfwGetKey(window, GLFW_KEY_P))
		{
			// Change to pause target cam
			cameraType = 2;
			Render(window); // Render it
			// Quick screenshot - need to do this twice; once here, again on Save
			// Alt press below ensures only game window is captured
			keybd_event(VK_MENU, 0, 0, 0); //Alt Press
			keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press
			keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release

			// MONDAY DEMO PRINT COMMANDS
			cout << "\nPAUSE CONTROLS:" << endl;
			cout << "Save level - S\n Exit game - B\n Main menu - C\n Unpause - U" << endl;


			// Flip paused bool
			bool paused = true;
			// Pause input...
			while (paused)
			{
				// Render to show menu changes etc

				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				// Need this to listen for further key presses
				glfwPollEvents();
				// Exit game 
				if (glfwGetKey(window, GLFW_KEY_B))
				{
					// Scene 0 is no scene - it runs winMgr.CleanUp() and closes app
					windowMgr::getInstance()->sceneManager.changeScene(0);
					break;
				}

				// Save this level 
				if (glfwGetKey(window, GLFW_KEY_S))
				{
					// Only save if not previously saved/loaded a saved level
					if (!levelSaved)
					{
						// Open file to append level seed 
						ofstream saves("saves.csv", ofstream::app);
						// ID of each tile makes up seed
						for (auto &t : masterAlgTiles[currentLevel])
						{
							saves << t->id;
						}
						saves << endl;
						cout << "Level saved" << endl;
						levelSaved = true;

						// Also save image of level
						// Alt press below ensures only game window is captured
						keybd_event(VK_MENU, 0, 0, 0); //Alt Press
						keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press
						keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
						keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release


						//// The above saves the game window capture to clipboard
						//// Retrieve image from clipboard, taken from https://www.experts-exchange.com/questions/24769725/Saving-a-clipboard-print-screen-image-to-disk-in-a-jpg-or-bmp-file-format.html
						HWND hwnd = GetDesktopWindow();
						if (!OpenClipboard(hwnd))
							cout << "Error with HWND" << endl;
						OpenClipboard(NULL);
						HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
						if (hBitmap == NULL)
							cout << "Error with clipboard bmp data" << endl;
						CloseClipboard();
						CImage image;
						image.Attach(hBitmap);
						// Build string to save with level seed name
						string fileName = "..\\NuttyPutters\\savesImages\\";
						for (auto &i : masterLevelSeeds[currentLevel])
						{
							fileName += to_string(i);
						}
						fileName += ".bmp";
						image.Save(fileName.c_str(), Gdiplus::ImageFormatBMP);
						cout << "course image saved as " << fileName << endl;

						// Tell winMgr to update its saved images list
						windowMgr::getInstance()->UpdateSavesImages(fileName.c_str());
					} // end level saving code

				}

				// Unpause
				if (glfwGetKey(window, GLFW_KEY_U))
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					cameraType = 1;
					paused = false;
					break;
				}

				// Exit to main menu
				//This function resets the scene to an empty screen
				if (glfwGetKey(window, GLFW_KEY_C))
				{
					// glLoadIdentity(); might need this later
					windowMgr::getInstance()->sceneManager.changeScene(1);
					break;
				}

			} // end while paused

			cout << "\nUnpaused" << endl;

		} // end pause

		// If button one is pressed change to free camera
		if (glfwGetKey(window, GLFW_KEY_1))
		{
			// Set camera version to free camera
			cout << "Free Camera selected" << endl;
			cameraType = 0;
			// Set the free cam position to where the chasecam stopped moving for debugging can me changed later
			windowMgr::getInstance()->freeCam->set_Posistion(windowMgr::getInstance()->chaseCams[0]->get_Posistion());
		}

		// If button two is pressed change to chase camera
		if (glfwGetKey(window, GLFW_KEY_2))
		{
			// Set camera version to chase camera
			cout << "Chase Camera selected" << endl;
			cameraType = 1;
		}

		// If the X button is pressed then continue on with game -used for HUD elements
		if (glfwGetKey(window, GLFW_KEY_X))
		{
			continuePressed = true;
			// Start game timer
			gameLogicMgr.StartGameClock();
		}

		// FREE CAM controls
		if (cameraType == 0)
		{
			// Create vector to apply to current cam pos
			vec3 freeCamPos = vec3(0, 0, 0);

			// Camera controls
			if (glfwGetKey(window, GLFW_KEY_W))
			{
				freeCamPos = (vec3(0, 0, camSpeed * dt));
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				freeCamPos = (vec3(-camSpeed * dt, 0, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				freeCamPos = (vec3(0, 0, -camSpeed * dt));
			}
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				freeCamPos = (vec3(camSpeed * dt, 0, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_Q))
			{
				freeCamPos = (vec3(0, camSpeed * dt, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_E))
			{
				freeCamPos = (vec3(0, -camSpeed * dt, 0));
			}
			if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
			{
				camSpeed = 10.0f;
			}
			else
				camSpeed = 2.0f;

			// Move camera by new pos after input
			windowMgr::getInstance()->freeCam->move(freeCamPos);
		}
		// CHASE CAM controls
		else if (cameraType == 1)
		{
			// If ball is not moving then allow for angle on chase camera to be changed
			if (!p.isMoving)
			{
				// controls in the chase camera 
				if (glfwGetKey(window, p.rightButton))
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[thisPlayer]->yaw_it(camSpeed * dt * 0.5); // TODO - make camSpeed a variable to allow sensitivity settings
					// Decrease chase camera angle (out of 360 degrees)
					p.chaseCamAngle -= (camSpeed * dt * 0.5);
				}
				if (glfwGetKey(window, p.leftButton))
				{
					windowMgr::getInstance()->chaseCams[thisPlayer]->neg_yaw_it(camSpeed * dt * 0.5);
					// Increase chase camera angle (out of 360 degrees)
					p.chaseCamAngle += (camSpeed * dt * 0.5);
				}
			}



			// Camera movement
			if (glfwGetKey(window, p.downButton))
			{
				windowMgr::getInstance()->chaseCams[thisPlayer]->neg_pitch_it(camSpeed * dt * 0.5, p.transform.getPos(), windowMgr::getInstance()->chaseCams[thisPlayer]->get_Posistion(), windowMgr::getInstance()->chaseCams[thisPlayer]->get_pos_offset().y);
			}
			if (glfwGetKey(window, p.upButton))
			{
				windowMgr::getInstance()->chaseCams[thisPlayer]->pitch_it(camSpeed * dt * 0.5, p.transform.getPos(), windowMgr::getInstance()->chaseCams[thisPlayer]->get_Posistion(), windowMgr::getInstance()->chaseCams[thisPlayer]->get_pos_offset().y);
			}
			if (glfwGetKey(window, p.zoomOutButton))
			{
				//function to rotate 
				windowMgr::getInstance()->chaseCams[thisPlayer]->zoom_out(camSpeed * dt * 0.5);
			}
			if (glfwGetKey(window, p.zoomInButton))
			{
				windowMgr::getInstance()->chaseCams[thisPlayer]->zoom_in(camSpeed * dt * 0.5);
			}


			// If chase camera angle is greater than 360 reset to 0
			if (p.chaseCamAngle > 6.28319)
			{
				p.chaseCamAngle = 0.0;
			}
			// If chase camera angle is less than 0 then reset to 360
			else if (p.chaseCamAngle < 0)
			{
				p.chaseCamAngle = 6.28319;
			}


		} // end chase camera controls

		// Player fire
		if (continuePressed)
		{
			// If Fire is pressed 
			if (glfwGetKey(window, p.fireButtton))
			{
				if (!p.isMoving)
				{
					if (p.power < 50) // Enforce power limit
					{
						// Increment power counter as long as fire is held
						p.power += 0.2;
					}

					// Update power bar indicator
					gameLogicMgr.UpdatePowerBar(p);

					// Update the power bar based on the the fireCounter value 
					//powerBarTrans.getPos().x -= (fireCounter/5.0f) * powerBarMesh->getGeomPos().x;

					//powerBarTrans.getPos().x += fireCounter /100.0f; // This value has has to be 20 times the dividing value as the scale extends both ways not just in a positive direction
					//powerBarTrans.getScale().x += fireCounter/5.0f; // Update the scale based on the fireCounter value

					//############################### CODE FOR POWER BAR WILL GO HERE ########################

					// SET DIRECTION BASED ON CHASE CAM ANGLE
					// If camera angle is between 0 and 90
					if (p.chaseCamAngle >= 0 && p.chaseCamAngle < 1.5708)
					{
						// x = -sin(theta), z = cos(theta)
						p.direction = normalize(vec3(-sin(p.chaseCamAngle), 0.0, cos(p.chaseCamAngle)));
					}
					// If camera angle is between 90 and 180
					else if (p.chaseCamAngle > 1.5709 && p.chaseCamAngle < 3.14159)
					{
						// x = -cos(theta - 90), z = -sin(theta - 90)
						p.direction = normalize(vec3(-cos(p.chaseCamAngle - 1.5708), 0.0, -sin(p.chaseCamAngle - 1.5708)));
					}
					// If camera angle is between 180 and 270
					else if (p.chaseCamAngle > 3.1416 && p.chaseCamAngle < 4.71239)
					{
						// x = sin(theta - 180), z = -cos(theta - 180)
						p.direction = normalize(vec3(sin(p.chaseCamAngle - 3.1416), 0.0, -cos(p.chaseCamAngle - 3.1416)));
					}
					// If camera angle is anything else
					else if (p.chaseCamAngle > 4.724 && p.chaseCamAngle <= 6.28319)
					{
						// x = cos(theta - 270), z = sin(theta- 270)
						p.direction = normalize(vec3(cos(p.chaseCamAngle - 4.71239), 0.0, sin(p.chaseCamAngle - 4.71239)));
					}
					p.firePressed = true;
				}
			}
		}
		// When Fire is realesed
		if (!glfwGetKey(window, p.fireButtton))
		{
			// Only work if fire button was just released
			if (p.firePressed)
			{
				// Play SFX
				if (p.power < 20.0f)
				{
					windowMgr::getInstance()->PlayThisSound("golfBallPutt");
				}
				else
				{
					windowMgr::getInstance()->PlayThisSound("golfBallHit");
				}
				// Power measure accumulated by holding space is impulse magnitude
				// Normal of impulse is direction
				physicsSystem.Fire(p, p.power);
				// Reset fire power counter
				p.power = 0;
				// Increment player stroke counter
				p.strokeCounter++;
				// Get game logic to call UI update to reflect updated stroke counter
				gameLogicMgr.PlayerFired(thisPlayer, p);
				// And we're off! 
				p.isMoving = true;


				// Flip
				p.firePressed = false;
			}
		} // End if (p is released)

		// Input loop complete; increase thisPlayer counter
		thisPlayer++;
	}
}

// Update each player's current tile value 
void gameScene::SpatialPartitioningUpdate()
{
	// Records index as list is iterated over
	int tileTracker = 0;
	for (auto &t : masterAlgTiles[currentLevel])
	{
		// For every player
		for (auto &p : players)
		{
			// Is this player on this tile?
			if (t->isPlayerOnTile(p.transform.getPos()))
			{
				// Update player's personal current tile property
				p.currentTile = tileTracker;
			}
		}
		// Increase the tile tracker counter
		tileTracker++;
	}
}

// Acts on whether to load the next level or not
void gameScene::CheckLoadNextLevel()
{
	// For each player
	for (int i = 0; i < players.size(); ++i)
	{
		// Check if player is falling through end hole, go to next level or finish game
		if (players[i].ballInHole && players[i].transform.getPos().y < -450.0f) // Abritrary time period before tp
		{
			// If finished last level
			if (currentLevel == numLevels - 1 && !changedLevel)
			{
				// TODO - quit, pause, ask for next level etc

				// Stop camera from following player
				players[i].camFollow = false;
				// Update the total time count for this player 
				gameLogicMgr.SetEndTime(players[i]);
				// Print game score for this player
				gameLogicMgr.PrintPlayerScore(players[i]);
			}
			// If there is another level to go...
			else if (currentLevel < numLevels - 1)
			{
				// Move onto next level; draws behind player while falling
				// Only do this once (will trigger multiple frames)
				if (!changedLevel)
				{
					// If there are 2 players
					if (numPlayers == 2)
					{
						// If this is players[0] it needs to check players[1], and visa versa
						// Need a key to make a 0 always 1, and a 1 always 0
						// i = (i * -1) + 1 is key
						// i=0 -> (0 * -1) + 1 = 1
						// i=1 -> (1 * -1) + 1 = 0 
						// If other player isn't through end hole, tp him
						if (!players[(i  * -1) + 1].ballInHole)
						{
							// Incur time penalty for not finishing course
							players[(i  * -1) + 1].totalTime += 20;
							// Move him to new start tile
							players[(i  * -1) + 1].transform.setPos(vec3(2.0f, 1.0f, 0.0f));

						}
					}

					// Increase level index
					currentLevel++;
					// Prevent further increments
					changedLevel = true;
					// Respawn pickup crates
					SetupPickupCrates();
				}
			}



		} // end check if player is falling through hole

		// Check for falling player, spawn wormhole underneath them
		if (players[i].transform.getPos().y < -400.0f)
		{
			wormholeTransforms[i].getPos() = players[i].transform.getPos();
			wormholeTransforms[i].getPos().y = -489;
			// Open up wormhole!
			if (wormholeTransforms[i].getScale().x < 10)
			{
				wormholeTransforms[i].getScale() += vec3(0.2);
			}
		}

		// Otherwise check if player is falling from top of skybox onto next level
		if (players[i].isFalling && players[i].transform.getPos().y > 50.0f)
		{
			// Shrink this players wormhole
			wormholeTransforms[i].getScale() = vec3(0);
			// Ensure player lands on start tile
			players[i].transform.getPos().x = i * 2.0f;
			players[i].transform.getPos().z = 0.0f;
			// Allow level changing for next level
			changedLevel = false;
			// Change pause cam properties to match with this level
			windowMgr::getInstance()->PAUSEtargetCam->set_Posistion(pauseCamLevelProperties[currentLevel * 2]);
			windowMgr::getInstance()->PAUSEtargetCam->set_Target(pauseCamLevelProperties[currentLevel * 2 + 1]);
		}
	}

}

// Update player positions, spatitial partitioning, check for level changeover
void gameScene::Update(GLFWwindow* window)
{
	// Rotate pickup crates
	for (auto &t : windowMgr::getInstance()->pickupCrateTransforms)
	{
		float yRot = t.getRot().y + 1.0f * dt;
		t.setRot(vec3(0.0f, yRot, 0.0f));
	}

	// Check whether to load next level, pass in player
	CheckLoadNextLevel();


	// Update spatial partitioning
	SpatialPartitioningUpdate();


	// Update game clock
	gameLogicMgr.Update();


	// Free cam stuff
	static double ratio_width = quarter_pi<float>() / 1600.0;
	static double ratio_height = (quarter_pi<float>() * (1600 / 900)) / static_cast<float>(1600);
	double current_x, current_y;
	glfwGetCursorPos(window, &current_x, &current_y);
	// Calc delta
	double delta_x = current_x - cursor_x;
	double delta_y = current_y - cursor_y;
	// Multiply deltas by ratios
	delta_x *= ratio_width;
	delta_y *= ratio_height * -1; // -1 to invert on y axis
								  // Rotate camera by delta
	windowMgr::getInstance()->freeCam->rotate(delta_x, delta_y);
	windowMgr::getInstance()->freeCam->update(0.001);
	// Update cursor pos
	cursor_x = current_x;
	cursor_y = current_y;

	// Update chase cams
	if (numPlayers == 1)
	{	// Only follow if not just finished the last level
		if (players[0].camFollow)
		{
			windowMgr::getInstance()->chaseCams[0]->move(players[0].transform.getPos(), players[0].transform.getRot());
		}
		// Update
		windowMgr::getInstance()->chaseCams[0]->update(0.00001);
	}
	else if (numPlayers == 2)
	{
		// Only follow if not just finished the last level
		if (players[0].camFollow)
		{
			windowMgr::getInstance()->chaseCams[0]->move(players[0].transform.getPos(), players[0].transform.getRot());
		}
		windowMgr::getInstance()->chaseCams[0]->update(0.00001);
		// Only follow if not just finished the last level
		if (players[1].camFollow)
		{
			windowMgr::getInstance()->chaseCams[1]->move(players[1].transform.getPos(), players[1].transform.getRot());
		}
		windowMgr::getInstance()->chaseCams[1]->update(0.00001);
	}

	// Update hud target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);

	// Update pause target camera
	windowMgr::getInstance()->PAUSEtargetCam->update(0.00001);


	// Calculate dt
	double newTime = glfwGetTime();
	double frameTime = newTime - currentTime;
	currentTime = newTime;

	accumulator += frameTime;

	// Calculate fps
	//double fps = 1.0 / frameTime;
	//if (accumulator > dt)
		//cout << "FPS:" << fps << endl;


	// Update each player
	for (auto &p : players)
	{
		// Only apply physics if it's moving
		if (p.isMoving)
		{
			// Work out whether to apply gravity or not (is player on the floor/in air)
			// Update player's floor level for this tile - this tile floor level + 0.5 (half tile thickness) + player radius
			p.floorLevel = masterAlgTiles[currentLevel].at(p.currentTile)->floorLevel + 0.5 + p.radius;
			physicsSystem.ApplyGravity(p, p.floorLevel);

			// If time to perform another physics step																						 // Perform physics step	
			//if (accumulator >= dt)
			{
				// Update position
				physicsSystem.Integrate(p, dt, p.floorLevel);

				// Remove dt from accumulator
				//accumulator -= dt;
			}
		}
		// Update p arrow mesh position to follow player
		p.arrowTransform.getPos() = vec3(p.transform.getPos().x, p.transform.getPos().y - 1.6, p.transform.getPos().z);
	}



}

// Calls collision checking code of tile player is on
void gameScene::Collisions()
{

	for (auto &p : players)
	{
		// Check collisions for the tile each player is on only
		masterAlgTiles[currentLevel].at(p.currentTile)->CheckCollisions(p);



		// 2 player only collisions (crates, other players)
		if (numPlayers == 2)
		{
			// Only check for collisions with pickup crates when player shares a tile with one		
			for (int i = 0; i < pickupPositionIndices.size(); i++)
			{
				// Check if player.currentTile is equal to any found in pickupPositionIndices
				if (p.currentTile == pickupPositionIndices[i])
				{
					// Look for pickup crate collision
					// if distance between pickup crate position and player position is < 1
					dvec3 distance = abs((windowMgr::getInstance()->pickupCrateTransforms[pickupPositionIndices[i] / 2].getPos() - p.transform.getPos()));
					double magnitude = (distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z);
					if (magnitude < 1.0)
					{
						// Pickup crate, don't render anymore; remove ppi from list
						if (i != pickupPositionIndices.size() - 1)
						{
							pickupPositionIndices[i] = std::move(pickupPositionIndices.back());

						}
						pickupPositionIndices.pop_back();

						// Give player a powerup
						gameLogicMgr.RandomPowerup(p);
					} // end if players intersect crates
				} // end if player is on same tile as pickup crate
			} // end for each pickup

			 // If players are on the same tile, check for collisions with each other
			if (players[p.id - 1].currentTile == players[(p.id - 1) *-1 + 1].currentTile)
			{
				// Find distance between players
				dvec3 distance = abs(players[p.id - 1].transform.getPos() - players[(p.id - 1) *-1 + 1].transform.getPos());
				double magnitude = (distance.x * distance.x) + (distance.y * distance.y) + (distance.z * distance.z);
				// If less than two radii apart we have a collision
				if (magnitude < players[p.id - 1].radius + players[(p.id - 1) *-1 + 1].radius)
				{
					// First normalize the distance vector; the collision normal
					dvec3 collisionNormal = players[p.id - 1].transform.getPos() - players[(p.id - 1) *-1 + 1].transform.getPos();
					collisionNormal = normalize(collisionNormal);
					// Find the length of the component of each movement vector on collision normal
					float a1 = dot(players[p.id - 1].velocity, collisionNormal);
					float a2 = dot(players[(p.id - 1) *-1 + 1].velocity, collisionNormal);
					// Using optimized version according to https://www.gamasutra.com/view/feature/131424/pool_hall_lessons_fast_accurate_.php?page=3
					float optimizedP = (2.0 * (a1 - a2)) / (players[p.id - 1].mass + players[(p.id - 1) *-1 + 1].mass);
					// Calculate new veloctiy for each player
					vec3 v1New = players[p.id - 1].velocity - optimizedP * players[(p.id - 1) *-1 + 1].mass * collisionNormal;
					vec3 v2New = players[(p.id - 1) *-1 + 1].velocity + optimizedP * players[p.id - 1].mass * collisionNormal;
					// Set players velocity to 0, then assign new velocities
					players[p.id - 1].velocity = v1New;
					players[(p.id - 1) *-1 + 1].velocity = v2New;
					// Both players are moving
					players[p.id - 1].isMoving = players[(p.id - 1) *-1 + 1].isMoving = true;
					break;
				}

			}

		} // end 2 player collisions code

	} // end for each player collisions code


	// TODO Determine if this can be done more cheapply, and less hardcoded

	if (numPlayers == 2)
	{



	}

} // end collisions function

// Draw stuff
void gameScene::Render(GLFWwindow* window)
{
	// Check whether to render for 1 or 2 players
	if (numPlayers == 1)
	{
		glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
	}
	else if (numPlayers == 2)
	{
		// Player 1 has left hand side of screen
		glViewport(0, 0, windowMgr::getInstance()->width / 2, windowMgr::getInstance()->height);
	}

	// Calculate mvp matrix
	mat4 mvp;
	// If camera type is free camera then
	if (cameraType == 0)
	{
		mvp = windowMgr::getInstance()->freeCam->get_Projection() * windowMgr::getInstance()->freeCam->get_View();
	}
	// Else camera type is chase camera
	else if (cameraType == 1)
	{
		mvp = windowMgr::getInstance()->chaseCams[0]->get_Projection() * windowMgr::getInstance()->chaseCams[0]->get_View();
	}
	// Else if camera type is pause camera
	else if (cameraType == 2)
	{
		mvp = windowMgr::getInstance()->PAUSEtargetCam->get_Projection() * windowMgr::getInstance()->PAUSEtargetCam->get_View();
	}

	// Generat vp of HUD target camera
	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);


	// Display HUD (exact meshes to draw depend on player count)
	if (numPlayers == 1)
	{
		for (int i = 0; i < 9; i++)
		{
			windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
			windowMgr::getInstance()->meshes.at(i)->Draw();
		}
	}
	else // its 2 player
	{
		for (int i = 0; i < 4; i++)
		{
			windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
			windowMgr::getInstance()->meshes.at(i)->Draw();
		}
	}



	// Reset the depth range to allow for objects at a distance to be rendered
	glDepthRange(0.01, 1.0);
	// HUD RENDERING ENDED - THANK YOU AND HAVE A NICE DAY



	// Skybox 
	windowMgr::getInstance()->skyboxShader->Bind();
	windowMgr::getInstance()->skyboxShader->Update(windowMgr::getInstance()->texShaderTransform, mvp);
	windowMgr::getInstance()->skyboxMesh->Draw();

	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();


	// DRAW WORMHOLES
	for (int i = 0; i < wormholeTransforms.size(); i++)
	{
		windowMgr::getInstance()->wormholeTexture->Bind(0);
		windowMgr::getInstance()->textureShader->Update(wormholeTransforms[i], mvp);
		windowMgr::getInstance()->wormholeMeshes[i]->Draw();
	}



	// DRAW all level tiles
	for (auto &t : masterTiles[currentLevel])
	{
		t.drawTile(windowMgr::getInstance()->textureShader, mvp);
	}
	// DRAW all scenery tiles
	//for (auto &t : masterSceneryTiles[currentLevel])
	//{
	//	t.drawTile(windowMgr::getInstance()->textureShader, mvp);
	//}

	// Draw 2 Player stuff
	if (numPlayers == 2)
	{
		// Render player 2
		windowMgr::getInstance()->textures["playerBlueTexture"]->Bind(0);
		windowMgr::getInstance()->textureShader->Update(players[1].transform, mvp);
		windowMgr::getInstance()->player1Mesh->Draw();
		// Putting the above code below the arrow rendering gives odd behaviour of arrow
		// Perhaps due to reuse of texture being rebound?

		// Draw world clock
		for (auto &m : windowMgr::getInstance()->worldClock)
		{
			m->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, mvp);
			m->Draw();
		}

		// Draw pickup crates
		for (auto &ppi : pickupPositionIndices)
		{
			windowMgr::getInstance()->pickupCrateTexture->Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->pickupCrateTransforms[ppi / 2], mvp);
			// Corresponding pickup mesh is half index value 
			windowMgr::getInstance()->pickupCrateMeshes[ppi / 2]->Draw();
		}

	}


	// Render player 1
	windowMgr::getInstance()->textures["playerRedTexture"]->Bind(0);
	windowMgr::getInstance()->textureShader->Update(players[0].transform, mvp);
	windowMgr::getInstance()->player2Mesh->Draw();

	// Render player 1 arrow
	windowMgr::getInstance()->p1ArrowMesh->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(players[0].arrowTransform, mvp);
	// Rotate the arrow on the Y axis by - camera angle minus 90 degrees
	players[0].arrowTransform.setRot(glm::vec3(0, -players[0].chaseCamAngle - 1.5708, 0));



	// TEST
	//windowMgr::getInstance()->reboundEffectMesh->thisTexture.Bind(0);
	//windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, mvp);
	//windowMgr::getInstance()->reboundEffectMesh->Draw();

	// If ball is not moving draw arrow (ie dont draw arrow when ball moving as not needed)
	if (!players[0].isMoving) // was !golfBallMoving
	{
		// Draw the arrow
		windowMgr::getInstance()->p1ArrowMesh->Draw();
	}

	// Update texture shader for free cam
	windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, (windowMgr::getInstance()->freeCam->get_Projection() * windowMgr::getInstance()->freeCam->get_View()));


	// ################### PLAYER 2 SCREEN ################### //
	// ################### PLAYER 2 SCREEN ################### //
	// ################### PLAYER 2 SCREEN ################### //


	if (numPlayers == 2)
	{
		// Player 2 has the right hand vertical half of the screen
		glViewport(windowMgr::getInstance()->width / 2, 0, windowMgr::getInstance()->width / 2, windowMgr::getInstance()->height);

		// model view projection matrix for p2 cam
		mat4 mvp2;

		// Render player 2's chase camera
		mvp2 = windowMgr::getInstance()->chaseCams[1]->get_Projection() * windowMgr::getInstance()->chaseCams[1]->get_View();

		glDepthRange(0, 0.01);

		// TODO HUD stuff
		for (int i = 4; i < 8; i++)
		{
			windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
			windowMgr::getInstance()->meshes.at(i)->Draw();
		}



		// Reset the depth range to allow for objects at a distance to be rendered
		glDepthRange(0.01, 1.0);



		// Skybox 
		windowMgr::getInstance()->skyboxShader->Bind();
		windowMgr::getInstance()->skyboxShader->Update(windowMgr::getInstance()->texShaderTransform, mvp2);
		windowMgr::getInstance()->skyboxMesh->Draw();

		// Bind texture shader
		windowMgr::getInstance()->textureShader->Bind();

		// DRAW WORLD CLOCK
		for (auto &m : windowMgr::getInstance()->worldClock)
		{
			m->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, mvp2);
			m->Draw();
		}

		// Draw pickup crates
		for (auto &ppi : pickupPositionIndices)
		{
			windowMgr::getInstance()->pickupCrateTexture->Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->pickupCrateTransforms[ppi / 2], mvp2);
			// Corresponding pickup mesh is half index value 
			windowMgr::getInstance()->pickupCrateMeshes[ppi / 2]->Draw();
		}

		// DRAW WORMHOLES
		for (int i = 0; i < wormholeTransforms.size(); i++)
		{
			windowMgr::getInstance()->wormholeTexture->Bind(0);
			windowMgr::getInstance()->textureShader->Update(wormholeTransforms[i], mvp2);
			windowMgr::getInstance()->wormholeMeshes[i]->Draw();
		}

		// DRAW all level tiles
		for (auto &t : masterTiles[currentLevel])
		{
			t.drawTile(windowMgr::getInstance()->textureShader, mvp2);
		}
		//// DRAW all scenery tiles
		//for (auto &t : masterSceneryTiles[currentLevel])
		//{
		//	t.drawTile(windowMgr::getInstance()->textureShader, mvp2);
		//}


		// Render player 1
		windowMgr::getInstance()->textures["playerRedTexture"]->Bind(0);
		windowMgr::getInstance()->textureShader->Update(players[0].transform, mvp2);
		windowMgr::getInstance()->player1Mesh->Draw();
		// Can't seem to draw p1 arrow... though it seems fitting that you can't
		// see the other player's direction


		// Render player 2
		windowMgr::getInstance()->textures["playerBlueTexture"]->Bind(0);
		windowMgr::getInstance()->textureShader->Update(players[1].transform, mvp2);
		windowMgr::getInstance()->player2Mesh->Draw();

		// Render player 2 arrow
		windowMgr::getInstance()->p2ArrowMesh->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(players[1].arrowTransform, mvp2);
		players[1].arrowTransform.setRot(glm::vec3(0, -players[1].chaseCamAngle - 1.5708, 0));
		// Only draw if player 2 is still
		if (!players[1].isMoving)
		{
			windowMgr::getInstance()->p2ArrowMesh->Draw();
		}
	}



	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}


