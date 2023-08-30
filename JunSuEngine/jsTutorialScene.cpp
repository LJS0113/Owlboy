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
#include "jsGeddyArmScript.h"


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
		otusCd->SetColliderOwner(eColliderOwner::Player);
		otusCd->SetCenter(Vector2(-0.1f, -0.05f));

		/*gGeddy = object::Instantiate<Geddy>(Vector3(otusPos.x, otusPos.y - 0.5f, otusPos.z), eLayerType::Player);
		gGeddy->SetName(L"Geddy");
		mr = gGeddy->AddComponent<MeshRenderer>();
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
		geddyCd->SetCenter(Vector2(-0.1f, -0.05f));*/

		//{
		//	GeddyArm* geddyArm = object::Instantiate<GeddyArm>(Vector3(geddyPos.x, geddyPos.y, geddyPos.z - 0.01f), eLayerType::Player);
		//	geddyArm->SetName(L"GeddyArm");
		//	mr = geddyArm->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
		//	geddyArm->AddComponent<Transform>();
		//	Transform* geddyArmTr = geddyArm->GetComponent<Transform>();
		//	geddyArm->AddComponent<GeddyArmScript>();
		//	geddyArm->GetComponent<GeddyArmScript>()->Initialize();
		//	geddyArmTr->SetScale(Vector3(1.5f, 1.5f, 1.0f));
		//}


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
		//camera->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;

	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"HouseScene");
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

				GeddyArm* geddyArm = object::Instantiate<GeddyArm>(Vector3(geddyPos.x, geddyPos.y, geddyPos.z-0.01f), eLayerType::Player);
				geddyArm->SetName(L"Geddy");
				mr = geddyArm->AddComponent<MeshRenderer>();
				mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
				mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
				geddyArm->AddComponent<Transform>();
				geddyArm->AddComponent<GeddyArmScript>();
			}
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