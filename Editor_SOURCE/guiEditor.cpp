#include "guiEditor.h"
#include "..\Engine_SOURCE\jsMesh.h"
#include "..\Engine_SOURCE\jsMaterial.h"
#include "..\Engine_SOURCE\jsMeshRenderer.h"
#include "..\Engine_SOURCE\jsTransform.h"
#include "..\Engine_SOURCE\jsResources.h"
#include "..\Engine_SOURCE\jsRenderer.h"

#include "..\JunSuEngine\jsGridScript.h"

namespace gui
{
	using namespace js::enums;
	using namespace js;
	std::vector<Widget*> Editor::mWidgets = {};
	std::vector<EditorObject*> Editor::mEditorObjects = {};
	std::vector<DebugObject*> Editor::mDebugObjects = {};

	Editor::Editor()
	{
	}

	Editor::~Editor()
	{
	}

	void Editor::Initialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<Mesh> mesh
			= Resources::Find<Mesh>(L"DebugRect");
		std::shared_ptr<Material> material
			= Resources::Find<Material>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();
		MeshRenderer* mr
			= mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();
		mr->SetMaterial(material);
		mr->SetMesh(mesh);


		EditorObject* grid = new EditorObject();
		grid->SetName(L"Grid");

		mr = grid->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"GridMaterial"));
		GridScript* gridSc = grid->AddComponent<GridScript>();
		gridSc->SetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);
	}

	void Editor::Run()
	{
		Update();
		LateUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::LateUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->LateUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (const js::graphics::DebugMesh& mesh : renderer::debugMeshs)
		{
			DebugRender(mesh);
		}

		renderer::debugMeshs.clear();
	}

	void Editor::Release()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::DebugRender(const js::graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서
		// 해당 게임오브젝트위에 그려주면된다.
		Transform* tr = debugObj->GetComponent<Transform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->SetPosition(pos);
		tr->SetScale(mesh.scale);
		tr->SetRotation(mesh.rotation);

		tr->LateUpdate();

		Camera* mainCamera = renderer::mainCamera;

		Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
		Camera::SetGpuProjectionMatrix(mainCamera->GetProjectionMatrix());


		//debugObj->Render();
	}

}