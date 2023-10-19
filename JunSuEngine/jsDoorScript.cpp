#include "jsDoorScript.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsScene.h"

namespace js
{

	DoorScript::DoorScript()
	{
	}

	DoorScript::~DoorScript()
	{
	}

	void DoorScript::Initialize()
	{
	}

	void DoorScript::Update()
	{
	}

	void DoorScript::LateUpdate()
	{
	}

	void DoorScript::Render()
	{
	}

	void DoorScript::OnCollisionEnter(Collider2D* other)
	{

	}

	void DoorScript::OnCollisionStay(Collider2D* other)
	{
		if (Input::GetKeyState(eKeyCode::F) == eKeyState::Down)
		{
			if (SceneManager::GetActiveScene() == SceneManager::FindScene(L"HouseScene"))
			{
				SceneManager::LoadScene(L"VellieScene");
				return;
			}
			if (SceneManager::GetActiveScene() == SceneManager::FindScene(L"VellieScene"))
			{
				SceneManager::LoadScene(L"BossScene");
				return;
			}
		}
	}

	void DoorScript::OnCollisionExit(Collider2D* other)
	{
	}

}