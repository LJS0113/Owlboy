#include "jsComputeShader.h"
#include "jsGraphicDevice_DX11.h"



namespace js::graphics
{
	ComputeShader::ComputeShader()
		: Resource(enums::eResourceType::ComputeShader)
	{
	}

	ComputeShader::~ComputeShader()
	{
	}

	bool ComputeShader::Create(const std::wstring& name, const std::string& methodName)
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullpath(shaderPath.c_str());
		fullpath += name;

		ID3DBlob* errorblob = nullptr;
		GetDevice()->CompileFromFile(fullpath, methodName, "cs_5_0", mCSBlob.GetAddressOf());
		GetDevice()->CreateComputeShader(mCSBlob->GetBufferPointer(), mCSBlob->GetBufferSize(), mCS.GetAddressOf());

		return true;
	}
}