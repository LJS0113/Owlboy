#pragma once
#include "jsEntity.h"
#include "jsLayer.h"

namespace js
{
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void AddGameObject(eLayerType type, GameObject* gameObj);

	private:
		std::vector<Layer> mLayers;
	};

}