#include "jsDungeonScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsTransform.h"
#include "jsCameraScript.h"
#include "jsResources.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsTitleScene.h" 
#include "jsObject.h"
#include "jsPlayerScript.h"
#include "jsPlayer.h"

namespace js
{
	DungeonScene::DungeonScene()
	{
	}

	DungeonScene::~DungeonScene()
	{
	}

	void DungeonScene::Initialize()
	{

		Player* player = object::Instantiate<Player>(Vector3(3.0f, -1.0f, 1.0f), eLayerType::Player);
		player->SetName(L"Otus");
		Transform* tr = player->GetComponent<Transform>();
		Collider2D* cd = player->AddComponent<Collider2D>();
		player->AddComponent<PlayerScript>();
		player->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		player->AddComponent<CameraScript>();


		{
			// 던전 확대버전
			GameObject* player = object::Instantiate<GameObject>(Vector3(-10.0f, 0.0f, 3.0f), eLayerType::Player);
			player->SetName(L"DungeonStage");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DungeonMaterial"));
			player->GetComponent<Transform>()->SetScale(Vector3(30.0f, 5.0f, 1.0f));
		}


		// 던전 원본
		//GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 3.0f), eLayerType::Player);
		//player->SetName(L"DungeonStage");
		//MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"DungeonMaterial"));
		//player->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));

		//player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::Player);
		//mr = player->AddComponent<MeshRenderer>();
		//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr->SetMaterial(Resources::Find<Material>(L"VellieSkyMaterial"));
		//player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		//player->AddComponent<CameraScript>();

		{
			// coin
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 1.6f, 1.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CoinMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.0f));
		}
		{
			// otus hp bar
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.0f, 2.0f, 1.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.2f, 1.0f));
		}
		{
			// otus hp bar Frame
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 2.0f, 1.1f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpIconframeMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.1f));
		}
		{
			// otus hp bar Icon
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 2.0f, 1.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpIconMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.0f));
		}

		Camera* cameraComp = nullptr;
		{
			// Main Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
		}

	}

	void DungeonScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"BossScene");
		}
		Scene::Update();
	}

	void DungeonScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void DungeonScene::Render()
	{
		Scene::Render();
	}

	void DungeonScene::OnEnter()
	{
	}

	void DungeonScene::OnExit()
	{
	}

}