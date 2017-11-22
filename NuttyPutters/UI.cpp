#include "UI.h"
#include "windowMgr.h"

void UI::Init()
{
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
}