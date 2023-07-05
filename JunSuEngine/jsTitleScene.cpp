#include "jsTitleScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsTransform.h"
#include "jsCameraScript.h"
#include "jsResources.h"
#include "jsMeshRenderer.h"
#include "jsPlayScene.h"

namespace js
{
	TitleScene::TitleScene()
	{
	}
	TitleScene::~TitleScene()
	{
	}
	void TitleScene::Initialize()
	{
		GameObject* titleBG = new GameObject();
		AddGameObject(eLayerType::BG, titleBG);
		MeshRenderer* mr = titleBG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleSkyMaterial"));
		titleBG->GetComponent<Transform>()->SetPosition(Vector3(0.5f, 0.0f, 2.0f));
		titleBG->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));

		{
			// MainRock
			GameObject* titleBG = new GameObject();
			AddGameObject(eLayerType::Player, titleBG);
			MeshRenderer* mr = titleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TitleMainRockMaterial"));
			titleBG->GetComponent<Transform>()->SetPosition(Vector3(2.5f, -0.5f, 1.0f));
			titleBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}	
		{
			// OtusHouseTop
			GameObject* titleBG = new GameObject();
			AddGameObject(eLayerType::Player, titleBG);
			MeshRenderer* mr = titleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseTopMaterial"));
			titleBG->GetComponent<Transform>()->SetPosition(Vector3(-3.15f, 1.0f, 1.1f));
			titleBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.1f, 1.0f));
		}
		{
			// OtusHouseMiddle
			GameObject* titleBG = new GameObject();
			AddGameObject(eLayerType::Player, titleBG);
			MeshRenderer* mr = titleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh")); 
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseMiddleMaterial"));
			titleBG->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, -1.0f, 1.0f));
			titleBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}
		{
			// Logo
			GameObject* titleBG = new GameObject();
			AddGameObject(eLayerType::Player, titleBG);
			MeshRenderer* mr = titleBG->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"LogoMaterial"));
			titleBG->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 1.0f, 1.0f));
			titleBG->GetComponent<Transform>()->SetScale(Vector3(2.0f, 1.0f, 1.0f));
		}
		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	void TitleScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TutorialScene");
		}
		Scene::Update();
	}
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}