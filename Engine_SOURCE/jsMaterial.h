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

		void SetShader(Shader* shader) { mShader = shader; }
		void SetTexture(Texture* texture) { mTexture = texture; }

	private:
		Shader* mShader;
		Texture* mTexture;
	};

}