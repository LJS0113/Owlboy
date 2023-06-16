#include "jsSceneManager.h"
#include "jsPlayScene.h"

namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;
	void SceneManager::Initialize()
	{
		mActiveScene = new PlayScene();
		mActiveScene->Initialize();
	}

	void SceneManager::Update()
	{
		mActiveScene->Update();
	}

	void SceneManager::LateUpdate()
	{
		mActiveScene->LateUpdate();
	}

	void SceneManager::Render()
	{
		mActiveScene->Render();
	}

}