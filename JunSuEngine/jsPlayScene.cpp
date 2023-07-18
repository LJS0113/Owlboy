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
#include "jsPlayerScript.h"
#include "jsMonsterScript.h"
#include "jsCollisionManager.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);

		GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
		player->SetName(L"Zelda");
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		//player->AddComponent<CameraScript>();
		player->GetComponent<Transform>()->SetPosition(Vector3(-2.0f, 0.0f, 1.0001f));
		player->AddComponent<PlayerScript>();
		Collider2D* cd = player->AddComponent<Collider2D>();
		cd->SetSize(Vector2(1.2f, 1.2f));

			

			//const float pi = 3.141592f;
			//float degree = pi / 2.0f;

			//player->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			//player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree));


		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.0f), eLayerType::Monster);
			player->SetName(L"Smile");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial02"));
			Collider2D* cd = player->AddComponent<Collider2D>();
			cd->SetSize(Vector2(1.0f, 1.0f));
			player->AddComponent<MonsterScript>();
			//player->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}

		Camera* cameraComp = nullptr;
		{
			// Main Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
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