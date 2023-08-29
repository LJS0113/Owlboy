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
#include "jsObject.h"
#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsMaskedTortoiseScript.h"
#include "jsMonster.h"
#include "jsGround.h"
#include "jsRigidBody.h"

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
		Player* player = object::Instantiate<Player>(Vector3(-3.0f, -1.5f, 1.0f), eLayerType::Player);
		player->SetName(L"Otus");
		Transform* tr = player->GetComponent<Transform>();
		Collider2D* cd = player->AddComponent<Collider2D>();
		Rigidbody* playerRb = player->AddComponent<Rigidbody>();
		player->AddComponent<PlayerScript>();
		player->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		//player->AddComponent<CameraScript>();

		{
			Monster* monster = object::Instantiate<Monster>(Vector3(0.0f, -1.2f, 1.0f), eLayerType::Monster);
			monster->SetName(L"MaskedTortoise");
			Transform* tr = monster->GetComponent<Transform>();
			Collider2D* cd = monster->AddComponent<Collider2D>();
			monster->AddComponent<MaskedTortoiseScript>();
			monster->GetComponent<MaskedTortoiseScript>()->Initialize();
			tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}
		{
			// Boss Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(0.0f, -2.0f, 2.0f), eLayerType::Ground);
			ground->SetName(L"BossGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(10.0f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BG);
			player->SetName(L"BossStage");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BossStageMaterial"));
			player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		}

		{
			// coin
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 1.6f, -5.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CoinMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.0f));
		}
		{
			// otus hp bar
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.0f, 2.0f, -5.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.2f, 1.0f));
		}
		{
			// otus hp bar Frame
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 2.0f, -5.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpIconframeMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.1f));
		}
		{
			// otus hp bar Icon
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(-3.6f, 2.0f, -5.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpIconMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(0.2f, 0.2f, 1.0f));
		}
		{
			// Boss hp bar
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(0.0f, -2.05f, -5.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BossHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(3.0f, 0.3f, 1.0f));
		}
		{
			// Boss hp bar
			GameObject* hpBar = object::Instantiate<GameObject>(Vector3(0.0f, -2.035f, -4.0f), eLayerType::UI);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BossHpBarOnMaterial"));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(2.4f, 0.22f, 1.0f));
		}
		Camera* cameraComp = nullptr;
		{
			// Main Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			renderer::mainCamera = cameraComp;
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::Monster, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
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

