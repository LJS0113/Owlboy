#include "jsTutorialScene.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"
#include "jsTransform.h"
#include "jsInput.h"
#include "jsCamera.h"
#include "jsCameraScript.h"
#include "jsSceneManager.h"

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
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::BG, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TutorialMaterial"));
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 2.0f));
		player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));

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
		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		camera->AddComponent<CameraScript>();

		{
			// UI Camera
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::BG, false);
			//camera->AddComponent<CameraScript>();
		}
	}
	void TutorialScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"VellieScene");
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