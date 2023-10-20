#include "jsVellieScene.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsTransform.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsObject.h"
#include "jsCloudScript.h"
#include "jsPlayer.h"
#include "jsPlayerScript.h"
#include "jsDoor.h"
#include "jsRenderer.h"
#include "jsGround.h"
#include "jsRigidBody.h"
#include "jsDoorScript.h"
#include "jsCollisionManager.h"
#include "jsGeddy.h"
#include "jsGeddyScript.h"
#include "jsWall.h"
#include "jsWallScript.h"
#include "jsAudioSource.h"
#include "jsMouseCursor.h"

namespace js
{
	VellieScene::VellieScene()
		: as(nullptr)
	{
	}

	VellieScene::~VellieScene()
	{
	}

	void VellieScene::Initialize()
	{
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Ground, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Wall, true);
		CollisionManager::SetLayer(eLayerType::Player, eLayerType::Artifact, true);

		MouseCursor* mouse = object::Instantiate<MouseCursor>(eLayerType::MouseCursor);
		mouse->Initialize();

		gPlayer = object::Instantiate<Player>(Vector3(1.5097f, -0.80f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		Transform* tr = gPlayer->GetComponent<Transform>();
		Collider2D* cd = gPlayer->AddComponent<Collider2D>();
		Rigidbody* otusRb = gPlayer->AddComponent<Rigidbody>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		gPlayer->AddComponent<CameraScript>();


		vellieBG = object::Instantiate<GameObject>(Vector3(-3.0f, 1.5f, 1.999f), eLayerType::Scenery);
		MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VellieMaterial"));
		vellieBG->GetComponent<Transform>()->SetScale(Vector3(48.0f, 27.0f, 1.0f));
		as = vellieBG->AddComponent<AudioSource>();
		as->SetClip(Resources::Load<AudioClip>(L"VellieSound", L"..\\Resources\\Sound\\OST\\Vellie.mp3"));
		as->Play();

		{
			// House Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(0.2629f, -0.9f, 2.0f), eLayerType::Ground);
			ground->SetName(L"HouseGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(3.0f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}
		{
			// Vellie Ground
			Ground* ground = object::Instantiate<Ground>(Vector3(-10.0f, -10.0f, 2.0f), eLayerType::Ground);
			ground->SetName(L"VellieGround");
			ground->GetComponent<Transform>()->SetScale(Vector3(50.5f, 0.2f, 2.0f));
			Collider2D* cd = ground->AddComponent<Collider2D>();
			cd->SetColliderOwner(eColliderOwner::Ground);
		}

		{
			// Sky
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(0.5f, 0.0f, 2.0f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"VellieSkyMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));
			vellieBG->AddComponent<CameraScript>();
		}

		{
			// Main Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			renderer::mainCamera = cameraComp;
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
			//Collider2D* camCd = camera->AddComponent<Collider2D>();
			//camCd->SetSize(Vector2(1.5f, 1.5f));
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			cameraComp->TurnLayerMask(eLayerType::Scenery, false);
			cameraComp->TurnLayerMask(eLayerType::MouseCursor, false);
		}

		{
			Door* door = object::Instantiate<Door>(Vector3(-22.65f, -9.699f, 1.1f), eLayerType::Artifact);
			Collider2D* col = door->GetComponent<Collider2D>();
			col->SetSize(Vector2(0.5f, 0.5f));
			door->AddComponent<DoorScript>();
		}
	}

	void VellieScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			as->Stop();
			SceneManager::LoadScene(L"BossScene");
		}

		Scene::Update();
	}

	void VellieScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void VellieScene::Render()
	{
		Scene::Render();
	}

	void VellieScene::OnEnter()
	{
	}

	void VellieScene::OnExit()
	{
		as->Stop();
	}

}