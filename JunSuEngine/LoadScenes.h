#pragma once
#include "..\Engine_SOURCE\jsSceneManager.h"
#include "jsTitleScene.h"
#include "jsPlayScene.h"
#include "jsEndingScene.h"
#include "jsTutorialScene.h"
#include "jsVellieScene.h"
#include "jsBossScene.h"
#include "jsDungeonScene.h"
#include "jsHouseScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\JunSuEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\JunSuEngine.lib")
#endif

namespace js
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<TutorialScene>(L"TutorialScene");
		SceneManager::CreateScene<VellieScene>(L"VellieScene");
		SceneManager::CreateScene<DungeonScene>(L"DungeonScene");
		SceneManager::CreateScene<BossScene>(L"BossScene");
		SceneManager::CreateScene<HouseScene>(L"HouseScene");
		SceneManager::CreateScene<PlayScene>(L"PlayScene");
		SceneManager::CreateScene<EndingScene>(L"EndingScene");
 
		SceneManager::LoadScene(L"PlayScene");
	}
}