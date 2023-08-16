#include "jsCameraScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsPlayer.h"

extern js::Player* gPlayer;

namespace js
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		
		Transform* playerTr = gPlayer->GetComponent<Transform>();
		Vector3 playerPos = playerTr->GetPosition();

		//if (Input::GetKey(eKeyCode::UP))
		//{
		//	pos.y = playerPos.y;
		//	//pos.y += 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::DOWN))
		//{
		//	pos.y = playerPos.y;
		//	//pos.y -= 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::LEFT))
		//{
		//	pos.x = playerPos.x;
		//	//pos.x -= 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::RIGHT))
		//{
		//	pos.x = playerPos.x;
		//	//pos.x += 2.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}

		if (Input::GetKey(eKeyCode::UP))
		{
			//pos.y = playerPos.y;
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::DOWN))
		{
			//pos.y = playerPos.y;
			pos.y -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::LEFT))
		{
			//pos.x = playerPos.x;
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			//pos.x = playerPos.x;
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}

		if (Input::GetKey(eKeyCode::W))
		{
			//pos.y = playerPos.y;
			pos.y += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::S))
		{
			//pos.y = playerPos.y;
			pos.y -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::A))
		{
			//pos.x = playerPos.x;
			pos.x -= 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		else if (Input::GetKey(eKeyCode::D))
		{
			//pos.x = playerPos.x;
			pos.x += 2.0f * Time::DeltaTime();
			tr->SetPosition(pos);
		}
		//else if (Input::GetKey(eKeyCode::Q))
		//{
		//	pos.z -= 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
		//else if (Input::GetKey(eKeyCode::E))
		//{
		//	pos.z += 5.0f * Time::DeltaTime();
		//	tr->SetPosition(pos);
		//}
	}
}