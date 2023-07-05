#include "jsVellieScene.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsTransform.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsInput.h"
#include "jsSceneManager.h"

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
		GameObject* vellieBG = new GameObject();
		AddGameObject(eLayerType::BG, vellieBG);
		MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VellieSkyMaterial"));
		vellieBG->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 0.0f, 2.0f));
		vellieBG->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));
		vellieBG->AddComponent<CameraScript>();

		{
			// Bombo Shop
			GameObject* vellieBG = new GameObject();
			AddGameObject(eLayerType::BG, vellieBG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BomboShopMaterial"));
			vellieBG->GetComponent<Transform>()->SetPosition(Vector3(-2.5f, 0.0f, 1.8f));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.05f, 1.0f));
		}

		{
			// Bombo House
			GameObject* vellieBG = new GameObject();
			AddGameObject(eLayerType::BG, vellieBG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BomboHouseMaterial"));
			vellieBG->GetComponent<Transform>()->SetPosition(Vector3(-2.6f, 1.0f, 1.9f));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.0f, 1.0f));
		}

		{
			// otus hp bar
			GameObject* hpBar = new GameObject();
			AddGameObject(eLayerType::UI, hpBar);
			MeshRenderer* mr = hpBar->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHpBarMaterial"));
			hpBar->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, 2.0f, 1.0f));
			hpBar->GetComponent<Transform>()->SetScale(Vector3(1.0f, 0.2f, 1.0f));
		}

		{
			// Canon
			GameObject* vellieBG = new GameObject();
			AddGameObject(eLayerType::BG, vellieBG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CanonMaterial"));
			vellieBG->GetComponent<Transform>()->SetPosition(Vector3(-2.1f, -1.2f, 1.9f));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		}

		{
			// Canon bottom
			GameObject* vellieBG = new GameObject();
			AddGameObject(eLayerType::BG, vellieBG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CanonBottomMaterial"));
			vellieBG->GetComponent<Transform>()->SetPosition(Vector3(-2.6f, -2.0f, 1.8f));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 1.0f, 1.0f));
		}

		{
			// OtusHouseOutside
			GameObject* vellieBG = new GameObject();
			AddGameObject(eLayerType::BG, vellieBG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseOutsideMaterial"));
			vellieBG->GetComponent<Transform>()->SetPosition(Vector3(2.0f, 0.0f, 1.8f));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}

		{
			// Main Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		{
			// UI Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false);
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			//camera->AddComponent<CameraScript>();
		}

	}

	void VellieScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"PlayScene");
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