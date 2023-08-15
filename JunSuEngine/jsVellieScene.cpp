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
		Player* player = object::Instantiate<Player>(Vector3(-3.0f, 1.5f, 1.0f), eLayerType::Player);
		player->SetName(L"Otus");
		Transform* tr = player->GetComponent<Transform>();
		Collider2D* cd = player->AddComponent<Collider2D>();
		player->AddComponent<PlayerScript>();
		player->GetComponent<PlayerScript>()->Initialize();

		{
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-3.0f, 1.5f, 1.999f), eLayerType::Scenery);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"VellieMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(48.0f, 27.0f, 1.0f));
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