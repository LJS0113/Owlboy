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

		gPlayer = object::Instantiate<Player>(Vector3(0.5f, 0.0f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		MeshRenderer* mr = gPlayer->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		gPlayer->AddComponent<Transform>();
		Transform* otusTr = gPlayer->GetComponent<Transform>();
		Vector3 otusPos = otusTr->GetPosition();
		Collider2D* otusCd = gPlayer->AddComponent<Collider2D>();
		Rigidbody* gPlayerRb = gPlayer->AddComponent<Rigidbody>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->GetComponent<PlayerScript>()->Initialize();
		otusTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		//cd->SetSize(Vector2(0.0f, 0.0f));
		//cd->SetCenter(Vector2(-0.1f, -0.05f));
		otusCd->SetColliderOwner(eColliderOwner::Player);
		otusCd->SetCenter(Vector2(-0.1f, -0.05f));


		Geddy* geddy = object::Instantiate<Geddy>(Vector3(otusPos.x, otusPos.y - 0.5f, otusPos.z), eLayerType::Player);
		geddy->SetName(L"Geddy");
		mr = geddy->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		geddy->AddComponent<Transform>();
		Transform* geddyTr = geddy->GetComponent<Transform>();
		Collider2D* geddyCd = geddy->AddComponent<Collider2D>();
		Rigidbody* geddyRb = geddy->AddComponent<Rigidbody>();
		geddy->AddComponent<GeddyScript>();
		geddy->GetComponent<GeddyScript>()->Initialize();
		geddyTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		geddyCd->SetColliderOwner(eColliderOwner::Player);
		geddyCd->SetCenter(Vector2(-0.1f, -0.05f));

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
		renderer::mainCamera = cameraComp;

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