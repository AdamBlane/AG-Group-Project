#include "PauseScreen.h"
#include "windowMgr.h"



// Sets up basic HUD layout for 1 player game
void PauseScreen::Init()
{
	windowMgr::getInstance()->meshes.at(0)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(0)->SetPos(vec3(2.0f, -1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(1)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(1)->SetPos(vec3(0.0f, 1.5f, 0.0f));
	windowMgr::getInstance()->meshes.at(2)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(2)->SetPos(vec3(0.0f, 0.9f, 0.0f));
	windowMgr::getInstance()->meshes.at(4)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(4)->SetPos(vec3(0.0f, 0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(3)->SetScale(1.8f, 0.6f);
	windowMgr::getInstance()->meshes.at(3)->SetPos(vec3(0.0f, -0.3f, 0.0f));
	windowMgr::getInstance()->meshes.at(0)->SetTexture(windowMgr::getInstance()->textures["smallwindowBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(1)->SetTexture(windowMgr::getInstance()->textures["fullscreenBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(2)->SetTexture(windowMgr::getInstance()->textures["windowBtnUnselected"]);
	windowMgr::getInstance()->meshes.at(3)->SetTexture(windowMgr::getInstance()->textures["halfBtnUnselected"]);

}


