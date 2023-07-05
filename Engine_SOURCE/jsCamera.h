#pragma once
#include "jsComponent.h"
#include "jsGraphics.h"

namespace js
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			OrthoGraphic,
			End,
		};
		static Matrix GetViewMatrix() { return View; }
		static Matrix GetProjectionMatrix() { return Projection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);
		void RegisterCameraInRenderer();

		void TurnLayerMask(eLayerType type, bool enable = true);
		void EnabelLayerMasks() { mLayerMask.set();}
		void DisabelLayerMasks() { mLayerMask.reset(); }

		void AlphaSortGameObjects();
		void ZSortTransparencyGameObjects();
		void DivideAlphaBlendGameObjcets(const std::vector<GameObject*> gameObjs);

		void RenderOpaque();
		void RenderCutOut();
		void RenderTransparent();

		void EnableDepthStencilState();
		void DisableDepthStencilState();

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<GameObject*> mOpaqueGameObjects;
		std::vector<GameObject*> mCutOutGameObjects;
		std::vector<GameObject*> mTransparentGameObjects;

	};

}