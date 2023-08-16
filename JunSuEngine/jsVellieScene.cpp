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


extern js::Player* gPlayer;


namespace js
{
	VellieScene::VellieScene()
	{
	}

	VellieScene::~VellieScene()
	{
	}

	void VellieScene::Initialize()
	{
		gPlayer = object::Instantiate<Player>(Vector3(0.0f, 0.0f, 1.0f), eLayerType::Player);
		gPlayer->SetName(L"Otus");
		Transform* tr = gPlayer->GetComponent<Transform>();
		Collider2D* cd = gPlayer->AddComponent<Collider2D>();
		gPlayer->AddComponent<PlayerScript>();
		gPlayer->GetComponent<PlayerScript>()->Initialize();
		tr->SetScale(Vector3(2.5f, 2.5f, 1.0f));
		gPlayer->AddComponent<CameraScript>();

		{
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-3.0f, 1.5f, 1.999f), eLayerType::Scenery);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"VellieMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(60.0f, 40.0f, 1.0f));
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
		}

		{
			// UI Camera
			GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			cameraComp->TurnLayerMask(eLayerType::Scenery, false);
		}

		{
			Door* door = object::Instantiate<Door>(Vector3(-27.431f, -15.214f, 1.1f), eLayerType::Artifact);
			Collider2D* col = door->GetComponent<Collider2D>();
			col->SetSize(Vector2(1.5f, 1.5f));
		}
	}

	void VellieScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"DungeonScene");
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
	}

}