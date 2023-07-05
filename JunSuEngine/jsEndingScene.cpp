#include "jsEndingScene.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsTransform.h"
#include "jsCameraScript.h"
#include "jsResources.h"
#include "jsMeshRenderer.h"
#include "jsGameObject.h"
#include "jsTitleScene.h" 

namespace js
{
	EndingScene::EndingScene()
	{
	}
	EndingScene::~EndingScene()
	{
	}
	void EndingScene::Initialize()
	{
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"Ending_SkyMaterial"));
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		player->GetComponent<Transform>()->SetScale(Vector3(8.0f, 4.5f, 1.0f));

		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	void EndingScene::Update()
	{
		if (Input::GetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			SceneManager::LoadScene(L"TitleScene");
		}
		Scene::Update();
	}
	void EndingScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void EndingScene::Render()
	{
		Scene::Render();
	}
	void EndingScene::OnEnter()
	{
	}
	void EndingScene::OnExit()
	{
	}
}