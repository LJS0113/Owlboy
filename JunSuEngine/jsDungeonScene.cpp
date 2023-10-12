#include "jsDungeonScene.h"
#include "jsRenderer.h"
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
#include "jsGround.h"
#include "jsGroundScript.h"
#include "jsRigidBody.h"
#include "jsGeddy.h"
#include "jsGeddyScript.h"

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

		gPlayer = object::Instantiate<Player>(Vector3(0.9f, -1.0f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		Transform* tr = gPlayer->GetComponent<Transform>();
		Collider2D* cd = gPlayer->AddComponent<Collider2D>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		//gPlayer->AddComponent<CameraScript>();
		Rigidbody* rb = gPlayer->AddComponent<Rigidbody>();

		{
			// 던전 확대버전
			GameObject* player = object::Instantiate<GameObject>(Vector3(-10.0f, 0.0f, 3.0f), eLayerType::Player);
			player->SetName(L"DungeonStage");
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"DungeonMaterial"));
			player->GetComponent<Transform>()->SetScale(Vector3(30.0f, 30.0f, 1.0f));
		}
		{
			// Dungeon Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(-10.0f, -1.8f, 2.0f), eLayerType::Ground);
			ground->SetName(L"DungeonGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(25.0f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
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
			renderer::mainCamera = cameraComp;
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
		Transform* otusTr = gPlayer->GetComponent<Transform>();
		Vector3 otusPos = otusTr->GetPosition();
		bool summon = gPlayer->GetComponent<PlayerScript>()->GetSummon();
		if (Input::GetKeyState(eKeyCode::R) == eKeyState::Down)
		{
			if (!summon)
			{
				gGeddy = object::Instantiate<Geddy>(Vector3(otusPos.x, otusPos.y - 0.5f, otusPos.z), eLayerType::Player);
				gGeddy->SetName(L"Geddy");
				MeshRenderer* mr = gGeddy->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				gGeddy->AddComponent<Transform>();
				Transform* geddyTr = gGeddy->GetComponent<Transform>();
				Vector3 geddyPos = geddyTr->GetPosition();
				Collider2D* geddyCd = gGeddy->AddComponent<Collider2D>();
				Rigidbody* geddyRb = gGeddy->AddComponent<Rigidbody>();
				gGeddy->AddComponent<GeddyScript>();
				gGeddy->GetComponent<GeddyScript>()->Initialize();
				geddyTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
				geddyCd->SetColliderOwner(eColliderOwner::Player);
				geddyCd->SetCenter(Vector2(-0.1f, -0.05f));
			}
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