#pragma once
#include "jsEngine.h"
#include "jsGraphicDevice_DX11.h"
#include "jsScene.h"

namespace js
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();
		void Destroy();
		void Present();

		void SetWindow(HWND hwnd, UINT width, UINT height);

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HWND GetHwnd() { return mHwnd; }

	private:
		bool mbInitialize = false;

		std::unique_ptr<js::graphics::GraphicDevice_DX11> graphicDevice;
									
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;
	};

}