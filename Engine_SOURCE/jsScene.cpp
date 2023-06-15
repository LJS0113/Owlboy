#include "jsScene.h"


namespace js
{
	Scene::Scene()
	{
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// ���⼭ �ʱ� ���� �ʵ����͸� ����������Ѵ�.
	}
	void Scene::Update()
	{
		for (Layer* layer : mLayers)
		{
			layer->Update();
		}
	}
	void Scene::LateUpdate()
	{
		for (Layer* layer : mLayers)
		{
			layer->Update();
		}
	}
	void Scene::Render()
	{
		for (Layer* layer : mLayers)
		{
			layer->Render();
		}
	}
}