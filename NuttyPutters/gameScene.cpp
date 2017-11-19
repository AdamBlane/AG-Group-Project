// Externals

// Internals
#include "gameScene.h"
#include "windowMgr.h" // to access singleton

// Default constructor
gameScene::gameScene() { }
// Deconstructor
gameScene::~gameScene() { }

// Setup scene; seed is an optional param passed in by loadGameScene
void gameScene::Init(GLFWwindow* window, int courseLength, string seed)
{
	// Set GL properties 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Hide cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Get initial cursor pos
	glfwSetCursorPos(window, cursor_x, cursor_y);

	// LEVEL GEN
	//courseGenV2 cg(12);
	//algTiles = cg.run();

	// Record desired course size 
	courseSize = courseLength;

	// Load game
	LoadGame(seed);

	// Take alg tiles, turn into render tiles
	SetupTilesToBeDrawn();

	// Setup scenery tiles
	FillScenery();

	// TODO - find a way to not init this here
	// Skybox stuff
	vector<string> filenames;
	//negx and posx are inverted (mistery)
	filenames.push_back("..\\NuttyPutters\\skyboxes\\left.png");	//negx
	filenames.push_back("..\\NuttyPutters\\skyboxes\\right.png");	//posx
	filenames.push_back("..\\NuttyPutters\\skyboxes\\top.png");		//posy
	filenames.push_back("..\\NuttyPutters\\skyboxes\\bot.png");		//negy
	filenames.push_back("..\\NuttyPutters\\skyboxes\\back.png");	//posz
	filenames.push_back("..\\NuttyPutters\\skyboxes\\front.png");	//negz
	sky = new Mesh(filenames);


	// Setup player position (must use transform as it's a loaded model - not drawn)
	player1Transform.getScale() = vec3(0.5);
	player1Transform.getPos() = vec3(0.0, 1.0, 0.0);

	// Arrow - TODO - draw lower! 
	//arrowMesh = new Mesh(Mesh::CUBOID, "..\\NuttyPutters\\box.jpg", vec3(golfBallMesh->getGeomPos().x + 1.8, golfBallMesh->getGeomPos().y + 2.6, golfBallMesh->getGeomPos().z), 3.0f, 0.5f, 0.5f);
	arrowTransform.getScale() = vec3(0.5);
	arrowTransform.getPos() = vec3(1.8 + player1Transform.getPos().x, 2.6 + player1Transform.getPos().y, player1Transform.getPos().z);
	windowMgr::getInstance()->arrowMesh->SetTexture(windowMgr::getInstance()->textures["arrowTexture"]); //?
    
    // Set camera startup properties
	cameraType = 1;// Want chase cam by default	
	windowMgr::getInstance()->freeCam->set_Posistion(vec3(0, 10, -10));
	windowMgr::getInstance()->freeCam->set_Target(vec3(0, 0, 0));
	windowMgr::getInstance()->chaseCam->set_target_pos(vec3(player1Transform.getPos()));
	
	// Stroke HUD Label setup
	windowMgr::getInstance()->meshes.at(0)->SetScale(0.5f, 0.5f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(-3.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["zeroStrokeLbl"]);
	// Player HUD Labelsetup
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.0f, 0.25f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(-2.75f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["playerOneLbl"]);
	// Power HUD Label setup
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.0f, 0.25f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(3.0f, -1.375f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["powerLbl"]);
	// Power Bar HUD setup
	windowMgr::getInstance()->meshes.at(3)->SetScale(0.1f, 0.15f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(1.6f, -1.625f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["arrowTexture"]);
	// Power Bar Outline HUD setup
	windowMgr::getInstance()->meshes.at(4)->SetScale(2.0f, 0.25f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(2.5f, -1.625f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetTexture(windowMgr::getInstance()->textures["powerOutlineLbl"]);
	// Setup timer values 
	// Timer first unit
	windowMgr::getInstance()->meshes.at(5)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(5)->SetPos(vec3(2.8f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(5)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
	// Timer second unit
	windowMgr::getInstance()->meshes.at(6)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(6)->SetPos(vec3(2.95f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
	// Timer third unit
	windowMgr::getInstance()->meshes.at(7)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(7)->SetPos(vec3(3.15f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
	// Timer forth unit
	windowMgr::getInstance()->meshes.at(8)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(8)->SetPos(vec3(3.3f, 1.7f, 0.0f));
	windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
	// Timer semi colon
	windowMgr::getInstance()->meshes.at(9)->SetScale(0.25f, 0.25f);
	windowMgr::getInstance()->meshes.at(9)->SetPos(vec3(3.05f, 1.725f, 0.0f));
	windowMgr::getInstance()->meshes.at(9)->SetTexture(windowMgr::getInstance()->textures["semiColonLbl"]);
	// End Game HUDs
	// Centre Header one 
	windowMgr::getInstance()->meshes.at(10)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(10)->SetPos(vec3(0.0f, 0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["parFourLbl"]);
	// Centre Header two 
	windowMgr::getInstance()->meshes.at(11)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(11)->SetPos(vec3(0.0f, 0.25f, 0.0f));
	windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["timeTwoLbl"]);
	// Centre Footer one 
	windowMgr::getInstance()->meshes.at(12)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(12)->SetPos(vec3(0.0f, -0.25f, 0.0f));
	windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["semiColonLbl"]);
	// Centre Footer two 
	windowMgr::getInstance()->meshes.at(13)->SetScale(2.0f, 0.5f);
	windowMgr::getInstance()->meshes.at(13)->SetPos(vec3(0.0f, -0.75f, 0.0f));
	windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["xContinueLbl"]);

	// Splash Screen
	windowMgr::getInstance()->meshes.at(19)->SetScale(8.0f, 5.0f);
	windowMgr::getInstance()->meshes.at(19)->SetPos(vec3(0.0f, 0.0f, 0.0f));
	windowMgr::getInstance()->meshes.at(19)->SetTexture(windowMgr::getInstance()->textures["gameSplashScreen"]);

	// Set the amount of time the user has to complete the hole
	holeTimer = 80;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Loads either random level of certain size, or level by seed
void gameScene::LoadGame(string seed)
{
	// Only get seed from file if not given to us from load game screen
	if (seed == "seed") // it's the default value
	{
		// Some magic numbers in the following section; for milestone 2, will replace after
		// Insert start
		levelSeed.push_back(0);
		// Open seeds file 
		ifstream seedsFile("res12.csv");
		// find how many lines in seed file (hardcoded for now)
		int seedsCount = 341;
		// pick random number in that range
		default_random_engine rng(random_device{}());
		uniform_int_distribution<int> distribution(1, seedsCount);
		int choice = distribution(rng);
		// read that line
		string line;
		for (int l = 0; l < choice; ++l)
		{
			getline(seedsFile, line);
		} // last iteration will be on desired line, so line should be correct seed now
		// parse seed into array
		for (int c = 0; c < line.length(); ++c)
		{
			// Convert each character in string to int
			levelSeed.push_back(line[c] - 48); // Char encoding for digits; ASCII int value is - 0, or - 48
		}


	} // end if seed is default
	else // this has been given a seed value
	{
		// Prevent this level being saved again
		levelSaved = true;
		// Parse into ints as above
		for (int c = 0; c < seed.length(); ++c)
		{
			levelSeed.push_back(seed[c] - 48);
		}
	}

	// Start added first (this & next coords already set)
	StartTile start;
	algTiles.push_back(start);
	// Track currently looked at coords
	vec3 curCoords;
	// Update size tracker
	float size = start.size;
	// For each number in seed array
	for (auto &i : levelSeed)
	{
		// Update current coordinates (next coords of last thing in list) 
		curCoords = algTiles.back().GetNextCoords();

		switch (i)
		{
			// Straight_V
		case 1:
		{
			// Create tile
			StraightTile_V straightV;
			// Set its position
			straightV.SetCoords(curCoords);
			// Find next position - based on direction
			if (algTiles.back().outDir.going_down)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				straightV.SetNextCoords(nextPos);
				// Set dir
				straightV.outDir.going_down = true;
			}
			else if (algTiles.back().outDir.going_up)
			{
				// The position of next tile in list
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				straightV.SetNextCoords(nextPos);
				// Set dir
				straightV.outDir.going_up = true;
			}
			// Add tile to list, finish (break)
			algTiles.push_back(straightV);
			break;
		}
		// Straight_H
		case 2:
		{
			// Create tile
			StraightTile_H straightH;
			// Set its position
			straightH.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_right)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				straightH.SetNextCoords(nextPos);
				// Set dir
				straightH.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Position of next tile in list
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				straightH.SetNextCoords(nextPos);
				// Set dir
				straightH.outDir.going_left = true;
			}

			// Add to list
			algTiles.push_back(straightH);
			break;
		}
		// Corner_BL
		case 3:
		{
			// Create tile
			CornerTile_BL cornerBL;
			// Set pos
			cornerBL.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_down)
			{
				// Last tile was going down; next tile is going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerBL.SetNextCoords(nextPos);
				// Set dir
				cornerBL.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Last tile was going left; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBL.SetNextCoords(nextPos);
				// Set dir
				cornerBL.outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBL);
			break;
		}
		// Corner_BR
		case 4:
		{
			// Create tile
			CornerTile_BR cornerBR;
			// Set pos
			cornerBR.SetCoords(curCoords);
			// Find next position
			if (algTiles.back().outDir.going_down)
			{
				// Last tile was going down; next tile is going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerBR.SetNextCoords(nextPos);
				// Set dir
				cornerBR.outDir.going_left = true;
			}
			else if (algTiles.back().outDir.going_right)
			{
				// Last tile was going right; next tile is going up
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z - size);
				cornerBR.SetNextCoords(nextPos);
				// Set dir
				cornerBR.outDir.going_up = true;
			}
			// Add to list
			algTiles.push_back(cornerBR);
			break;
		}
		// Corner_TL
		case 5:
		{
			// Create tile
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(curCoords);
			// Find next pos
			if (algTiles.back().outDir.going_up)
			{
				// Last tile was going up; next going right
				vec3 nextPos = vec3(curCoords.x + size, curCoords.y, curCoords.z);
				cornerTL.SetNextCoords(nextPos);
				// Set dir
				cornerTL.outDir.going_right = true;
			}
			else if (algTiles.back().outDir.going_left)
			{
				// Last tile was going left; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTL.SetNextCoords(nextPos);
				// Set dir
				cornerTL.outDir.going_down = true;
			}
			// Add to list
			algTiles.push_back(cornerTL);
			break;
		}
		// Corner_TR
		case 6:
		{
			// Create tile
			CornerTile_TR cornerTR;
			// Set pos
			cornerTR.SetCoords(curCoords);
			// Find next pos
			if (algTiles.back().outDir.going_right)
			{
				// Last tile going right; next tile going down
				vec3 nextPos = vec3(curCoords.x, curCoords.y, curCoords.z + size);
				cornerTR.SetNextCoords(nextPos);
				// Set dir
				cornerTR.outDir.going_down = true;
			}
			else if (algTiles.back().outDir.going_up)
			{
				// Last tile going up; next tile going left
				vec3 nextPos = vec3(curCoords.x - size, curCoords.y, curCoords.z);
				cornerTR.SetNextCoords(nextPos);
				// Set dir
				cornerTR.outDir.going_left = true;
			}
			// Add to list
			algTiles.push_back(cornerTR);
			break;
		}
		// UpRampDown
		case 7:
		{
			// Create tile
			UpRampDown upRamp;
			upRamp.SetCoords(curCoords);
			// Find next pos (always know dir is down when 7 is placed)
			vec3 nextPos = vec3(curCoords.x, curCoords.y + 3.8, curCoords.z + size);
			upRamp.SetNextCoords(nextPos);
			upRamp.outDir.going_down = true;
			algTiles.push_back(upRamp);
			break;
		}
		// DownRampDown
		case 8:
		{
			// Create tile
			DownRampDown downRamp;
			downRamp.SetCoords(curCoords);
			// Find next pos (always know dir is up with tile 8)
			vec3 nextPos = vec3(curCoords.x, curCoords.y - 3.8, curCoords.z - size);
			downRamp.SetNextCoords(nextPos);
			downRamp.outDir.going_up = true;
			algTiles.push_back(downRamp);
			break;
		}

		// End tile
		case 9:
		{
			// Create end tile
			EndTile end;
			end.SetCoords(curCoords);
			end.outDir = algTiles.back().outDir;
			algTiles.push_back(end);
			break;
		}


		} // Switch end

	} // for loop end
}

// Populates scenery tiles
void gameScene::FillScenery()
{
	// Get boundary positions of level tiles in x and z
	float xMax = 0;
	float xMin = 0;
	float zMax = 0;
	float zMin = 0;
	for (auto &t : algTiles)
	{
		if (t.thisCoords.x > xMax)
			xMax = t.thisCoords.x;
		if (t.thisCoords.x < xMin)
			xMin = t.thisCoords.x;

		if (t.thisCoords.z > zMax)
			zMax = t.thisCoords.z;
		if (t.thisCoords.z < zMin)
			zMin = t.thisCoords.z;
	}
	// Add another tile's width to boundaries
	xMin -= 10; // To add another layer to the boundary, add 10 to each value
	zMin -= 20;
	xMax += 20;
	zMax += 10;

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
			for (int i = 0; i < algTiles.size(); ++i)
			{
				if (algTiles.at(i).thisCoords == thisPos)
				{
					// We have a match
					posTaken = true;
				}
			}
			// If able to create a scenery tile...
			if (!posTaken)
			{
				// Create straight tile
				//Mesh lava(Mesh::QUAD, "..\\NuttyPutters\\box.jpg", thisPos, 10.0f, 10.0f, 10.0f);
				Tile tile(Tile::SCENERY, thisPos, 0);
				//tile.transform.getRot().x = -0.785398;
				// Add to list of tiles to be rendered
				sceneryTiles.push_back(tile);


			}
		} // end x block
	} // end z block
}

// Creates tile classes to be drawn
void gameScene::SetupTilesToBeDrawn()
{
	int index = 0;

	// TILE CREATION
	for (auto &t : algTiles)
	{
		int obstacleID = 0;
		bool hasObstacle = false;

		// Ramp testing
		// Ramp up when dir is down
		if (t.id == 7)
		{
			hasObstacle = Tile::randomNumber(0, 1);
			if (hasObstacle)
			{
				obstacleID = Tile::randomNumber(1, 2);
				//save this tile position in algTiles
				obstacles.push_back(index);
				obstacles.push_back(obstacleID);
			}
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, obstacleID);
			// Rotate on x
			tile.transform.getRot().x = -0.349066;
			tile.transform.getPos().y += 1.8;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		// Ramp down when dir is up
		if (t.id == 8)
		{
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, obstacleID);
			// Rotate on x
			tile.transform.getRot().x = -0.349066;
			tile.transform.getPos().y -= 1.8;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		if (t.id == 0) // Start
		{
			// Create start tile
			Tile tile(Tile::START, t.thisCoords, obstacleID);
			// Start tile needs rotating 180 (should always face down)
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 1) // Straight V
		{
			hasObstacle = Tile::randomNumber(0, 1);
			if (hasObstacle)
			{
				obstacleID = Tile::randomNumber(1, 2);
				//save this tile position in algTiles
				obstacles.push_back(index);
				obstacles.push_back(obstacleID);
			}
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, 0);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 2) // Straight H
		{
			hasObstacle = Tile::randomNumber(0, 1);
			if (hasObstacle)
			{
				obstacleID = Tile::randomNumber(1, 2);
				//save this tile position in algTiles
				obstacles.push_back(index);
				obstacles.push_back(obstacleID);
			}
			// Create straight tile
			Tile tile(Tile::STRAIGHT, t.thisCoords, 0);
			// Straight needs rotating by 90, since it's vertical by default
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 3) // Corner BL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, obstacleID);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 4) // Corner BR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, obstacleID);
			// Corner needs rotating by 90
			tile.transform.getRot().y = 3.14159;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 5) // Corner TL
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, obstacleID);
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 6) // Corner TR
		{
			// Create corner tile
			Tile tile(Tile::CORNER, t.thisCoords, obstacleID);
			// Corner needs rotating by 90
			tile.transform.getRot().y = -1.5708;
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
		else if (t.id == 9) // end
		{
			// Create start tile
			Tile tile(Tile::END, t.thisCoords, obstacleID);
			// Consult direction to determine how much to rotate
			if (t.outDir.going_up)
			{
				tile.transform.getRot().y = 3.14159;
			}
			else if (t.outDir.going_down)
			{
				// No rotation needed
			}
			else if (t.outDir.going_left)
			{
				tile.transform.getRot().y = -1.5708;
			}
			else if (t.outDir.going_right)
			{
				tile.transform.getRot().y = 1.5708;
			}
			// Add to list of tiles to be rendered
			tiles.push_back(tile);
		}
	}

}

// Main game loop 
void gameScene::Loop(GLFWwindow* window)
{
	// Scene background
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
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

	// Exit
	if (glfwGetKey(window, GLFW_KEY_B))
	{
		// Access singleton instance to update it's sceneManager's state
		windowMgr::getInstance()->sceneManager.changeScene(0);
		cout << "Pressed B" << endl;
	}
	// Pause
	if (glfwGetKey(window, GLFW_KEY_P))
	{
		cout << "game paused" << endl;
		bool paused = true;
		while (paused)
		{
			// Need this or we get stuck in loop
			glfwPollEvents();
			// Save this level (move this code later to end of game, so we can save score with it)
			if (glfwGetKey(window, GLFW_KEY_S))
			{
				// Only save this level once
				if (!levelSaved)
				{
					// Open file to append level seed 
					ofstream saves("saves.csv", ofstream::app);
					// ID of each tile makes up seed
					for (auto &t : algTiles)
					{
						saves << t.id;
					}
					saves << endl;
					cout << "Level saved" << endl;
					levelSaved = true;

					// Also save image of level
					// Alt press below ensures only game window is captured
					//keybd_event(VK_MENU, 0, 0, 0); //Alt Press
					//keybd_event(VK_SNAPSHOT, 0, 0, 0); //PrntScrn Press
					//keybd_event(VK_SNAPSHOT, 0, KEYEVENTF_KEYUP, 0); //PrntScrn Release
					//keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); //Alt Release


					//// The above saves the game window capture to clipboard
					//// Retrieve image from clipboard, taken from https://www.experts-exchange.com/questions/24769725/Saving-a-clipboard-print-screen-image-to-disk-in-a-jpg-or-bmp-file-format.html
					//HWND hwnd = GetDesktopWindow(); 
					//if (!OpenClipboard(hwnd))
					//	cout << "Error with HWND" << endl;
					//OpenClipboard(NULL);
					//HBITMAP hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);
					//if (hBitmap == NULL)
					//	cout << "Error with clipboard bmp data" << endl;
					//CloseClipboard();
					//CImage image;
					//image.Attach(hBitmap);
					//// Build string to save with level seed name
					//string fileName;
					//for (auto &i : levelSeed)
					//{
					//	fileName += to_string(i);
					//}
					//fileName += ".bmp";
					//image.Save(fileName.c_str(), Gdiplus::ImageFormatBMP);
					//cout << "course image saved as " << fileName << endl;	
				}

			}

			// Unpause
			if (glfwGetKey(window, GLFW_KEY_U))
			{
				paused = false;
				break;
			}
		} // end while paused
		cout << "Unpaused" << endl;
	} // end pause

	// If button one is pressed change to free camera
	if (glfwGetKey(window, GLFW_KEY_1))
	{
		// Set camera version to free camera
		cout << "Free Camera selected" << endl;
		cameraType = 0;
		// Set the free cam position to where the chasecam stopped moving for debugging can me changed later
		windowMgr::getInstance()->freeCam->set_Posistion(windowMgr::getInstance()->chaseCam->get_Posistion());
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
		if (!golfBallMoving)
		{
			// controls in the chase camera 
			if (glfwGetKey(window, GLFW_KEY_D))
			{
				//function to rotate 
				windowMgr::getInstance()->chaseCam->yaw_it(camSpeed * dt * 0.5);
				// Decrease chase camera angle (out of 360 degrees)
				chaseCamAngle -= (camSpeed * dt * 0.5);
			}
			if (glfwGetKey(window, GLFW_KEY_A))
			{
				windowMgr::getInstance()->chaseCam->neg_yaw_it(camSpeed * dt * 0.5);
				// Increase chase camera angle (out of 360 degrees)
				chaseCamAngle += (camSpeed * dt * 0.5);
			}
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			windowMgr::getInstance()->chaseCam->neg_pitch_it(camSpeed * dt * 0.5, player1Transform.getPos(), windowMgr::getInstance()->chaseCam->get_Posistion(), windowMgr::getInstance()->chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			windowMgr::getInstance()->chaseCam->pitch_it(camSpeed * dt * 0.5, player1Transform.getPos(), windowMgr::getInstance()->chaseCam->get_Posistion(), windowMgr::getInstance()->chaseCam->get_pos_offset().y);
		}
		if (glfwGetKey(window, GLFW_KEY_Q))
		{
			//function to rotate 
			windowMgr::getInstance()->chaseCam->zoom_out(camSpeed * dt * 0.5);
		}
		if (glfwGetKey(window, GLFW_KEY_E))
		{
			windowMgr::getInstance()->chaseCam->zoom_in(camSpeed * dt * 0.5);
		}


		// If chase camera angle is greater than 360 reset to 0
		if (chaseCamAngle > 6.28319)
		{
			chaseCamAngle = 0.0;
		}
		// If chase camera angle is less than 0 then reset to 360
		else if (chaseCamAngle < 0)
		{
			chaseCamAngle = 6.28319;
		}
	}

	// PLAYER
	// Only allow ball movement if continue has been pressed
	if (continuePressed)
	{
		// If P is pressed 
		if (glfwGetKey(window, GLFW_KEY_SPACE))
		{
			if (!golfBallMoving)
			{
				// Start counter
				Pcounter += 0.5f;
				// Update the power bar based on the the Pcounter value 
				//powerBarTrans.getPos().x -= (Pcounter/5.0f) * powerBarMesh->getGeomPos().x;

			//	powerBarTrans.getPos().x += Pcounter /100.0f; // This value has has to be 20 times the dividing value as the scale extends both ways not just in a positive direction
				//powerBarTrans.getScale().x += Pcounter/5.0f; // Update the scale based on the Pcounter value

				//############################### CODE FOR POWER BAR WILL GO HERE ########################

				// SET DIRECTION BASED ON CHASE CAM ANGLE
				// If camera angle is between 0 and 90
				if (chaseCamAngle >= 0 && chaseCamAngle < 1.5708)
				{
					// Update the golf ball position and the arrow position
					// x = -sin(theta), z = cos(theta)
					// Separate below statement into direction = vec3(-sin, 0, cos) (normalise)		
					gbDirection = normalize(vec3(-sin(chaseCamAngle), 0.0, cos(chaseCamAngle)));
				}
				// If camera angle is between 90 and 180
				else if (chaseCamAngle > 1.5709 && chaseCamAngle < 3.14159)
				{
					// x = -cos(theta - 90), z = -sin(theta - 90)
					gbDirection = normalize(vec3(-cos(chaseCamAngle - 1.5708), 0.0, -sin(chaseCamAngle - 1.5708)));
				}
				// If camera angle is between 180 and 270
				else if (chaseCamAngle > 3.1416 && chaseCamAngle < 4.71239)
				{
					// x = sin(theta - 180), z = -cos(theta - 180)
					gbDirection = normalize(vec3(sin(chaseCamAngle - 3.1416), 0.0, -cos(chaseCamAngle - 3.1416)));
				}
				// If camera angle is anything else
				else if (chaseCamAngle > 4.724 && chaseCamAngle <= 6.28319)
				{
					// x = cos(theta - 270), z = sin(theta- 270)
					gbDirection = normalize(vec3(cos(chaseCamAngle - 4.71239), 0.0, sin(chaseCamAngle - 4.71239)));
				}
				pPressed = true;
			}
		}
	}
	// When P is realesed
	if ((glfwGetKey(window, GLFW_KEY_SPACE)) == false)
	{
		// Only work if p was just released
		if (pPressed)
		{
			golfBallMoving = true;
			// Force to apply is held in counter
			//Pcounter *= 3; // slightly magic number (Pc isn't enough on its own)
			// Apply to speed
			speed += Pcounter;
			//repeat until Pcounter is reset to 0
			while (Pcounter > 0.0)
			{
				//This just inverts the increasing in size and positions done before when P was pressed
			//	powerBarTrans.getPos().x += (Pcounter / 5.0f) * powerBarMesh->getGeomPos().x;
				//powerBarTrans.getPos().x -= Pcounter / 100.0f;
				//powerBarTrans.getScale().x -= Pcounter / 5.0f;
				//Decrease Pcounter until reaches 0
				Pcounter -= 0.5;
			}
			// Increment stroke counter by one
			strokeCounter += 1;

			// Switch statement which changes the stroke counter based on how many strokes the player has taken
			switch (strokeCounter)
			{
			case 0:	
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["zeroStrokeLbl"]);
				break;
			case 1:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["oneStrokeLbl"]);
				break;
			case 2:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["twoStrokeLbl"]);
				break;
			case 3:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["threeStrokeLbl"]);
				break;
			case 4:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["fourStrokeLbl"]);
				break;
			case 5:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["fiveStrokeLbl"]);
				break;
			case 6:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["sixStrokeLbl"]);
				break;
			case 7:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["sevenStrokeLbl"]);
				break;
			case 8:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["eightStrokeLbl"]);
				break;
			case 9:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["nineStrokeLbl"]);
				break;
			case 10:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["tenStrokeLbl"]);
				break;
			case 11:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["elevenStrokeLbl"]);
				break;
			case 12:
				windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["twelveStrokeLbl"]);
				break;
			case 13:
				// If more than 13 strokes have been taken then update necessary textures and set boolean to true
				windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["outOfLbl"]);
				windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["outOfStrokesLbl"]);
				windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["saveGameLbl"]);
				windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
				isUserOutOfStrokes = true;
				break;
			}

			// Flip
			pPressed = false;
		}
	} // End if (p is released)

	  //This function resets the scene to an empty screen
	if (glfwGetKey(window, GLFW_KEY_C))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
		glLoadIdentity();
		glfwSwapBuffers(window);

		windowMgr::getInstance()->sceneManager.changeScene(1);
	}

}

// Update positions
void gameScene::Update(GLFWwindow* window)
{
	// Calculate dt
	lastFrame = thisFrame;
	thisFrame = glfwGetTime();
	dt = (float)(thisFrame - lastFrame);
	if (dt > 0.03)
		dt = 0.016;

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

	// The getRot of golf ball - will this be troublesome? Don't want the camera
	// to rotate along with the ball! 
	windowMgr::getInstance()->chaseCam->move(player1Transform.getPos(), player1Transform.getRot());
	windowMgr::getInstance()->chaseCam->update(0.00001);

	// Update target camera
	windowMgr::getInstance()->HUDtargetCam->update(0.00001);

	// PLAYER UPDATE
	// Velocity is direction by speed by delta time
	gbVelocity = (gbDirection * speed);
	// Apply friction when moving
	if (speed > 0 + 0.5) // this magic number is epsilon
	{
		speed -= speed * 0.03; // this magic number is friction
		 // Rotation is cross product of direction and up
		vec3 rot = normalize(cross(normalize(gbDirection), vec3(0.0f, 1.0f, 0.0f)));

		rot *=  speed *  dt;
		player1Transform.getRot() += -rot;

	}
	// Prevent it moving forever
	else
	{
		speed = 0;
		golfBallMoving = false;
	}
	// Lock to frame rate
	gbVelocity *= dt;

	// Update positions of ball and arrow
	player1Transform.getPos() += gbVelocity;
	arrowTransform.getPos() += gbVelocity;	

	// TIMER RELATED INFORMATION
	// If the time been in scene is equal to zero then
	if (timeBeenInScene == 0)
	{
		// Get the amount of time been in scene
		timeBeenInScene = glfwGetTime();
	}
	// Increment time Counter - used for splash screen
	timeCounter++;

	// If the continue button is pressed 
	if (continuePressed)
	{
		// If the time taken to reach this method is zero then
		if (timeToThisMethod == 0)
		{
			// Get the time to this method
			timeToThisMethod = glfwGetTime();
		}
		// Get the time since continue was pressed by taking away the time to this method 
		timeSinceContinueWasPressed = glfwGetTime() - timeToThisMethod;
		// Get the time remaining in seconds by taking away the time the user has to complete the hole 
		timeRemainingInSeconds = holeTimer - timeSinceContinueWasPressed;
		// Get the time in minutes, tenths and seconds - 0M:TS
		timeRemainingInMinutes = timeRemainingInSeconds / 60;
		timeRemainingInTenths = (timeRemainingInSeconds - (timeRemainingInMinutes * 60)) / 10;
		timeRemainingInSeconds = timeRemainingInSeconds - (timeRemainingInMinutes * 60) - (timeRemainingInTenths * 10);
		//cout << "Mins and secs: " << timeRemainingInMinutes << " " << timeRemainingInTenths << " " << timeRemainingInSeconds << endl;

		// Switch statements which update the minutes, tenths and seconds meshes
		switch (timeRemainingInMinutes)
		{
		case 0:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		case 1:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["oneLbl"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["threeLbl"]);
			break;
		case 4:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["fourLbl"]);
			break;
		case 5:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["fiveLbl"]);
			break;
		case 6:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["sixLbl"]);
			break;
		case 7:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["sevenLbl"]);
			break;
		case 8:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["eightLbl"]);
			break;
		case 9:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["nineLbl"]);
			break;
		default:
			windowMgr::getInstance()->meshes.at(6)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		}

		switch (timeRemainingInTenths)
		{
		case 0:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		case 1:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["oneLbl"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["threeLbl"]);
			break;
		case 4:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["fourLbl"]);
			break;
		case 5:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["fiveLbl"]);
			break;
		case 6:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["sixLbl"]);
			break;
		case 7:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["sevenLbl"]);
			break;
		case 8:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["eightLbl"]);
			break;
		case 9:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["nineLbl"]);
			break;
		default:
			windowMgr::getInstance()->meshes.at(7)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		}

		switch (timeRemainingInSeconds)
		{
		case 0:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		case 1:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["oneLbl"]);
			break;
		case 2:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["twoLbl"]);
			break;
		case 3:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["threeLbl"]);
			break;
		case 4:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["fourLbl"]);
			break;
		case 5:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["fiveLbl"]);
			break;
		case 6:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["sixLbl"]);
			break;
		case 7:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["sevenLbl"]);
			break;
		case 8:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["eightLbl"]);
			break;
		case 9:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["nineLbl"]);
			break;
		default:
			windowMgr::getInstance()->meshes.at(8)->SetTexture(windowMgr::getInstance()->textures["zeroLbl"]);
			break;
		}
		// If user has no time remaining then
		if (timeRemainingInSeconds < 0)
		{
			// Update necessary textures
			windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["outOfLbl"]);
			windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["outOfTimeLbl"]);
			windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["saveGameLbl"]);
			windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
			// Update boolean - used for rendering
			isUserOutOfTime = true;
		}
	}
}

// Tracks current tile player is on (TODO improve performance)
// Calls collision checking code of tile player is on
void gameScene::Collisions()
{

	int tileTracker = 0;
	// Check which tile player is on (do this every n frames, not each tick)
	for (auto &t : algTiles)
	{
		// if (t.isPlayerOnTile)
		// currentTile = tileTracker
		// if not, tileTracker++
		if (t.isPlayerOnTile(player1Transform.getPos()))
		{
			currentTile = tileTracker;
		}
		else
			tileTracker++;
	}
	//cout << "Current tile: " << algTiles.at(currentTile).id << "at (" << algTiles.at(currentTile).thisCoords.x << ", " << algTiles.at(currentTile).thisCoords.x << ") " << " : " << currentTile << "pos: " << player1Transform.getPos().x << ", " << player1Transform.getPos().y << ", " << player1Transform.getPos().z  << endl;

	// Switch on the currentTile 
	switch (algTiles.at(currentTile).id)
	{

			// On start tile
		case 0:
		{
			// Need to do this to access start only methods (which includes col check)
			//onRamp = false;
			StartTile start;
			gbDirection = start.CheckCollisions(player1Transform.getPos(), gbDirection);
			break;
		}
		// On straight V tile
		case 1:
		{
			//onRamp = false;
			StraightTile_V straightV;
			straightV.SetCoords(algTiles.at(currentTile).GetThisCoords());
			// Ensure don't go through floor
			player1Transform.setPos(straightV.SetPlayerHeight(player1Transform.getPos()));
			gbDirection = straightV.CheckCollisions(player1Transform.getPos(), gbDirection);

			for (unsigned int i = 0; i < obstacles.size(); i = i + 2)

			{
				switch (obstacles.at(i + 1))
				{
					switch (obstacles.at(i + 1))
					{
					case 1:

						break;
					case 2:
						gbDirection = CheckCollisionsObstacle1(straightV.thisCoords, player1Transform.getPos(),
							gbDirection, straightV.displace, straightV.radius);
						break;
					default:
						break;
					}
				}
			}
			break;
		}
		
		// On straight H tile
		case 2:
		{
			//onRamp = false;
			StraightTile_H straightH;
			straightH.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = straightH.CheckCollisions(player1Transform.getPos(), gbDirection);
			for (unsigned int i = 0; i < obstacles.size(); i = i + 2)
			{

				//onRamp = false;
				StraightTile_H straightH;
				straightH.SetCoords(algTiles.at(currentTile).GetThisCoords());
				gbDirection = straightH.CheckCollisions(player1Transform.getPos(), gbDirection);
				for (unsigned int i = 0; i < obstacles.size(); i = i + 2)

				{
					switch (obstacles.at(i + 1))
					{
						switch (obstacles.at(i + 1))
						{
						case 1:

							break;
						case 2:
							gbDirection = CheckCollisionsObstacle1(straightH.thisCoords, player1Transform.getPos(),
								gbDirection, straightH.displace, straightH.radius);
							break;
						default:
							break;
						}
					}
				}
			}
			break; 
		}
			// On corner_BL tile
		case 3:
		{
			//onRamp = false;
			CornerTile_BL cornerBL;
			cornerBL.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerBL.CheckCollisions(player1Transform.getPos(), gbDirection);
			break;
		}
		// On corner_BR tile
		case 4:
		{
			//onRamp = false;
			CornerTile_BR cornerBR;
			cornerBR.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerBR.CheckCollisions(player1Transform.getPos(), gbDirection);
			break;
		}
		// On corner_TL tile
		case 5:
		{
			//onRamp = false;
			CornerTile_TL cornerTL;
			cornerTL.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerTL.CheckCollisions(player1Transform.getPos(), gbDirection);
			break;
		}
		// On corner_TR tile
		case 6:
		{
			//onRamp = false;
			CornerTile_TR cornerTR;
			cornerTR.SetCoords(algTiles.at(currentTile).GetThisCoords());
			gbDirection = cornerTR.CheckCollisions(player1Transform.getPos(), gbDirection);
			break;
		}
		// Up ramp tile
		case 7:
		{
			UpRampDown ramp;
			ramp.SetCoords(algTiles.at(currentTile).GetThisCoords());
			ramp.thisCoords.y += 1.8;
			// Set player height
			player1Transform.setPos(ramp.SetPlayerHeight(player1Transform.getPos()));
			//onRamp = true;
			break;
		}
		// End tile
		case 9:
		{
			//onRamp = false;
			EndTile end;
			end.SetCoords(algTiles.at(currentTile).GetThisCoords());
			end.outDir = algTiles.at(currentTile).outDir;
			gbDirection = end.CheckCollisions(player1Transform.getPos(), gbDirection, speed);

			// If user hasnt completed hole then - get
			if (!hasUserCompletedHole)
			{
				// If ball in hole is equal to true - function to courseGenTiles
				if(end.getBallInHole());
				{
					// Update boolean to user having completed the hole
					hasUserCompletedHole = true;
					// Update necessary textures
					windowMgr::getInstance()->meshes.at(10)->SetTexture(windowMgr::getInstance()->textures["holeLbl"]);
					windowMgr::getInstance()->meshes.at(11)->SetTexture(windowMgr::getInstance()->textures["completeLbl"]);
					windowMgr::getInstance()->meshes.at(12)->SetTexture(windowMgr::getInstance()->textures["saveGameLbl"]);
					windowMgr::getInstance()->meshes.at(13)->SetTexture(windowMgr::getInstance()->textures["mainMenuBtnUnselected"]);
				}
			}

			break;
		}
	}
}

vec3 gameScene::CheckCollisionsObstacle1(vec3 coords, vec3 playerPos, vec3 dir, float displace, float radius)
{
	// M - here, you're checking for player pos within an x range
	// Check x axis - left side of cube corner boundary
	if (playerPos.x > coords.x - (1 + radius) && playerPos.x < coords.x + (1 + radius))
	{
		// M - This section should be removed, only one deflection (-dir) should take place for each collision
		// the above if statement only checks what x range the ball is in - not if it should actually collide
		// Hit going right, reflect on x
		dir.x = -dir.x;
		// Move away from boundary so as not to retrigger this
		playerPos.x -= displace;



		//lower boundary of cube
		// M - change this to read 'if player.z < coords.z + (1 + radius) && dir of travel is towards this boundary
		//   dir will be up when gbDir.z is negative
		if (playerPos.z > coords.z - (1 + radius) && playerPos.z < coords.z + (1 + radius))
		{
			// Hit going right, reflect on x
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}


		// M -Add another if statement as above, this time checking for upper boundary of cube
		// player.z > coords.z - (1 + radius) && dir.z is positive

	}

	// M - Repeat above for the following z block (change x with z)
	if (playerPos.z > coords.z - (1 + radius) && playerPos.z < coords.z + (1 + radius))
	{
		// Hit going right, reflect on x
		dir.x = -dir.x;
		// Move away from boundary so as not to retrigger this
		playerPos.x -= displace;

		if (playerPos.x > coords.x - (1 + radius) && playerPos.x < coords.x + (1 + radius))
		{
			// Hit going right, reflect on x
			dir.z = -dir.z;
			// Move away from boundary so as not to retrigger this
			playerPos.z -= displace;
		}
	}
	return dir;
}

// Draw stuff
void gameScene::Render(GLFWwindow* window)
{
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
		mvp = windowMgr::getInstance()->chaseCam->get_Projection() * windowMgr::getInstance()->chaseCam->get_View();
	}
	// If camera type is target camera - used for HUD elements - then

	glm::mat4 hudVP = windowMgr::getInstance()->HUDtargetCam->get_Projection() * windowMgr::getInstance()->HUDtargetCam->get_View();

	// HUD RENDERING STARTING - DONT NOT ENTER ANY OTHER CODE NOT RELATED TO HUD BETWEEN THIS AND THE END HUD COMMENT
	// Set depth range to near to allow for HUD elements to be rendered and drawn
	glDepthRange(0, 0.01);

	// If timeCounter - which is a variable that increases as of when the scene has loaded is less than the time been in scene + a value that can be changed then
	if (timeCounter < timeBeenInScene + 300)
	{
		// Display splash screen
		windowMgr::getInstance()->meshes.at(19)->thisTexture.Bind(0);
		windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
		windowMgr::getInstance()->meshes.at(19)->Draw();
	}

	// If user has completed the hole or if the continue button hasnt been pressed of if the user has run out of time or if the user has run out of strokes
	if (hasUserCompletedHole || !continuePressed || isUserOutOfTime || isUserOutOfStrokes)
	{
		// For loop which goes through all the information elements and binds, updates and draws them.
		for (int i = 10; i < 14; i++)
		{
			windowMgr::getInstance()->meshes.at(i)->thisTexture.Bind(0);
			windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, hudVP);
			windowMgr::getInstance()->meshes.at(i)->Draw();
		}
	}
	// Else then display remaining gameplay HUDs
	else
	{
		// For loop which goes through all 10 HUD elements and binds, updates anbd draws the meshes.
		for (int i = 0; i < 10; i++)
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
	//sky->thisTexture->Bind(0);
	windowMgr::getInstance()->skyboxShader->Update(windowMgr::getInstance()->texShaderTransform, mvp);
	sky->Draw();
	// Bind texture shader
	windowMgr::getInstance()->textureShader->Bind();

	// DRAW all level tiles
	for (auto &t : tiles)
	{
		t.drawTile(windowMgr::getInstance()->textureShader, mvp);
	}
	// DRAW all scenery tiles
	for (auto &t : sceneryTiles)
	{
		t.drawTile(windowMgr::getInstance()->textureShader, mvp);
	}

	// Render player 1
	windowMgr::getInstance()->textures["playerRedTexture"]->Bind(0);
	windowMgr::getInstance()->textureShader->Update(player1Transform, mvp);
	windowMgr::getInstance()->player1Mesh->Draw();
	// Render player 1 arrow
	windowMgr::getInstance()->arrowMesh->thisTexture.Bind(0);
	windowMgr::getInstance()->textureShader->Update(arrowTransform, mvp);
	// Rotate the arrow on the Y axis by - camera angle minus 90 degrees
	arrowTransform.setRot(glm::vec3(0, -chaseCamAngle - 1.5708, 0));

	// Arrow
	//arrowTexture->Bind(0);
	//textureShader->Update(arrowTransform, mvp);
	//arrowTransform.setRot(glm::vec3(0, -chaseCamAngle - 1.5708, 0));

	// If ball is not moving draw arrow (ie dont draw arrow when ball moving as not needed)
	if (!golfBallMoving)
	{
		// Draw the arrow
		windowMgr::getInstance()->arrowMesh->Draw();
	}

	// Update texture shader
	windowMgr::getInstance()->textureShader->Update(windowMgr::getInstance()->texShaderTransform, (windowMgr::getInstance()->freeCam->get_Projection() * windowMgr::getInstance()->freeCam->get_View()));

	// Fully reset depth range for next frame - REQUIRED
	glDepthRange(0, 1.0);

	glfwSwapBuffers(window);
	glfwPollEvents();
}