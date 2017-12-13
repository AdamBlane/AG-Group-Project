// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton
#include "courseGenV2.h"
#include "UI.h"
#include "PauseScreen.h"
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

	paused = false;
	gameEnded = false;

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
	//cout << "\nGAME CONTROLS:" << endl;
	//cout << "Pause - P" << endl;
	//cout << "Reset Player 1 position - R" << endl;

	// LEVEL GEN	
	//ofstream seeds("seeds16.csv", ofstream::app);
	//vector<BaseTile*> algTiles;
	//for (int i = 0; i < 250; i++)
	//{
	//	courseGenV2 cg(16);
	//	algTiles = cg.run();
	//	for (auto &a : algTiles)
	//	{
	//		seeds << a->id;
	//	}
	//	seeds << endl;
	//	algTiles.clear();
	//}



	// Record desired course size 
	courseSize = courseLength;

	//courseSize = 12;


	// Record how many levels to load
	numLevels = levelCount;

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
			windowMgr::getInstance()->chaseCams[p]->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / 2 / (float)windowMgr::getInstance()->height, 0.414f, 40000.0f);
		else
			windowMgr::getInstance()->chaseCams[p]->set_projection(quarter_pi<float>(), (float)windowMgr::getInstance()->width / (float)windowMgr::getInstance()->height, 0.414f, 40000.0f);
		// Set this player's id
		player.id = p + 1;
		// Add to players list
		players.push_back(player);
	}

	// Assign arrow textures for both player arrows

	windowMgr::getInstance()->p1ArrowMesh->SetTexture(windowMgr::getInstance()->textures["playerBlueTexture"]); //?
	windowMgr::getInstance()->p2ArrowMesh->SetTexture(windowMgr::getInstance()->textures["playerRedTexture"]);
	


	windowMgr::getInstance()->p1ArrowMesh->SetTexture(windowMgr::getInstance()->textures["arrowBlueTexture"]);
	windowMgr::getInstance()->p2ArrowMesh->SetTexture(windowMgr::getInstance()->textures["arrowRedTexture"]);
  
	//Alien Planet
	windowMgr::getInstance()->alienPlanet->SetTexture(windowMgr::getInstance()->alienPlanetTex);
	alienPlanetTrans.getPos() = vec3(300.0f, -5.0f, 300.0f);
	alienPlanetTrans.getScale() = vec3(30.0f);

	//Galaxy Planet
	windowMgr::getInstance()->galaxyPlanet->SetTexture(windowMgr::getInstance()->galaxyPlanetTex);
	galaxyPlanetTrans.getPos() = vec3(-200.0f, 10.0f, 250.0f);
	galaxyPlanetTrans.getScale() = vec3(20.0f);

	//Gas Planet
	windowMgr::getInstance()->gasPlanet->SetTexture(windowMgr::getInstance()->gasPlanetTex);
	gasPlanetTrans.getPos() = vec3(250.0f, -20.0f, -350.0f);
	gasPlanetTrans.getScale() = vec3(40.0f);

	//Lava Planet
	windowMgr::getInstance()->lavaPlanet->SetTexture(windowMgr::getInstance()->lavaPlanetTex);
	lavaPlanetTrans.getPos() = vec3(-180.0f, -5.0f, -200.0f);
	lavaPlanetTrans.getScale() = vec3(10.0f);


	// Set camera startup properties
	cameraType = 1; // Want chase cam by default	
	windowMgr::getInstance()->freeCam->set_Posistion(vec3(0, 10, -10));
	windowMgr::getInstance()->freeCam->set_Target(vec3(0, 0, 0));
	// Pause cam initially takes the first two values (pos & target) from master list
	windowMgr::getInstance()->PAUSEtargetCam->set_Posistion(pauseCamLevelProperties[0]);
	windowMgr::getInstance()->PAUSEtargetCam->set_Target(pauseCamLevelProperties[1]);

	// Setup wormhole stuff for both players (regardless of player mode)
	Transform wormholeTransform;
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
	wormholeTransform2.getScale() = vec3(0);
	wormholeTransforms.push_back(wormholeTransform2);


	// Set pickup crate properties
	SetupPickupCrates();

	SetupWorldClock();
	// Set dt based on player count
	//dt = (playerCount * 0.01) - 0.002;
	dt = 0.012;



	// Perform game logic and UI setup
	// World clock should appear over end hole - pass in end hole position and direction


	gameLogicMgr.Setup(numPlayers);
	gameLogicMgr.StartGameClock();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

// Loads either random level of certain size, or level by seed
void gameScene::LoadGame(string seed)
{
	// Create the course gen object that deals with seed and alg tile creation
	courseGenV2 cgSystem;
	// Setup the seed (either given or default)
	vector<int> levelSeed = cgSystem.SetupSeed(seed, courseSize);
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
		// test
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
				Tile tile(Tile::BRIDGE, t->thisCoords, obstacleID);
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			// Ramp down when dir is up
			if (t->id == 8)
			{
				// Create straight tile
				Tile tile(Tile::GAP, t->thisCoords, obstacleID);
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
				// Create straight tile
				Tile tile(Tile::STRAIGHT, t->thisCoords, obstacleID);
				// Add to list of tiles to be rendered
				tiles.push_back(tile);
			}
			else if (t->id == 2) // Straight H
			{
				// Create straight tile
				Tile tile(Tile::STRAIGHT, t->thisCoords, obstacleID);
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
	for (int i = 0; i < courseSize / 2; i++)
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

// Sets up world clock on level load
void gameScene::SetupWorldClock()
{
	// Clear from any previous level
	worldClockTransforms.clear();
	// Set position of clock to just above end hole
	vec3 endPos = masterAlgTiles[currentLevel].back()->thisCoords;
	// Find direction of end hole
	string dir;
	// Hacking this for now
	if (masterAlgTiles[currentLevel].back()->outDir.going_down)
	{
		dir = "down";
		// Setup world clock initial texture values, and transform values
		for (int i = 0; i < windowMgr::getInstance()->worldClockMeshes.size(); i++)
		{
			Transform trans;
			trans.getScale() = vec3(1);
			if (i == 2) // Put colon in middle
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
			else
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

			// Set pos
			trans.getPos() = (vec3((endPos.x + 5.0f) - (i * 2.5), 2.0f, endPos.z));
			// Then rotate based on direction of end hole
			trans.getRot().y = 3.14159;

			// Add to list
			worldClockTransforms.push_back(trans);
		}
	}
	else if (masterAlgTiles[currentLevel].back()->outDir.going_up)
	{
		dir = "up";
		// Setup world clock initial texture values, and transform values
		for (int i = 0; i < windowMgr::getInstance()->worldClockMeshes.size(); i++)
		{
			Transform trans;
			trans.getScale() = vec3(1);
			if (i == 2) // Put colon in middle
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
			else
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

			// Set pos
			trans.getPos() = (vec3((endPos.x - 5.0f) + (i * 2.5), 2.0f, endPos.z));
			// Then rotate based on direction of end hole
			// Auto spawns correct rotation when dir is up

			// Add to list
			worldClockTransforms.push_back(trans);
		}
	}
	else if (masterAlgTiles[currentLevel].back()->outDir.going_left)
	{
		dir = "left";
		// Setup world clock initial texture values, and transform values
		for (int i = 0; i < windowMgr::getInstance()->worldClockMeshes.size(); i++)
		{
			Transform trans;
			trans.getScale() = vec3(1);
			if (i == 2) // Put colon in middle
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
			else
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

			// Set pos
			trans.getPos() = (vec3(endPos.x, 2.0f, (endPos.z + 5.0f) - (i * 2.5)));
			// Then rotate based on direction of end hole
			trans.getRot().y = 1.5708;

			// Add to list
			worldClockTransforms.push_back(trans);
		}
	}
	else if (masterAlgTiles[currentLevel].back()->outDir.going_right)
	{
		dir = "right";
		// Setup world clock initial texture values, and transform values
		for (int i = 0; i < windowMgr::getInstance()->worldClockMeshes.size(); i++)
		{
			Transform trans;
			trans.getScale() = vec3(1);
			if (i == 2) // Put colon in middle
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(10));
			else
				windowMgr::getInstance()->worldClockMeshes.at(i)->SetTexture(windowMgr::getInstance()->numberTextures.at(0));

			// Set pos
			trans.getPos() = (vec3(endPos.x, 2.0f, (endPos.z - 5.0f) + (i * 2.5)));
			// Then rotate based on direction of end hole
			trans.getRot().y = -1.5708;

			// Add to list
			worldClockTransforms.push_back(trans);
		}
	}

	cout << dir << endl;

}

// Called from pause menu; screenshots and saves current level to file
void gameScene::Save_Level(GLFWwindow* win)
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
		//cout << "course image saved as " << fileName << endl;

		// Tell winMgr to update its saved images list
		windowMgr::getInstance()->UpdateSavesImages(fileName.c_str());
	} // end level saving code

}

// Track where them mouse is on pause screen
void gameScene::Track_mouse(GLFWwindow* win)
{
	glfwGetCursorPos(win, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
	//cout << windowMgr::getInstance()->mouse_x << " " << windowMgr::getInstance()->mouse_y << endl;
	if ((windowMgr::getInstance()->mouse_x >= 604 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_x <= 995 * windowMgr::getInstance()->windowScale)
		&& (windowMgr::getInstance()->mouse_y >= 200 * windowMgr::getInstance()->windowScale) && (windowMgr::getInstance()->mouse_y <= 710 * windowMgr::getInstance()->windowScale))
	{
		previousMenuItem = currentMenuItem;
		if (windowMgr::getInstance()->mouse_y <= 255 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 1;
		}
		else if (windowMgr::getInstance()->mouse_y <= 380 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 2;
		}
		else if (windowMgr::getInstance()->mouse_y <= 505 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 3;
		}
		else if (windowMgr::getInstance()->mouse_y <= 645 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 4;
		}
		else if (windowMgr::getInstance()->mouse_y <= 800 * windowMgr::getInstance()->windowScale)
		{
			currentMenuItem = 5;
		}
		ChangeTextures(win);
	}
}

// Called when on pause screen; enact highlighted choice
void gameScene::Click_Or_Enter(GLFWwindow* win, bool pause)
{
	switch (currentMenuItem)
	{
		// Resume
	case 1:
		glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		cameraType = 1;
		pause = false;
		break;

		// Save this level 
	case 2:
		Save_Level(win);
		break;
		// Exit to main menu
		//This case resets the scene to an empty screen
	case 3:
		// Setup control screen meshes
		// gameLogicMgr.ShowControlScreen -> UImgr.ShowControlScreen
		windowMgr::getInstance()->doesUserWantControls = true;
		break;
	case 4:
		// glLoadIdentity(); might need this later
		windowMgr::getInstance()->sceneManager.changeScene(1);
		break;
		// Exit Game
	case 5:
		// Scene 0 is no scene - it runs winMgr.CleanUp() and closes app
		windowMgr::getInstance()->sceneManager.changeScene(0);
		break;
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

// Textures
void gameScene::ChangeTextures(GLFWwindow * win)
{
	int a;
	if (numPlayers == 1)
	{
		a = 9;
	}
	else if (numPlayers == 2)
	{
		a = 8;
	}
	switch (previousMenuItem)
	{
		//cases for the buttons to switch to each screen
	case 1:
		windowMgr::getInstance()->meshes.at(0 + a)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnUnselected"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(1 + a)->SetTexture(windowMgr::getInstance()->textures["saveBtnUnselected"]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(2 + a)->SetTexture(windowMgr::getInstance()->textures["controlsBtnUnselected"]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(3 + a)->SetTexture(windowMgr::getInstance()->textures["menuBtnUnselected"]);
		break;
	case 5:
		windowMgr::getInstance()->meshes.at(4 + a)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnUnselected"]);
		break;
	}
	switch (currentMenuItem)
	{
		//cases for the buttons to switch to each screen
	case 1:
		windowMgr::getInstance()->meshes.at(0 + a)->SetTexture(windowMgr::getInstance()->textures["unpauseBtnSelected"]);
		break;
	case 2:
		windowMgr::getInstance()->meshes.at(1 + a)->SetTexture(windowMgr::getInstance()->textures["saveBtnSelected"]);
		break;
	case 3:
		windowMgr::getInstance()->meshes.at(2 + a)->SetTexture(windowMgr::getInstance()->textures["controlsBtnSelected"]);
		break;
	case 4:
		windowMgr::getInstance()->meshes.at(3 + a)->SetTexture(windowMgr::getInstance()->textures["menuBtnSelected"]);
		break;
	case 5:
		windowMgr::getInstance()->meshes.at(4 + a)->SetTexture(windowMgr::getInstance()->textures["exitgameBtnSelected"]);
		break;
	}

}

// Player movement; jump
void gameScene::Jump(Player &p)
{
	// SFX
	windowMgr::getInstance()->PlayThisSound("golfBallJump");

	// Tell physics system to add upwards impulse
	physicsSystem.Jump(p, 5.0f); // Arbitrary jump value

								 // Ball is moving!
	p.isMoving = true;
}

// Player movement; fire press
void gameScene::FirePress(Player &p)
{
	// Should power counter be increasing?
	if (p.powerIncreasing)
	{
		// Increase power counter
		p.power += 0.2;

		// Check if limit was reached
		if (p.power >= 50)
		{
			p.powerIncreasing = false;
		}
	}
	// Otherwise power is decreasing
	else
	{
		// Decrease power counter
		p.power -= 0.2;

		// Check if power at 0
		if (p.power <= 0)
		{
			p.powerIncreasing = true;
		}
	}

	//cout << p.power << endl;
	// Update power bar indicator
	gameLogicMgr.UpdatePowerBar(p);


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

}

// Player movement; fire release
void gameScene::FireRelease(Player &p)
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
	gameLogicMgr.PlayerFired(p);
	// And we're off! 
	p.isMoving = true;

}

// Pause functionality here
void gameScene::Pause(GLFWwindow* window)
{
	// Perform a cheeky wee render
	// Quick screenshot - need to do this twice; once here, again on Save
	// Alt press below ensures only game window is captured
	keybd_event(VK_MENU, 0, 0, 0); //Alt Press
	keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release
	keybd_event(VK_MENU, 0, 0, 0); //Alt Press
	keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press
	keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
	keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release
	glViewport(0, 0, windowMgr::getInstance()->width, windowMgr::getInstance()->height);
	mat4 mvp;
	mvp = windowMgr::getInstance()->PAUSEtargetCam->get_Projection() * windowMgr::getInstance()->PAUSEtargetCam->get_View();
	//// Skybox 
	windowMgr::getInstance()->skyboxShader->Bind();
	windowMgr::getInstance()->skyboxShader->Update(windowMgr::getInstance()->texShaderTransform, mvp);
	windowMgr::getInstance()->skyboxMesh->Draw();
	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();
	// DRAW all level tiles
	for (auto &t : masterTiles[currentLevel])
	{
		t.drawTile(windowMgr::getInstance()->textureShader, mvp);
	}
	glDepthRange(0, 1.0);
	glfwSwapBuffers(window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();



	// Change to pause target cam
	cameraType = 2;
	// Flip paused bool
	paused = true;

	// Show mouse while paused
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// Pause game clock
	gameLogicMgr.PauseGameClock();

	while (paused)
	{
		//code to disable mouse
		windowMgr::getInstance()->previous_mouse_x = windowMgr::getInstance()->mouse_x;
		windowMgr::getInstance()->previous_mouse_y = windowMgr::getInstance()->mouse_y;
		glfwGetCursorPos(window, &windowMgr::getInstance()->mouse_x, &windowMgr::getInstance()->mouse_y);
		//tracks mouse
		if (windowMgr::getInstance()->previous_mouse_x != windowMgr::getInstance()->mouse_x || windowMgr::getInstance()->previous_mouse_y != windowMgr::getInstance()->mouse_y)
		{
			Track_mouse(window);
		}

		// If user on coontrol screen
		if (windowMgr::getInstance()->doesUserWantControls)
		{
			windowMgr::getInstance()->ControlsInputKeyboard();
			windowMgr::getInstance()->ControlsInputController();
			windowMgr::getInstance()->ControlsTrackMouse();
			windowMgr::getInstance()->returnToGame = true;
			//cout << "Input" << endl;
		}
		else if (windowMgr::getInstance()->previous_mouse_x != windowMgr::getInstance()->mouse_x && windowMgr::getInstance()->previous_mouse_y != windowMgr::getInstance()->mouse_y)
		{
			Track_mouse(window);
		}
		//************************** KEYBOARD MOVEMENT //

		if (glfwGetKey(window, GLFW_KEY_ENTER))
		{
			windowMgr::getInstance()->enterPressed = true;
		}
		if (!glfwGetKey(window, GLFW_KEY_ENTER) && total_time >= 5.0f)
		{
			if (windowMgr::getInstance()->enterPressed)
			{
				// If clicking save level, don't unpause
				if (currentMenuItem != 2 && currentMenuItem != 3)
				{
					paused = false;
				}
				// Perform action clicked
				Click_Or_Enter(window, paused); // why pass paused? 
				// Flip flag
				windowMgr::getInstance()->enterPressed = false;
			}
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) && total_time >= 5.0f)
		{
			windowMgr::getInstance()->mouseLpressed = true;
		}
		if (!glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT))
		{
			if (windowMgr::getInstance()->mouseLpressed)
			{
				if (currentMenuItem != 2 && currentMenuItem != 3)
				{
					paused = false;
				}
				Click_Or_Enter(window, paused);
				windowMgr::getInstance()->mouseLpressed = false;
			}
		}
		
		if (glfwGetKey(window, GLFW_KEY_UP))
		{
			windowMgr::getInstance()->upPressed = true;
		}
		if (!glfwGetKey(window, GLFW_KEY_UP))
		{
			if (windowMgr::getInstance()->upPressed)
			{
				previousMenuItem = currentMenuItem;
				if (currentMenuItem == 1)
				{
					currentMenuItem = 5;
				}
				else if (currentMenuItem == 0)
				{
					currentMenuItem = 5;
				}
				else
				{
					currentMenuItem--;
				}
				ChangeTextures(window);
				windowMgr::getInstance()->upPressed = false;
			}
		}

		if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			windowMgr::getInstance()->downPressed = true;
		}
		if (!glfwGetKey(window, GLFW_KEY_DOWN))
		{
			previousMenuItem = currentMenuItem;
			if (windowMgr::getInstance()->downPressed)
			{
				if (currentMenuItem == 5)
				{
					currentMenuItem = 1;
				}
				else
				{
					currentMenuItem++;
				}
				windowMgr::getInstance()->downPressed = false;
				ChangeTextures(window);
			}
		}
		//*********************************** KEYBOARD MOVEMENT END//
		// P1 controller input section
		// Get the state of controller one
		controllerOne = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &controllerOneButtonCount);
		// If controller 1 is connected, run controller input loop for p1 only
		if (controllerOne != NULL)
		{
			// Get axes details
			controllerOneAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &controllerOneAxisCount);

		
			// Enter
			if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]])
			{
				players[0].firePressedC = true;
			}
			if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]])
			{
				if (players[0].firePressedC)
				{
					// Paused is false, click or enter? 
					paused = false;
					Click_Or_Enter(window, paused);
					players[0].firePressedC = false;
				}
			}
			// Up
			if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][3]])
			{
				players[0].upPressedC = true;
			}
			if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][3]])
			{
				if (players[0].upPressedC)
				{
					// Paused is false, click or enter? 
					previousMenuItem = currentMenuItem;
					if (currentMenuItem == 1)
					{
						currentMenuItem = 5;
					}
					else if (currentMenuItem == 0)
					{
						currentMenuItem = 5;
					}
					else
					{
						currentMenuItem--;
					}
					ChangeTextures(window);
					players[0].upPressedC = false;
				}
			}
			// Down
			if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][5]])
			{
				players[0].downPressedC = true;
			}
			if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][5]])
			{
				if (players[0].downPressedC)
				{
					// Paused is false, click or enter? 
					if (currentMenuItem == 5)
					{
						currentMenuItem = 1;
					}
					else
					{
						currentMenuItem++;
					}
					ChangeTextures(window);
					players[0].downPressedC = false;
				}
			}
		}// end p1 pause controls
		// P2 controller input section
		// Get the state of controller two
		controllerTwo = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &controllerTwoButtonCount);
		// If controller 2 is connected  (& there are 2 players) run controller input loop for p2
		if (controllerTwo != NULL && numPlayers == 2)
		{
			// Get axes details of second controller
			controllerTwoAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &controllerTwoAxisCount);

			// Fire/Select
			if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][0]])
			{
				players[1].firePressedC = true;
			}
			if (GLFW_RELEASE == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][0]])
			{
				if (players[1].firePressedC)
				{
					// pause/click or enter
					players[1].firePressedC = false;
				}
			}

			// Up
			if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][3]])
			{
				players[1].upPressedC = true;
			}
			if (GLFW_RELEASE == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][3]])
			{
				if (players[1].upPressedC)
				{
					// pause/click or enter
					players[1].upPressedC = false;
				}
			}

			// Down 
			if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][5]])
			{
				players[1].downPressedC = true;
			}
			if (GLFW_RELEASE == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][5]])
			{
				if (players[1].downPressedC)
				{
					// pause/click or enter
					players[1].downPressedC = false;
				}
			}
		} // end p2 pause controls

		// Increase time delay tracker (prevents enter/Lclick reoccuring from last scene)
		if (total_time <= 5.0f)
		{
			total_time += 1.0f;
		}
		Render(window); // Render it

	}//endloop

	// Unpause clocks
	gameLogicMgr.UnpauseGameClock();

	std::cout << "\nUnpaused" << std::endl;
}

// Act on input
void gameScene::Input(GLFWwindow* window)
{
	// These functions are for debugging, to be excluded from final game
	// REST POSITION FUNCTION
	//if (glfwGetKey(window, GLFW_KEY_R))
	//{
	//	resetPressed = true;
	//}
	//if (!glfwGetKey(window, GLFW_KEY_R))
	//{
	//	if (resetPressed)
	//	{
	//		cout << "Player 1 position reset" << endl;
	//		// Move player 1 to center of tile
	//		players[0].transform.getPos() = (vec3(masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.x, masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.y + 0.5 + players[0].radius, masterAlgTiles[currentLevel].at(players[0].currentTile)->thisCoords.z));
	//		// Consider setting velocity to 0 

	//		// Flip flag
	//		resetPressed = false;
	//	}
	//}

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

	// INPUT LOOPS:
	// 1 - Keyboard input for both players (always runs)
	// 2 - If (1 controller connected) -> controller id mapped to player of that id
	//|| (controllers.size() > 0 && p.id == 1 ? GLFW_PRESS == controllers[p.id - 1][windowMgr::getInstance()->playerXboxControls[p.id - 1][7]] : (controllers.size() > 1 && p.id == 2 ? GLFW_PRESS == controllers[p.id - 1][windowMgr::getInstance()->playerXboxControls[p.id - 1][7]] : NULL))
	// 3 - If (2 controllers connected)

	// Keyboard input for each player
	for (auto &p : players)
	{
		// Jump press AND player hasn't jumped thrice
		if ((glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][7])) && p.jumpCounter < 3)
		{
			// Increase player jump count
			p.jumpCounter++;
			p.jumpPressed = true;
		}
		// Jump release
		if (!glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][7]))
		{
			// If jump button recently pressed 
			if (p.jumpPressed)
			{
				// Jump
				Jump(p);
				// Flip flag
				p.jumpPressed = false;
			}
		}

		// Pause
		if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][2]) && !gameEnded)
		{
			Pause(window);
		}


		// If the X button is pressed then continue on with game -used for HUD elements
		//if (glfwGetKey(window, GLFW_KEY_X))
		//{
		//	continuePressed = true;
		//	// Start game timer
		//	gameLogicMgr.StartGameClock();
		//}


		// CHASE CAM controls
		if (cameraType == 1)
		{
			// If ball is not moving then allow for angle on chase camera to be changed
			if (!p.gameOver)
			{
				// controls in the chase camera 
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][4]))
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[p.id - 1]->yaw_it(camSpeed * dt * 0.5);
					// Decrease chase camera angle (out of 360 degrees)
					p.chaseCamAngle -= (camSpeed * dt * 0.5);
				}
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][6]))
				{
					windowMgr::getInstance()->chaseCams[p.id - 1]->neg_yaw_it(camSpeed * dt * 0.5);
					// Increase chase camera angle (out of 360 degrees)
					p.chaseCamAngle += (camSpeed * dt * 0.5);
				}




				// Camera movement
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][5]))
				{
					windowMgr::getInstance()->chaseCams[p.id - 1]->neg_pitch_it(camSpeed * dt * 0.5, p.transform.getPos(), windowMgr::getInstance()->chaseCams[p.id - 1]->get_Posistion(), windowMgr::getInstance()->chaseCams[p.id - 1]->get_pos_offset().y);
				}
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][3]))
				{
					windowMgr::getInstance()->chaseCams[p.id - 1]->pitch_it(camSpeed * dt * 0.5, p.transform.getPos(), windowMgr::getInstance()->chaseCams[p.id - 1]->get_Posistion(), windowMgr::getInstance()->chaseCams[p.id - 1]->get_pos_offset().y);
				}
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][9]))
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[p.id - 1]->zoom_out(camSpeed * dt * 0.5);
				}
				if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][8]))
				{
					windowMgr::getInstance()->chaseCams[p.id - 1]->zoom_in(camSpeed * dt * 0.5);
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
			} // if game isn't over 
		} // end if !p.isMoving chase camera controls


		  // If Fire is pressed 
		if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][0]))
		{
			if (!p.isMoving)
			{
				FirePress(p);
				p.firePressed = true;
			}
		}
		// When Fire is realesed
		if (!glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[p.id - 1][0]))
		{
			// Only work if fire button was just released
			if (p.firePressed)
			{
				FireRelease(p);

				// Flip
				p.firePressed = false;
			}
		} // End if (p is released)

	} // end keyboard input for every player


	  // Get the state of controller one
	controllerOne = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &controllerOneButtonCount);
	// If controller 1 is connected, run controller input loop for p1 only
	if (controllerOne != NULL)
	{
		// Get axes details
		controllerOneAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &controllerOneAxisCount);

		// Jump press AND player hasn't jumped thrice
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][7]] && players[0].jumpCounter < 3)
		{
			// Increase player jump count
			players[0].jumpCounter++;
			players[0].jumpPressedC = true;
		}
		// Jump release
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][7]])
		{
			// If jump button recently pressed 
			if (players[0].jumpPressedC)
			{
				// Jump
				Jump(players[0]);
				// Flip flag
				players[0].jumpPressedC = false;
			}
		}

		// Pause
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][2]] && !gameEnded)
		{
			Pause(window);
		}


		// If the X button is pressed then continue on with game -used for HUD elements
		//if (glfwGetKey(window, GLFW_KEY_X))
		//{
		//	continuePressed = true;
		//	// Start game timer
		//	gameLogicMgr.StartGameClock();
		//}


		// CHASE CAM controls
		if (cameraType == 1)
		{
			// If ball is not moving then allow for angle on chase camera to be changed
			if (!players[0].gameOver)
			{
				// controls in the chase camera 
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][4]] || controllerOneAxis[0] < -0.5)
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[0]->yaw_it(camSpeed * dt * 0.5);
					// Decrease chase camera angle (out of 360 degrees)
					players[0].chaseCamAngle -= (camSpeed * dt * 0.5);
				}
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][6]] || controllerOneAxis[0] > 0.5)
				{
					windowMgr::getInstance()->chaseCams[0]->neg_yaw_it(camSpeed * dt * 0.5);
					// Increase chase camera angle (out of 360 degrees)
					players[0].chaseCamAngle += (camSpeed * dt * 0.5);
				}




				// Camera movement
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][5]] || controllerOneAxis[1] < -0.5)
				{
					windowMgr::getInstance()->chaseCams[0]->neg_pitch_it(camSpeed * dt * 0.5, players[0].transform.getPos(), windowMgr::getInstance()->chaseCams[0]->get_Posistion(), windowMgr::getInstance()->chaseCams[0]->get_pos_offset().y);
				}
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][3]] || controllerOneAxis[1] > 0.5)
				{
					windowMgr::getInstance()->chaseCams[0]->pitch_it(camSpeed * dt * 0.5, players[0].transform.getPos(), windowMgr::getInstance()->chaseCams[0]->get_Posistion(), windowMgr::getInstance()->chaseCams[0]->get_pos_offset().y);
				}
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][9]])
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[0]->zoom_out(camSpeed * dt * 0.5);
				}
				if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][8]])
				{
					windowMgr::getInstance()->chaseCams[0]->zoom_in(camSpeed * dt * 0.5);
				}


				// If chase camera angle is greater than 360 reset to 0
				if (players[0].chaseCamAngle > 6.28319)
				{
					players[0].chaseCamAngle = 0.0;
				}
				// If chase camera angle is less than 0 then reset to 360
				else if (players[0].chaseCamAngle < 0)
				{
					players[0].chaseCamAngle = 6.28319;
				}
			} // end if game isn't over allow camera control
		} // end chase camera controls


		  // If Fire is pressed 
		if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]])
		{
			if (!players[0].isMoving)
			{
				FirePress(players[0]);
				players[0].firePressedC = true;
			}
		}

		// When Fire is realesed
		if (GLFW_RELEASE == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]])
		{
			// Only work if fire button was just released
			if (players[0].firePressedC)
			{
				FireRelease(players[0]);

				players[0].firePressedC = false;
			}
		} // End if (p is released)

	}

	// IF THE GAME IS ENDED --> allow to go back to main menu
	if (gameEnded)
	{
		// if controller button is pressed
		if (controllerOne != NULL)
		{
			if (GLFW_PRESS == controllerOne[windowMgr::getInstance()->playerXboxControls[0][0]] || glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[0][0]))
			{
				windowMgr::getInstance()->sceneManager.changeScene(1);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
		}
		else if (glfwGetKey(window, windowMgr::getInstance()->playerKeyboardControls[0][0]))
		{
			windowMgr::getInstance()->sceneManager.changeScene(1);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}


	// Get the state of controller two
	controllerTwo = glfwGetJoystickButtons(GLFW_JOYSTICK_2, &controllerTwoButtonCount);
	// If controller 2 is connected  (& there are 2 players) run controller input loop for p2
	if (controllerTwo != NULL && numPlayers == 2)
	{
		// Get axes details of second controller
		controllerTwoAxis = glfwGetJoystickAxes(GLFW_JOYSTICK_2, &controllerTwoAxisCount);

		// Jump press AND player hasn't jumped thrice
		if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][7]] && players[1].jumpCounter < 3)
		{
			// Increase player jump count
			players[1].jumpCounter++;
			players[1].jumpPressedC = true;
		}
		// Jump release
		if (GLFW_RELEASE == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][7]])
		{
			// If jump button recently pressed 
			if (players[1].jumpPressedC)
			{
				// Jump
				Jump(players[1]);
				// Flip flag
				players[1].jumpPressedC = false;
			}
		}

		// Pause
		if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][2]] && !gameEnded)
		{
			Pause(window);
		}


		//// If the X button is pressed then continue on with game -used for HUD elements
		//if (glfwGetKey(window, GLFW_KEY_X))
		//{
		//	continuePressed = true;
		//	// Start game timer
		//	gameLogicMgr.StartGameClock();
		//}


		// CHASE CAM controls
		if (cameraType == 1)
		{
			// If ball is not moving then allow for angle on chase camera to be changed
			if (!players[1].gameOver)
			{
				// controls in the chase camera 
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][4]] || controllerTwoAxis[0] < -0.5)
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[1]->yaw_it(camSpeed * dt * 0.5);
					// Decrease chase camera angle (out of 360 degrees)
					players[1].chaseCamAngle -= (camSpeed * dt * 0.5);
				}
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][6]] || controllerTwoAxis[0] > 0.5)
				{
					windowMgr::getInstance()->chaseCams[1]->neg_yaw_it(camSpeed * dt * 0.5);
					// Increase chase camera angle (out of 360 degrees)
					players[1].chaseCamAngle += (camSpeed * dt * 0.5);
				}




				// Camera movement
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][5]] || controllerTwoAxis[1] < -0.5)
				{
					windowMgr::getInstance()->chaseCams[1]->neg_pitch_it(camSpeed * dt * 0.5, players[1].transform.getPos(), windowMgr::getInstance()->chaseCams[1]->get_Posistion(), windowMgr::getInstance()->chaseCams[1]->get_pos_offset().y);
				}
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][3]] || controllerTwoAxis[1] > 0.5)
				{
					windowMgr::getInstance()->chaseCams[1]->pitch_it(camSpeed * dt * 0.5, players[1].transform.getPos(), windowMgr::getInstance()->chaseCams[1]->get_Posistion(), windowMgr::getInstance()->chaseCams[1]->get_pos_offset().y);
				}
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][9]])
				{
					//function to rotate 
					windowMgr::getInstance()->chaseCams[1]->zoom_out(camSpeed * dt * 0.5);
				}
				if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][8]])
				{
					windowMgr::getInstance()->chaseCams[1]->zoom_in(camSpeed * dt * 0.5);
				}


				// If chase camera angle is greater than 360 reset to 0
				if (players[1].chaseCamAngle > 6.28319)
				{
					players[1].chaseCamAngle = 0.0;
				}
				// If chase camera angle is less than 0 then reset to 360
				else if (players[1].chaseCamAngle < 0)
				{
					players[1].chaseCamAngle = 6.28319;
				}
			} // end if game isn't over allow camera control
		} // end chase camera controls


		  // If Fire is pressed 
		if (GLFW_PRESS == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][0]])
		{
			if (!players[1].isMoving)
			{
				FirePress(players[1]);
				players[1].firePressedC = true;
			}
		}

		// When Fire is realesed
		if (GLFW_RELEASE == controllerTwo[windowMgr::getInstance()->playerXboxControls[1][0]])
		{
			// Only work if fire button was just released
			if (players[1].firePressedC)
			{
				FireRelease(players[1]);

				players[1].firePressedC = false;
			}
		} // End if (p is released)

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
			if (t->isPlayerOnTile(p))
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
			if (currentLevel == numLevels - 1 && !changedLevel) // don't end after just changing
			{
				// Calculate this players final score
				gameLogicMgr.SetScore(players[i]);


				// This player's game is over! (Locks their camera, prevents score being reset)
				players[i].gameOver = true;


				// Print game score for this player
				//gameLogicMgr.PrintPlayerScore(players[i]);

				// If 2 players, check if both players game over, that's the real gameOver
				if (numPlayers == 2 && players[i * -1 + 1].gameOver)
				{
					// Flip flag
					gameEnded = true;
					// Both players' score are set, print them
					gameLogicMgr.ShowEndgameScoreboard(players); // pass in players list

				}
				// Or it's just one player
				else if (numPlayers == 1)
				{
					// Flip flag
					gameEnded = true;
					// Player's score is set, print it
					gameLogicMgr.ShowEndgameScoreboard(players); // pass in players list
				}


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
					// Reset world clock
					SetupWorldClock();
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
			players[i].floorLevel = 0.5f + players[i].radius;
			// Allow level changing for next level
			changedLevel = false;
			// Change pause cam properties to match with this level
			windowMgr::getInstance()->PAUSEtargetCam->set_Posistion(pauseCamLevelProperties[currentLevel * 2]);
			windowMgr::getInstance()->PAUSEtargetCam->set_Target(pauseCamLevelProperties[currentLevel * 2 + 1]);
			// Reset player size to default
			players[i].transform.getScale() = vec3(0.5);
			players[i].radius = 0.5;
			players[i].mass = 1.2;
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
	// Rotate planets
	float alienRot = alienPlanetTrans.getRot().y + 0.05f * dt;
	alienPlanetTrans.setRot(vec3(0.0f, alienRot, 0.0f));
	float galaxyRot = galaxyPlanetTrans.getRot().y + 0.025f * dt;
	galaxyPlanetTrans.setRot(vec3(0.0f, galaxyRot, 0.0f));
	float gasRot = gasPlanetTrans.getRot().y + 0.04f * dt;
	gasPlanetTrans.setRot(vec3(0.0f, gasRot, 0.0f));
	float lavaRot = lavaPlanetTrans.getRot().y + 0.03 * dt;
	lavaPlanetTrans.setRot(vec3(0.0f, lavaRot, 0.0f));

	

	// Check whether to load next level, pass in player
	CheckLoadNextLevel();


	// Update spatial partitioning
	SpatialPartitioningUpdate();


	// Update game clock
	if (!gameEnded && !paused)
		gameLogicMgr.UpdateClock();


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
		if (!players[0].gameOver)
		{
			windowMgr::getInstance()->chaseCams[0]->move(players[0].transform.getPos(), players[0].transform.getRot());
		}
		// Update
		windowMgr::getInstance()->chaseCams[0]->update(0.00001);
	}
	else if (numPlayers == 2)
	{
		// Only follow if not just finished the last level
		if (!players[0].gameOver)
		{
			windowMgr::getInstance()->chaseCams[0]->move(players[0].transform.getPos(), players[0].transform.getRot());
		}
		windowMgr::getInstance()->chaseCams[0]->update(0.00001);
		// Only follow if not just finished the last level
		if (!players[1].gameOver)
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
			//p.floorLevel = masterAlgTiles[currentLevel].at(p.currentTile)->floorLevel + 0.5 + p.radius;
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
	// if the game has ended, reset viewport to normal
	if (numPlayers == 1 || paused == true || gameEnded)
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
	if (paused == true)
	{
		// If clicked on control option in pause screen, show control option screen
		if (windowMgr::getInstance()->doesUserWantControls)
		{
			for (int i = 1; i < 38; i++)
			{
				windowMgr::getInstance()->controllerMeshes.at(i)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->controllerMeshes.at(i)->Draw();
			}
		}
		// Otherwise show pause screen meshes
		else
		{
			if (numPlayers == 1)
			{
				for (int i = 9; i <= 13; i++)
				{
					windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
					windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
					windowMgr::getInstance()->meshes.at(i)->Draw();
				}
			}
			else if (numPlayers == 2)
			{
				for (int i = 8; i <= 12; i++)
				{
					windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
					windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
					windowMgr::getInstance()->meshes.at(i)->Draw();
				}
			}
		}

	} // end if paused is true
	//HUD for end game
	//if game has ended for both players
	else if (gameEnded)
	{
		//if number of players is 1
		if (numPlayers == 1)
		{
			//render background for player score
			windowMgr::getInstance()->winConditionsMeshes.at(0)->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
			windowMgr::getInstance()->winConditionsMeshes.at(0)->Draw();

			//render numbers for printing the score on screen
			for (int i = 0; i < gameLogicMgr.uiMgr.usedMeshesP1; i++)
			{
				windowMgr::getInstance()->player1ScoreMeshes.at(i)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->player1ScoreMeshes.at(i)->Draw();
			}
		}
		//if number of players is 2
		else if (numPlayers == 2)
		{
			//Checks what winning condition is satisfied

			//if p1 has higher score than p2 ->> p2 won
			if (gameLogicMgr.p1Score > gameLogicMgr.p2Score)
			{
				//printing background with "Player 2 won"
				windowMgr::getInstance()->winConditionsMeshes.at(2)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->winConditionsMeshes.at(2)->Draw();

			}
			//if p2 has higher score than p1 ->> p1 won
			else if (gameLogicMgr.p2Score > gameLogicMgr.p1Score)
			{
				//printing background with "Player 1 won"
				windowMgr::getInstance()->winConditionsMeshes.at(1)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->winConditionsMeshes.at(1)->Draw();
			}
			//if players have same score
			else if (gameLogicMgr.p1Score == gameLogicMgr.p2Score)
			{
				//printing background with "it's a draw"
				windowMgr::getInstance()->winConditionsMeshes.at(3)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->winConditionsMeshes.at(3)->Draw();
			}
			//End of IF statements

			//printing score for player 1, getting size from UI
			for (int i = 0; i < gameLogicMgr.uiMgr.usedMeshesP1; i++)
			{
				windowMgr::getInstance()->player1ScoreMeshes.at(i)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->player1ScoreMeshes.at(i)->Draw();
			}
			//printing score for player 2, getting size from UI
			for (int i = 0; i < gameLogicMgr.uiMgr.usedMeshesP2; i++)
			{
				windowMgr::getInstance()->player2ScoreMeshes.at(i)->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				windowMgr::getInstance()->player2ScoreMeshes.at(i)->Draw();
			}
		}
	}
	else if (!gameEnded)
	{
		// 1P Game Mode: Normal, unpaused, gameplay
		if (numPlayers == 1)
		{
			// render HUD meshes for p1
			for (auto &m : windowMgr::getInstance()->p1HUDmeshes)
			{
				m->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				m->Draw();
			}
		}
		// 2P Game Mode: Normal, unpaused, gameplay
		else
		{
			for (auto &m : windowMgr::getInstance()->p1HUDmeshes)
			{
				m->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				m->Draw();
			}

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

	// Draw world clock
	for (int i = 0; i < worldClockTransforms.size(); i++)
	{
		windowMgr::getInstance()->worldClockMeshes[i]->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(worldClockTransforms[i], mvp);
		windowMgr::getInstance()->worldClockMeshes[i]->Draw();
	}


	// Draw spaceships!
	for (int i = 0; i < windowMgr::getInstance()->threadCount; i++)
	{
		windowMgr::getInstance()->spaceshipMeshes[i]->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->spaceshipTransforms[i], mvp);
		windowMgr::getInstance()->spaceshipMeshes[i]->Draw();
	}


	


	//////////////// RENDER PLANETS //////////////
	windowMgr::getInstance()->alienPlanet->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(alienPlanetTrans, mvp);
	windowMgr::getInstance()->alienPlanet->Draw();

	windowMgr::getInstance()->galaxyPlanet->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(galaxyPlanetTrans, mvp);
	windowMgr::getInstance()->galaxyPlanet->Draw();

	windowMgr::getInstance()->gasPlanet->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(gasPlanetTrans, mvp);
	windowMgr::getInstance()->gasPlanet->Draw();

	windowMgr::getInstance()->lavaPlanet->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(lavaPlanetTrans, mvp);
	windowMgr::getInstance()->lavaPlanet->Draw();

	// Draw 2 Player stuff
	if (numPlayers == 2 && paused != true && !gameEnded)
	{
		// Render player 2
		windowMgr::getInstance()->textures["playerBlueTexture"]->Bind(0);
		windowMgr::getInstance()->textureShader->Update(players[1].transform, mvp);
		windowMgr::getInstance()->player1Mesh->Draw();
		// Putting the above code below the arrow rendering gives odd behaviour of arrow
		// Perhaps due to reuse of texture being rebound?



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


	if (numPlayers == 2 && paused != true && !gameEnded)
	{
		// Player 2 has the right hand vertical half of the screen
		glViewport(windowMgr::getInstance()->width / 2, 0, windowMgr::getInstance()->width / 2, windowMgr::getInstance()->height);

		// model view projection matrix for p2 cam
		mat4 mvp2;

		// Render player 2's chase camera
		mvp2 = windowMgr::getInstance()->chaseCams[1]->get_Projection() * windowMgr::getInstance()->chaseCams[1]->get_View();
		// Set depth range for hud rendering
		glDepthRange(0, 0.01);


		// Only render if game hasn't ended
		if (!gameEnded)
		{
			// Show p2 hud meshes
			for (auto &m : windowMgr::getInstance()->p2HUDmeshes)
			{
				m->thisTexture.Bind(0);
				windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
				m->Draw();
			}
		}



		// Reset the depth range to allow for objects at a distance to be rendered
		glDepthRange(0.01, 1.0);



		// Skybox 
		windowMgr::getInstance()->skyboxShader->Bind();
		windowMgr::getInstance()->skyboxShader->Update(windowMgr::getInstance()->texShaderTransform, mvp2);
		windowMgr::getInstance()->skyboxMesh->Draw();

		// Bind texture shader
		windowMgr::getInstance()->textureShader->Bind();

		// Draw world clock
		for (int i = 0; i < worldClockTransforms.size(); i++)
		{
			windowMgr::getInstance()->worldClockMeshes[i]->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(worldClockTransforms[i], mvp2);
			windowMgr::getInstance()->worldClockMeshes[i]->Draw();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();
}


