#include "jsPlayScene.h"
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
	PlayScene::PlayScene()
	{
	}
	PlayScene::~PlayScene()
	{
	}
	void PlayScene::Initialize()
	{
		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Zelda");
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
		//	//player->AddComponent<CameraScript>();

		//	//GameObject* player2 = new GameObject();
		//	//player2->SetName(L"ZeldaChild");
		//	//AddGameObject(eLayerType::Player, player2);
		//	//MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
		//	//mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	//mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//	//player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));

		//	//player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		//	//const float pi = 3.141592f;
		//	//float degree = pi / 2.0f;

		//	//player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
		//	//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));
		//}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::Player, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0f));
		//	//player->AddComponent<CameraScript>();
		//}

		//{
		//	GameObject* player = new GameObject();
		//	player->SetName(L"Smile");
		//	AddGameObject(eLayerType::UI, player);
		//	MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
		//	player->GetComponent<Transform>()->SetPosition(Vector3(0.2f, 0.0f, 0.0f));
		//	//player->AddComponent<CameraScript>();
		//}
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
		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();
		//Transform* tr = player->GetComponent<Transform>();
		//tr->SetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"EndingScene");
		}
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
		//
		//Vector3 pos(600, 450, 0.0f);
		//Vector3 pos2(600, 450, 1000.0f);
		//Viewport viewport;
		//viewport.width = 1600.0f;
		//viewport.height = 900.0f;
		//viewport.x = 0;
		//viewport.y = 0;
		//viewport.minDepth = 0.0f;
		//viewport.maxDepth = 1.0f;

		//pos = viewport.Unproject(pos, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
		//pos2 = viewport.Unproject(pos2, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		Scene::LateUpdate();
	}
	void PlayScene::Render()
	{
		Scene::Render();
	}
	void PlayScene::OnEnter()
	{
	}
	void PlayScene::OnExit()
	{
	}
}