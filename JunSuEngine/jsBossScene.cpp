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
#include "jsGeddy.h"
#include "jsGeddyScript.h"
#include "jsWall.h"
#include "jsGeddyBullet.h"
#include "jsGeddyBulletScript.h"
#include "jsAttackRange.h"
#include "jsAttackRangeScript.h"
#include "jsCollisionManager.h"

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
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::AttackRange, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Monster, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::MonsterBullet, true);

		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Artifact, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::PlayerBullet, true);
		CollisionManager::SetLayer(eLayerType::Monster, eLayerType::PlayerAttack, true);

		CollisionManager::SetLayer(eLayerType::Artifact, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Artifact, eLayerType::Wall, true);

		gPlayer = object::Instantiate<Player>(Vector3(-3.0f, -1.5f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		Transform* tr = gPlayer->GetComponent<Transform>();
		Collider2D* cd = gPlayer->AddComponent<Collider2D>();
		Rigidbody* gPlayerRb = gPlayer->AddComponent<Rigidbody>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		//gPlayer->AddComponent<CameraScript>();

		monster = object::Instantiate<Monster>(Vector3(0.0f, -1.2f, 1.0f), eLayerType::Monster);
		monster->SetName(L"MaskedTortoise");
		Transform* monsterTr = monster->GetComponent<Transform>();
		Collider2D* monsterCd = monster->AddComponent<Collider2D>();
		monster->AddComponent<MaskedTortoiseScript>();
		monster->GetComponent<MaskedTortoiseScript>()->Initialize();
		monsterTr->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		Vector3 monsterPos = monsterTr->GetPosition();

		{
			// Boss Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(0.0f, -1.9f, 2.0f), eLayerType::Ground);
			ground->SetName(L"BossGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(10.0f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
		{
			// Boss Left Wall
			Wall* wall = object::Instantiate<Wall>(Vector3(-4.0, 0.0f, 2.0f), eLayerType::Wall);
			wall->SetName(L"BossLeftWall");
			wall->GetComponent<Transform>()->SetScale(Vector3(0.5f, 5.0f, 1.9f));
			Collider2D* cd = wall->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Wall);
		}
		{
			// Boss Right Wall
			Wall* wall = object::Instantiate<Wall>(Vector3(4.0, 0.0f, 2.0f), eLayerType::Wall);
			wall->SetName(L"BossRightWall");
			wall->GetComponent<Transform>()->SetScale(Vector3(0.5f, 5.0f, 1.9f));
			Collider2D* cd = wall->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Wall);
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
			//camera->AddComponent<CameraScript>();
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
				mr->SetMaterial(Resources::Find<Material>(L"SpriteReverseAnimationMaterial"));
				gGeddy->AddComponent<Transform>();
				Transform* geddyTr = gGeddy->GetComponent<Transform>();
				Vector3 geddyPos = geddyTr->GetPosition();
				Collider2D* geddyCd = gGeddy->AddComponent<Collider2D>();
				Rigidbody* geddyRb = gGeddy->AddComponent<Rigidbody>();
				gGeddy->AddComponent<GeddyScript>();
				gGeddy->GetComponent<GeddyScript>()->Initialize();
				geddyTr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
				geddyCd->SetColliderOwner(eColliderOwner::Player);
				geddyCd->SetCenter(Vector2(0.0f, -0.05f));
			}
		}

		bool hang = gPlayer->GetComponent<PlayerScript>()->IsHang();
		if (hang && Input::GetKeyState(eKeyCode::LBUTTON) == eKeyState::Down)
		{
			Transform* geddyTr = gGeddy->GetComponent<Transform>();
			Vector3 geddyPos = geddyTr->GetPosition();

			GeddyBullet* bullet = object::Instantiate<GeddyBullet>(Vector3(geddyPos), eLayerType::PlayerBullet);
			MeshRenderer* mr = bullet->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteAnimationMaterial"));
			bullet->AddComponent<Collider2D>();
			bullet->AddComponent<Transform>();
			bullet->AddComponent<GeddyBulletScript>();
			bullet->GetComponent<GeddyBulletScript>()->Initialize();
		}

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

