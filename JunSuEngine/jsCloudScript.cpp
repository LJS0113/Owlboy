#include "jsCloudScript.h"
#include "jsTransform.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsObject.h"

namespace js
{

	CloudScript::CloudScript()
	{
	}

	CloudScript::~CloudScript()
	{
	}

	void CloudScript::Initialize()
	{
	}

	void CloudScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		pos.x += 0.4f * Time::DeltaTime();
		tr->SetPosition(pos);

		if(pos.x >= 5.0f)
			object::Destroy(GetOwner());
	}

	void CloudScript::LateUpdate()
	{
	}

	void CloudScript::Render()
	{
	}

}