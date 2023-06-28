#include "jsSceneManager.h"
#include "jsPlayScene.h"
#include "jsTitleScene.h"
#include "jsEndingScene.h"


namespace js
{
	Scene* SceneManager::mActiveScene = nullptr;
	std::map<std::wstring, Scene*> SceneManager::mScenes;

	void SceneManager::Initialize()
	{
		Scene* scene = new TitleScene();
		mScenes.insert(std::make_pair(L"TitleScene", scene));

		scene = new PlayScene();
		mScenes.insert(std::make_pair(L"PlayScene", scene));

		scene = new EndingScene();
		mScenes.insert(std::make_pair(L"EndingScene", scene));

		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(L"TitleScene");

		mActiveScene = iter->second;
		mActiveScene->OnEnter();
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

	void SceneManager::Release()
	{
		for (auto iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	Scene* SceneManager::LoadScene(std::wstring name)
	{
		std::map<std::wstring, Scene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		mActiveScene->OnExit();
		mActiveScene = iter->second;
		mActiveScene->OnEnter();
		mActiveScene->Initialize();

		return iter->second;
	}

}