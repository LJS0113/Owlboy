#include "jsTitleScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsTransform.h"
#include "jsCameraScript.h"
#include "jsResources.h"
#include "jsMeshRenderer.h"
#include "jsPlayScene.h"
#include "jsObject.h"
#include "jsTime.h"


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
		GameObject* titleBG1 = object::Instantiate<GameObject>(Vector3(0.5f, 0.0f, 2.0f), eLayerType::BG);
		MeshRenderer* mr = titleBG1->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleSkyMaterial"));
		titleBG1->GetComponent<Transform>()->SetScale(Vector3(9.0f, 4.5f, 1.0f));
		

		titleBG = object::Instantiate<GameObject>(Vector3(0.0f, 0.5f, 1.9999f), eLayerType::BG);
		mr = titleBG->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleCloudMaterial"));
		titleBG->GetComponent<Transform>()->SetScale(Vector3(5.0f, 4.0f, 1.0f));
		//TitleCloudMaterial
		{
			// MainRock
			GameObject* titleBG1 = object::Instantiate<GameObject>(Vector3(2.5f, -0.5f, 1.0f), eLayerType::Player);
			MeshRenderer* mr = titleBG1->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"TitleMainRockMaterial"));
			titleBG1->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}
		{
			// OtusHouseTop
			GameObject* titleBG1 = object::Instantiate<GameObject>(Vector3(-3.15f, 1.0f, 1.1f), eLayerType::Player);
			MeshRenderer* mr = titleBG1->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseTopMaterial"));
			titleBG1->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.1f, 1.0f));
		}
		{
			// OtusHouseMiddle
			GameObject* titleBG1 = object::Instantiate<GameObject>(Vector3(-3.0f, -1.0f, 1.0f), eLayerType::Player);
			MeshRenderer* mr = titleBG1->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"OtusHouseMiddleMaterial"));
			titleBG1->GetComponent<Transform>()->SetScale(Vector3(2.0f, 2.0f, 1.0f));
		}
		{
			// Logo
			GameObject* titleBG1 = object::Instantiate<GameObject>(Vector3(0.0f, 1.0f, 1.0f), eLayerType::Player);
			MeshRenderer* mr = titleBG1->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"LogoMaterial"));
			titleBG1->GetComponent<Transform>()->SetScale(Vector3(2.0f, 1.0f, 1.0f));
		}
		// Main Camera
		GameObject* camera = object::Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		Camera* cameraComp = camera->AddComponent<Camera>();
		//camera->AddComponent<CameraScript>();
	}
	void TitleScene::Update()
	{
		static float chTime = 0.0f;
		chTime += Time::DeltaTime();

		const float pi = 3.141592f;
		float degree = pi / 180.0f;

		titleBG->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, degree* chTime));

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