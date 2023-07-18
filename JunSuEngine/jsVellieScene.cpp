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
		GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(0.5f, 0.0f, 2.0f), eLayerType::BG);
		MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"VellieSkyMaterial"));
		vellieBG->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));
		vellieBG->AddComponent<CameraScript>();

		{
			// Cloud1
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.5f, 0.0f, 1.9f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Cloud1Material"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.05f, 1.0f));
			vellieBG->AddComponent<CloudScript>();
		}


		{
			// Cloud2
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.5f, 2.0f, 1.9f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"Cloud2Material"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.05f, 1.0f));
			vellieBG->AddComponent<CloudScript>();
		}

		//{
		//	// Cloud3
		//	GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.5f, -1.0f, 1.9f), eLayerType::BG);
		//	MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
		//	mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		//	mr->SetMaterial(Resources::Find<Material>(L"Cloud3Material"));
		//	vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.05f, 1.0f));
		//	vellieBG->AddComponent<CloudScript>();
		//}

		{
			// Bombo Shop
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.5f, 0.0f, 1.8f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BomboShopMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.5f, 1.05f, 1.0f));
		}

		{
			// Bombo House
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.6f, 1.0f, 1.8f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"BomboHouseMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(1.5f, 1.0f, 1.0f));
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

		{
			// Canon
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.1f, -1.2f, 1.9f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CanonMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(1.0f, 1.0f, 1.0f));
		}

		{
			// Canon bottom
			GameObject* vellieBG = object::Instantiate<GameObject>(Vector3(-2.6f, -2.0f, 1.8f), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"CanonBottomMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 1.0f, 1.0f));
		}

		{
			// OtusHouseOutside
			GameObject* vellieBG = object::Instantiate<GameObject>(Transform::GetNDCPos(Vector3(3000.0f, 1000.0f, 1.8f)), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseOutsideMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}
		{
			// Lab
			GameObject* vellieBG = object::Instantiate<GameObject>(Transform::GetNDCPos(Vector3(2500.0f, -1000.0f, 1.8f)), eLayerType::BG);
			MeshRenderer* mr = vellieBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"LabMaterial"));
			vellieBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
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