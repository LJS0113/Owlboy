#include "jsMaterial.h"


namespace js::graphics
{
	Material::Material()
		: Resource(js::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
	{
	}

	Material::~Material()
	{
	}

	HRESULT Material::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void Material::Binds()
	{
		if(mTexture)
			mTexture->BindShader(eShaderStage::PS, 0);

		if(mShader)
			mShader->Binds();
	}

	void Material::Clear()
	{
		mTexture->Clear();
	}
}