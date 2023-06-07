#include "jsRenderer.h"
#include "jsInput.h"


namespace renderer
{
	Vertex vertexes[4] = {};

	// Input Layout(정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// vertexes는 cpu에 저장되어 있는 정보이므로 이걸 gpu로 보내려면 버퍼가 필요함. 그게 버텍스 버퍼.
	// Vertext Buffer
	js::Mesh* mesh = nullptr;
	//ID3D11Buffer* triangleBuffer = nullptr;
	//ID3D11Buffer* triangleIdxBuffer = nullptr;
	ID3D11Buffer* triangleConstantBuffer = nullptr;

	// 컴파일시에 뭐가 잘못 됐는지 모르니 에러들의 정보를 모아놓는 곳이 에러블롭
	// error blob
	ID3DBlob* errorBlob = nullptr;

	// 셰이더에서 처리한 정보들이 블롭으로 들어감. 버텍스 셰이더에서 처리한 정보들은 버텍스셰이더블롭에 들어가있음.
	// Vertex Shader Code -> binary code
	js::Shader* shader = nullptr;
	//ID3DBlob* triangleVSBlob = nullptr;

	//// 전달받는 정보를 가공하는곳이 버텍스 셰이더.(가공 = 위치정보를 공간에 맞게 변환)
	//// blob에는 코드만 들어있으니 이 코드를 실행시키는게 바로 버텍스 셰이더.
	//// VertexShader
	//ID3D11VertexShader* triangleVSShader = nullptr;

	//// PixelShader code -> binary code
	//ID3DBlob* trianglePSBlob = nullptr;

	// PixelShader
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		mesh = new js::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		// Index Buffer
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		js::graphics::GetDevice()->CreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		js::graphics::GetDevice()->SetConstantBuffer(renderer::triangleConstantBuffer, &pos, sizeof(Vector4));
		js::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBType::Transform, renderer::triangleConstantBuffer);
	}

	void LoadShader()
	{
		//js::graphics::GetDevice()->CreateShader();

		shader = new js::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}
	void renderer::Release()
	{
		if (triangleLayout != nullptr)
			triangleLayout->Release();

		if (triangleConstantBuffer != nullptr)
			triangleConstantBuffer->Release();

		if (errorBlob != nullptr)
			errorBlob->Release();

		if (trianglePSShader != nullptr)
			trianglePSShader->Release();
	}
}