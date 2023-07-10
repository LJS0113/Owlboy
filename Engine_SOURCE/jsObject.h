#pragma once
#include "jsLayer.h"
#include "jsGameObject.h"
#include "jsScene.h"
#include "jsSceneManager.h"
#include "jsTransform.h"

namespace js::object
{
	template <typename T>
	static __forceinline T* Instantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* Instantiate(Vector3 pos, Vector3 rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		Transform* tr = gameObj->GetComponent<Transform>();
		tr->SetPosition(pos);
		tr->SetRotation(rotate);
		tr->SetScale(scale);

		Scene* scene = SceneManager::GetActiveScene();
		scene->AddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void Destroy(GameObject* gameObj)
	{
		gameObj->SetState(js::GameObject::eState::Dead);
	}


}