#pragma once
#include "jsResource.h"
#include "jsShader.h"
#include "jsTexture.h"

namespace js::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material(); 

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;
	};

}