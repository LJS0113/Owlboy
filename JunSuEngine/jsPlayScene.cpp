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
#include "jsObject.h"
#include "jsRenderer.h"
#include "jsCollider2D.h"

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
		GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
		player->SetName(L"Zelda");
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//player->AddComponent<CameraScript>();
		player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		player->AddComponent<Collider2D>();
		//Collider2D* cd = player->AddComponent<Collider2D>();
		//cd->SetCenter(Vector2(0.5f, 0.0f));

		//GameObject* player2 = new GameObject();
		//player2->SetName(L"ZeldaChild");
		//AddGameObject(eLayerType::Player, player2);
		//MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
		//mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));

		//player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>());

		//const float pi = 3.141592f;
		//float degree = pi / 2.0f;

		//player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
		//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));


		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0f), eLayerType::Player);
			player->SetName(L"Smile");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			//player->AddComponent<CameraScript>();
		}
		Camera* cameraComp = nullptr;
		{
			// Main Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			//camera->AddComponent<CameraScript>();
		}

		{
			//// Grid 
			//GameObject* grid = object::Instantiate<GameObject>(eLayerType::Grid);
			//player->SetName(L"Grid");
			//MeshRenderer* mr = grid->AddComponent<MeshRenderer>();
			//mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			//mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
			//GridScript* gridSc = grid->AddComponent<GridScript>();
			//gridSc->SetCamera(cameraComp);
		}
		
	}
	void PlayScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
		}
		Scene::Update();
	}
	void PlayScene::LateUpdate()
	{
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