#include "jsTutorialScene.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsTransform.h"
#include "jsInput.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsSceneManager.h"
#include "jsObject.h"
#include "jsPlayerScript.h"
#include "jsAnimator.h"
#include "jsRigidBody.h"
#include "jsGround.h"
#include "jsCollisionManager.h"
#include "jsGeddyScript.h"
#include "jsPlayer.h"
#include "jsGeddy.h"
#include "jsGeddyArm.h"

namespace js
{
	TutorialScene::TutorialScene()
	{
	}
	TutorialScene::~TutorialScene()
	{
	}
	void TutorialScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);

		//GameObject* player = object::Instantiate<GameObject>(Vector3(0.5f, 0.0f, 1.0f), eLayerType::Player);
		Player* player = object::Instantiate<Player>(Vector3(0.5f, 0.0f, 1.0f), eLayerType::Player);
		player->SetName(L"Otus");
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		Transform* tr = player->GetComponent<Transform>();
		Collider2D* cd = player->AddComponent<Collider2D>();
		Rigidbody* playerRb = player->AddComponent<Rigidbody>();
		player->AddComponent<PlayerScript>();
		player->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		//cd->SetSize(Vector2(0.0f, 0.0f));
		//cd->SetCenter(Vector2(-0.1f, -0.05f));
		cd->SetColliderOwner(eColliderOwner::Player);
		cd->SetCenter(Vector2(-0.1f, -0.05f));

		{
			Geddy* geddy = object::Instantiate<Geddy>(Vector3(0.5f, -0.2f, 1.1f), eLayerType::Player);
			geddy->SetName(L"Geddy");
			MeshRenderer* geddyMr = geddy->AddComponent<MeshRenderer>();
			geddyMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			geddyMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			geddy->AddComponent<GeddyScript>();
			geddy->GetComponent<GeddyScript>()->Initialize();
			Transform* tr = geddy->GetComponent<Transform>();
			tr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
			Vector3 geddyPos = tr->GetPosition();

			GeddyArm* arm = object::Instantiate<GeddyArm>(Vector3(geddyPos.x, geddyPos.y , 1.0f), eLayerType::Player);
			MeshRenderer* geddyArmMr = arm->AddComponent<MeshRenderer>();
			geddyArmMr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			geddyArmMr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		}
		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BG);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TutorialMaterial"));
			player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));
		}
		{
			Ground* ground = object::Instantiate<Ground>(Vector3(0.0f, -1.9f, 2.0f), eLayerType::Ground);
			ground->SetName(L"ground"); 
			//ground->SetPlayer(player);
			ground->GetComponent<Transform>()->SetScale(Vector3(3.5f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
			//cd->SetCenter(Vector2(-0.05f, -1.9f));
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
		// Main Camera
		GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();

		{
			//// UI Camera
			//GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
			//Camera* cameraComp = camera->AddComponent<Camera>();
			//cameraComp->TurnLayerMask(eLayerType::BG, false);
		}
	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"HouseScene");
		}
		Scene::Update();
	}
	void TutorialScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TutorialScene::Render()
	{
		Scene::Render();
	}
	void TutorialScene::OnEnter()
	{
	}
	void TutorialScene::OnExit()
	{
	}
}