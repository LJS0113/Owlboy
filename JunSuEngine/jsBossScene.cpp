#include "jsBossScene.h"
#include "jsTransform.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsMesh.h"
#include "jsCameraScript.h"
#include "jsCamera.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsEndingScene.h"
#include "jsGridScript.h"

namespace js
{
	BossScene::BossScene()
	{
	}
	BossScene::~BossScene()
	{
	}
	void BossScene::Initialize()
	{
		GameObject* player = new GameObject();
		player->SetName(L"BossStage");
		AddGameObject(eLayerType::BG, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"BossStageMaterial"));
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
		player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));

		{
			// otus hp bar
			GameObject* hpBar = new GameObject();
			AddGameObject(eLayerType::UI, hpBar);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 2.0f, 1.0f));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.2f, 1.0f));
		}
		{
			// Boss hp bar
			GameObject* hpBar = new GameObject();
			AddGameObject(eLayerType::UI, hpBar);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BossHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -2.05f, 1.1f));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(3.0f, 0.3f, 1.0f));
		}
		{
			// Boss hp bar
			GameObject* hpBar = new GameObject();
			AddGameObject(eLayerType::UI, hpBar);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BossHpBarOnMaterial"));
			hpBar->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -2.035f, 1.0f));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(2.4f, 0.22f, 1.0f));
		}
		Camera* cameraComp = nullptr;
		{
			// Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		{
			// UI Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			//camera->AddComponent<CameraScript>();
		}

		{
			GameObject* grid = new GameObject();
			player->SetName(L"Grid");
			AddGameObject(eLayerType::Grid, grid);
			MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			GridScript* gridSc = grid->AddComponent<GridScript>();
			gridSc->SetCamera(cameraComp);
		}
	}
	void BossScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"EndingScene");
		}
		Scene::Update();
	}
	void BossScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void BossScene::Render()
	{
		Scene::Render();
	}
	void BossScene::OnEnter()
	{
	}
	void BossScene::OnExit()
	{
	}
}

