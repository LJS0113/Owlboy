#include "jsMouseCursor.h"
#include "jsInput.h"
#include "jsMeshRenderer.h"
#include "jsResources.h"



namespace js
{
	MouseCursor::MouseCursor()
	{

	}
	MouseCursor::~MouseCursor()
	{
	}
	void MouseCursor::Initialize()
	{
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"MouseMaterial"));
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(0.3f, 0.3f, 1.0f));
		ShowCursor(false);
	}
	void MouseCursor::Update()
	{
		GameObject::Update();

		Transform* tr = GetComponent<Transform>();
		Vector2 pos = Input::GetMousePos();
		Vector3 mousePos = Vector3(pos.x, pos.y, 0.0f);
		mousePos = tr->GetNDCPos(Vector3(mousePos.x, mousePos.y, mousePos.z));

		tr->SetPosition(mousePos.x, mousePos.y, 1.9f);
	}
	void MouseCursor::Render()
	{
		GameObject::Render();
	}
	void MouseCursor::LateUpdate()
	{
		GameObject::LateUpdate();
	}
}