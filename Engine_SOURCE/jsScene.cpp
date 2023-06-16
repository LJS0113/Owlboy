#include "jsScene.h"


namespace js
{
	Scene::Scene()
	{
		mLayers.resize((int)js::enums::eLayerType::End);
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
	}
	void Scene::Update()
	{
		for (Layer& layer : mLayers)
		{
			layer.Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer& layer : mLayers)
		{
			layer.LateUpdate();
		}
	}
	void Scene::Render()
	{
		for (Layer& layer : mLayers)
		{
			layer.Render();
		}
	}
	void Scene::AddGameObject(eLayerType type, GameObject* gameObj)
	{
		mLayers[(int)type].AddGameObject(gameObj);
	}
}