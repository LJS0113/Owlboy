#include "jsHouseScene.h"
#include "jsTitleScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsTransform.h"
#include "jsCameraScript.h"
#include "jsResources.h"
#include "jsMeshRenderer.h"
#include "jsPlayScene.h"
#include "jsObject.h"
#include "jsDoor.h"
#include "jsDoorScript.h"
#include "jsGround.h"
#include "jsGroundScript.h"
#include "jsCollider2D.h"
#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsRigidBody.h"
#include "jsCollisionManager.h"
#include "jsRenderer.h"
#include "jsWall.h"
#include "jsWallScript.h"

namespace js
{
	HouseScene::HouseScene()
	{
	}
	HouseScene::~HouseScene()
	{
	}
	void HouseScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Artifact, true);


		gPlayer = object::Instantiate<Player>(Vector3(0.0f, 1.0f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		MeshRenderer* mr = gPlayer->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		Transform* tr = gPlayer->GetComponent<Transform>();
		Collider2D* cd = gPlayer->AddComponent<Collider2D>();
		Rigidbody* playerRb = gPlayer->AddComponent<Rigidbody>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->AddComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		cd->SetSize(Vector2(0.1f, 0.2f));

		{
			GameObject* player = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, 2.0f), eLayerType::BG);
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"HouseMaterial"));
			player->GetComponent<Transform>()->SetScale(Vector3(6.0f, 4.5f, 1.0f));
		}
		{
			// wall
			Wall* wall= object::Instantiate<Wall>(Vector3(-2.0f, 0.0f, 2.0f), eLayerType::Ground);
			wall->SetName(L"BedGround");
			wall->GetComponent<Transform>()->SetScale(Vector3(0.3f, 3.0f, 2.0f));
			wall->AddComponent<WallScript>();
			Collider2D* cd = wall->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
		//{
		//	// Bed Ground
		//	Ground* ground = object::Instantiate<Ground>(Vector3(-1.0f, 0.5f, 2.0f), eLayerType::Ground);
		//	ground->SetName(L"BedGround");
		//	ground->GetComponent<Transform>()->SetScale(Vector3(1.3f, 0.2f, 2.0f));
		//	Collider2D* cd = ground->AddComponent<Collider2D>();
		//	cd->SetColliderOwner(eColliderOwner::Ground);
		//}

		//{
		//	// Bed Right Ground
		//	Ground* ground = object::Instantiate<Ground>(Vector3(1.0f, 0.0f, 2.0f), eLayerType::Ground);
		//	ground->SetName(L"BedGround");
		//	ground->GetComponent<Transform>()->SetScale(Vector3(1.3f, 0.2f, 2.0f));
		//	Collider2D* cd = ground->AddComponent<Collider2D>();
		//	cd->SetColliderOwner(eColliderOwner::Ground);
		//}
		{
			// House Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(0.0f, -1.5f, 2.0f), eLayerType::Ground);
			ground->SetName(L"BedGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(4.0f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
		{
			// Door
			Door* door = object::Instantiate<Door>(Vector3(-1.1f, -1.2f, 1.0f), eLayerType::Artifact);
			Collider2D* cd = door->GetComponent<Collider2D>();
			cd->SetSize(Vector2(0.3f, 0.5f));
			door->AddComponent<DoorScript>();
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
		GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		renderer::mainCamera = cameraComp;
		//camera->AddComponent<CameraScript>();
		
		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			cameraComp->TurnLayerMask(eLayerType::Player, false);
		}
	}
	void HouseScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"VellieScene");
		}
		Scene::Update();
	}
	void HouseScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void HouseScene::Render()
	{
		Scene::Render();
	}
	void HouseScene::OnEnter()
	{
	}
	void HouseScene::OnExit()
	{
	}
}