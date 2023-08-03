#include "jsRenderer.h"
#include "jsResources.h"
#include "jsTexture.h"
#include "jsMaterial.h"
#include "jsStructedBuffer.h"
#include "jsPaintShader.h"


namespace renderer
{
	using namespace js;
	using namespace js::graphics;
	js::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};

	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	js::Camera* mainCamera = nullptr;
	std::vector<js::Camera*> cameras = {};
	std::vector<DebugMesh> debugMeshs = {};

	// light
	std::vector<Light*> lights = {};
	StructedBuffer* lightsBuffer = nullptr;

	void SetupState()
	{
#pragma region InputLayout
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = js::Resources::Find<Shader>(L"TriangleShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = js::Resources::Find<Shader>(L"SpriteShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = js::Resources::Find<Shader>(L"GridShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = js::Resources::Find<Shader>(L"DebugShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = js::Resources::Find<Shader>(L"SpriteAnimationShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = js::Resources::Find<Shader>(L"ParticleShader");
		js::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

#pragma endregion

#pragma region Sampler State
		// Sampler state
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(&samplerDesc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion

#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // 통짜 메쉬, 즉 그대로 채워준다.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;	// 뒷면 제거
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // 통짜 메쉬, 즉 그대로 채워준다.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;	// 앞면 제거
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID; // 통짜 메쉬, 즉 그대로 채워준다.
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;	// 제거안함
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME; // 그물형태
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;	// 뒷면 제거
		GetDevice()->CreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion

#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		// Less
		depthStencilDesc.DepthEnable = true;	// 깊이 체크를 할건지 안할건지.
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;		// 더 작은값을 그려주겠다.
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		// Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		// NoWrite
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		//None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion

#pragma region Blend State
		D3D11_BLEND_DESC blendDesc = {};
		//default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&blendDesc
			, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion


	}

	void LoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());
		Resources::Insert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear();

		// RECT
		vertexes.resize(4);
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Vertex Buffer
		mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);

		mesh->CreateVertexBuffer(vertexes.data(), vertexes.size());
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// RECT Debug Mesh
		std::shared_ptr<Mesh> rectDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugRect", rectDebug);
		rectDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->CreateIndexBuffer(indexes.data(), indexes.size());

		// Circle Debug Mesh
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			vertexes.push_back(center);
		}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}
		indexes.push_back(1);

		std::shared_ptr<Mesh> circleDebug = std::make_shared<Mesh>();
		Resources::Insert(L"DebugCircle", circleDebug);
		circleDebug->CreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->CreateIndexBuffer(indexes.data(), indexes.size());
		circleDebug->SetRadius(fRadius);
	}

	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Animatior] = new ConstantBuffer(eCBType::Animatior);
		constantBuffer[(UINT)eCBType::Animatior]->Create(sizeof(AnimatorCB));

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Reverse] = new ConstantBuffer(eCBType::Reverse);
		constantBuffer[(UINT)eCBType::Reverse]->Create(sizeof(SpriteReverseCB));

		// light structed buffer
		lightsBuffer = new StructedBuffer();
		lightsBuffer->Create(sizeof(LightAttribute), 2, eSRVTpye::None);
	}

	void LoadShader()
	{
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		js::Resources::Insert(L"TriangleShader", shader);

		shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		js::Resources::Insert(L"SpriteShader", shader);

		std::shared_ptr<Shader> spriteAniShader = std::make_shared<Shader>();
		spriteAniShader->Create(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->Create(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		js::Resources::Insert(L"SpriteAnimationShader", spriteAniShader);

		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		js::Resources::Insert(L"GridShader", gridShader);

		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->SetRSState(eRSType::WireframeNone);
		debugShader->SetDSState(eDSType::End);
		js::Resources::Insert(L"DebugShader", debugShader);

		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		js::Resources::Insert(L"PaintShader", paintShader);

		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		js::Resources::Insert(L"ParticleShader", particleShader);


	}

	void LoadTexture()
	{
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024,1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		Resources::Insert(L"PaintTexture", uavTexture);
	}

	void LoadMaterial()
	{
		std::shared_ptr<Shader> shader = Resources::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Shader> spriteAniShader = Resources::Find<Shader>(L"SpriteAnimationShader");

		std::shared_ptr<Texture> texture = Resources::Load<Texture>(L"Link", L"..\\Resources\\Texture\\link.png");
		std::shared_ptr<Material> spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetShader(shader);
		spriteMaterial->SetTexture(texture);
		Resources::Insert(L"SpriteMaterial", spriteMaterial);

		//std::shared_ptr<Texture> texture1 = Resources::Load<Texture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		std::shared_ptr<Texture> texture1 = Resources::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Material> spriteMaterial1 = std::make_shared<Material>();
		spriteMaterial1->SetShader(shader);
		spriteMaterial1->SetTexture(texture1);
		spriteMaterial1->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteMaterial02", spriteMaterial1);

		spriteMaterial1 = std::make_shared<Material>();
		spriteMaterial1->SetShader(spriteAniShader);
		spriteMaterial1->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"SpriteAnimationMaterial", spriteMaterial1);

		std::shared_ptr<Shader> gridShader = Resources::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetShader(gridShader);
		Resources::Insert(L"GridMaterial", gridMaterial);

		std::shared_ptr<Shader> debugShader = Resources::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetShader(debugShader);
		Resources::Insert(L"DebugMaterial", debugMaterial);

		shader = Resources::Find<Shader>(L"ParticleShader");
		spriteMaterial = std::make_shared<Material>();
		spriteMaterial->SetShader(shader);
		spriteMaterial->SetRenderingMode(eRenderingMode::Transparent);
		Resources::Insert(L"ParticleMaterial", spriteMaterial);


#pragma region TitleScene
		shader = Resources::Find<Shader>(L"SpriteShader");
		// Title Sky
		std::shared_ptr<Texture> titleTexture = Resources::Load<Texture>(L"TitleSky", L"..\\Resources\\Texture\\TitleScene\\title.png");
		std::shared_ptr<Material> titleMaterial = std::make_shared<Material>();
		titleMaterial->SetShader(shader);
		titleMaterial->SetTexture(titleTexture);
		Resources::Insert(L"TitleSkyMaterial", titleMaterial);

		// Title Cloud
		std::shared_ptr<Texture> titleCloudTexture = Resources::Load<Texture>(L"TitleCloud", L"..\\Resources\\Texture\\TitleScene\\startBackgroundCloud_800x800.bmp");
		std::shared_ptr<Material> titleCloudMaterial = std::make_shared<Material>();
		titleCloudMaterial->SetShader(shader);
		titleCloudMaterial->SetTexture(titleCloudTexture);
		Resources::Insert(L"TitleCloudMaterial", titleCloudMaterial);

		// Title MainRock
		std::shared_ptr<Texture> titleRockTexture = Resources::Load<Texture>(L"TitleMainRock", L"..\\Resources\\Texture\\TitleScene\\TitleSceneRock.png");
		std::shared_ptr<Material> titleRockMaterial = std::make_shared<Material>();
		titleRockMaterial->SetShader(shader);
		titleRockMaterial->SetTexture(titleRockTexture);
		Resources::Insert(L"TitleMainRockMaterial", titleRockMaterial);

		// Title OtusHouseTop
		std::shared_ptr<Texture> otusHouseTopTexture = Resources::Load<Texture>(L"OtusHouseTop", L"..\\Resources\\Texture\\TitleScene\\OtusHouseTop.png");
		std::shared_ptr<Material> otusHouseTopMaterial = std::make_shared<Material>();
		otusHouseTopMaterial->SetShader(shader);
		otusHouseTopMaterial->SetTexture(otusHouseTopTexture);
		Resources::Insert(L"OtusHouseTopMaterial", otusHouseTopMaterial);

		// Title OtusHouseMiddle
		std::shared_ptr<Texture> otusHouseMiddleTexture = Resources::Load<Texture>(L"OtusHouseMiddle", L"..\\Resources\\Texture\\TitleScene\\OtusHouseMiddle.png");
		std::shared_ptr<Material> otusHouseMiddleMaterial = std::make_shared<Material>();
		otusHouseMiddleMaterial->SetShader(shader);
		otusHouseMiddleMaterial->SetTexture(otusHouseMiddleTexture);
		Resources::Insert(L"OtusHouseMiddleMaterial", otusHouseMiddleMaterial);

		// Title OtusHouseTop
		std::shared_ptr<Texture> logoTexture = Resources::Load<Texture>(L"Logo", L"..\\Resources\\Texture\\TitleScene\\OwlboyLogo.png");
		std::shared_ptr<Material> logoMaterial = std::make_shared<Material>();
		logoMaterial->SetShader(shader);
		logoMaterial->SetTexture(logoTexture);
		Resources::Insert(L"LogoMaterial", logoMaterial);
#pragma endregion
#pragma region Tutorial
		// Tutorial
		std::shared_ptr<Texture> tutorialTexture = Resources::Load<Texture>(L"Tutorial", L"..\\Resources\\Texture\\Tutorial.bmp");
		std::shared_ptr<Material> tutorialMaterial = std::make_shared<Material>();
		tutorialMaterial->SetShader(shader);
		tutorialMaterial->SetTexture(tutorialTexture);
		Resources::Insert(L"TutorialMaterial", tutorialMaterial);
#pragma endregion
#pragma region HouseScene
		std::shared_ptr<Texture> houseTexture = Resources::Load<Texture>(L"House", L"..\\Resources\\Texture\\VellieScene\\Owlboyhouse.png");
		std::shared_ptr<Material> houseMaterial = std::make_shared<Material>();
		houseMaterial->SetShader(shader);
		houseMaterial->SetTexture(houseTexture);
		Resources::Insert(L"HouseMaterial", houseMaterial);
#pragma endregion

#pragma region VellieScene

		std::shared_ptr<Texture> vellieTexture = Resources::Load<Texture>(L"Vellie", L"..\\Resources\\Texture\\VellieScene\\Vellie.png");
		std::shared_ptr<Material> vellieMaterial = std::make_shared<Material>();
		vellieMaterial->SetShader(shader);
		vellieMaterial->SetTexture(vellieTexture);
		Resources::Insert(L"VellieMaterial", vellieMaterial);

		std::shared_ptr<Texture> vellieskyTexture = Resources::Load<Texture>(L"VellieSky", L"..\\Resources\\Texture\\VellieScene\\skyScreen.png");
		std::shared_ptr<Material> vellieskyMaterial = std::make_shared<Material>();
		vellieskyMaterial->SetShader(shader);
		vellieskyMaterial->SetTexture(vellieskyTexture);
		Resources::Insert(L"VellieSkyMaterial", vellieskyMaterial);

		std::shared_ptr<Texture>  bomboShopTexture = Resources::Load<Texture>(L"BomboShop", L"..\\Resources\\Texture\\VellieScene\\bomboShopFront1.png");
		std::shared_ptr<Material> bomboShopMaterial = std::make_shared<Material>();
		bomboShopMaterial->SetShader(shader);
		bomboShopMaterial->SetTexture(bomboShopTexture);
		Resources::Insert(L"BomboShopMaterial", bomboShopMaterial);

		std::shared_ptr<Texture>  bomboHouseTexture = Resources::Load<Texture>(L"BomboHouse", L"..\\Resources\\Texture\\VellieScene\\bomboHouse.png");
		std::shared_ptr<Material> bomboHouseMaterial = std::make_shared<Material>();
		bomboHouseMaterial->SetShader(shader);
		bomboHouseMaterial->SetTexture(bomboHouseTexture);
		Resources::Insert(L"BomboHouseMaterial", bomboHouseMaterial);

		std::shared_ptr<Texture>  canonTexture = Resources::Load<Texture>(L"Canon", L"..\\Resources\\Texture\\VellieScene\\Cannon.png");
		std::shared_ptr<Material> canonMaterial = std::make_shared<Material>();
		canonMaterial->SetShader(shader);
		canonMaterial->SetTexture(canonTexture);
		Resources::Insert(L"CanonMaterial", canonMaterial);

		std::shared_ptr<Texture>  canonBottomTexture = Resources::Load<Texture>(L"CanonBottom", L"..\\Resources\\Texture\\VellieScene\\caveSegment3.png");
		std::shared_ptr<Material> canonBottomMaterial = std::make_shared<Material>();
		canonBottomMaterial->SetShader(shader);
		canonBottomMaterial->SetTexture(canonBottomTexture);
		Resources::Insert(L"CanonBottomMaterial", canonBottomMaterial);

		std::shared_ptr<Texture>  otusHouseOutsideTexture = Resources::Load<Texture>(L"OtusHouseOutside", L"..\\Resources\\Texture\\VellieScene\\island01.png");
		std::shared_ptr<Material> otusHouseOutsideMaterial = std::make_shared<Material>();
		otusHouseOutsideMaterial->SetShader(shader);
		otusHouseOutsideMaterial->SetTexture(otusHouseOutsideTexture);
		Resources::Insert(L"OtusHouseOutsideMaterial", otusHouseOutsideMaterial);

		std::shared_ptr<Texture>  labTexture = Resources::Load<Texture>(L"Lab", L"..\\Resources\\Texture\\VellieScene\\Lab_island.png");
		std::shared_ptr<Material> labMaterial = std::make_shared<Material>();
		labMaterial->SetShader(shader);
		labMaterial->SetTexture(labTexture);
		Resources::Insert(L"LabMaterial", labMaterial);

		std::shared_ptr<Texture> cloud1Texture = Resources::Load<Texture>(L"Cloud1", L"..\\Resources\\Texture\\VellieScene\\cloud01.png");
		std::shared_ptr<Material> cloud1Material = std::make_shared<Material>();
		cloud1Material->SetShader(shader);
		cloud1Material->SetTexture(cloud1Texture);
		Resources::Insert(L"Cloud1Material", cloud1Material);

		std::shared_ptr<Texture> cloud2Texture = Resources::Load<Texture>(L"Cloud2", L"..\\Resources\\Texture\\VellieScene\\cloud02.png");
		std::shared_ptr<Material> cloud2Material = std::make_shared<Material>();
		cloud2Material->SetShader(shader);
		cloud2Material->SetTexture(cloud2Texture);
		Resources::Insert(L"Cloud2Material", cloud2Material);

		std::shared_ptr<Texture> cloud3Texture = Resources::Load<Texture>(L"Cloud3", L"..\\Resources\\Texture\\VellieScene\\cloud03.png");
		std::shared_ptr<Material> cloud3Material = std::make_shared<Material>();
		cloud3Material->SetShader(shader);
		cloud3Material->SetTexture(cloud3Texture);
		Resources::Insert(L"Cloud3Material", cloud3Material);
#pragma endregion
#pragma region DungeonScene
		std::shared_ptr<Texture> dundeonTexture = Resources::Load<Texture>(L"Dungeon", L"..\\Resources\\Texture\\dungeon.bmp");
		std::shared_ptr<Material> dungeonMaterial = std::make_shared<Material>();
		dungeonMaterial->SetShader(shader);
		dungeonMaterial->SetTexture(dundeonTexture);
		Resources::Insert(L"DungeonMaterial", dungeonMaterial);

		std::shared_ptr<Texture> testTexture = Resources::Load<Texture>(L"Test", L"..\\Resources\\Texture\\vellie.png");
		std::shared_ptr<Material> testMaterial = std::make_shared<Material>();
		testMaterial->SetShader(shader);
		testMaterial->SetTexture(testTexture);
		Resources::Insert(L"TestMaterial", testMaterial);
#pragma endregion

#pragma region BossScene
		// Boss Stage
		std::shared_ptr<Texture> bossBGTexture = Resources::Load<Texture>(L"BossStage", L"..\\Resources\\Texture\\BossStage.bmp");
		std::shared_ptr<Material> bossBGMaterial = std::make_shared<Material>();
		bossBGMaterial->SetShader(shader);
		bossBGMaterial->SetTexture(bossBGTexture);
		Resources::Insert(L"BossStageMaterial", bossBGMaterial);
#pragma endregion
#pragma region EndingScene
		// Ending Sky
		std::shared_ptr<Texture> endingTexture = Resources::Load<Texture>(L"Ending_Sky", L"..\\Resources\\Texture\\Ending_Sky.png");
		std::shared_ptr<Material> endingMaterial = std::make_shared<Material>();
		endingMaterial->SetShader(shader);
		endingMaterial->SetTexture(endingTexture);
		Resources::Insert(L"Ending_SkyMaterial", endingMaterial);
#pragma endregion

#pragma region UI
		// Coin 
		std::shared_ptr<Texture> coinTexture = Resources::Load<Texture>(L"Coin", L"..\\Resources\\Texture\\coin_15x17.png");
		std::shared_ptr<Material> coinMaterial = std::make_shared<Material>();
		coinMaterial->SetShader(shader);
		coinMaterial->SetTexture(coinTexture);
		Resources::Insert(L"CoinMaterial", coinMaterial);

		// Hp Bar Icon
		std::shared_ptr<Texture> otusHpIconTexture = Resources::Load<Texture>(L"OtusHpIcon", L"..\\Resources\\Texture\\gunnerIcon.png");
		std::shared_ptr<Material> otusHpIconMaterial = std::make_shared<Material>();
		otusHpIconMaterial->SetShader(shader);
		otusHpIconMaterial->SetTexture(otusHpIconTexture);
		Resources::Insert(L"OtusHpIconMaterial", otusHpIconMaterial);

		// Hp Bar Icon frame
		std::shared_ptr<Texture> otusHpframeTexture = Resources::Load<Texture>(L"OtusHpIconframe", L"..\\Resources\\Texture\\sprFrame_36x32.png");
		std::shared_ptr<Material> otusHpframeMaterial = std::make_shared<Material>();
		otusHpframeMaterial->SetShader(shader);
		otusHpframeMaterial->SetTexture(otusHpframeTexture);
		Resources::Insert(L"OtusHpIconframeMaterial", otusHpframeMaterial);

		// Otus Hp Bar
		std::shared_ptr<Texture> otusHpTexture = Resources::Load<Texture>(L"OtusHpBar", L"..\\Resources\\Texture\\hpBarFront.bmp");
		std::shared_ptr<Material> otusHpMaterial = std::make_shared<Material>();
		otusHpMaterial->SetShader(shader);
		otusHpMaterial->SetTexture(otusHpTexture);
		Resources::Insert(L"OtusHpBarMaterial", otusHpMaterial);

		// Boss Hp Bar
		std::shared_ptr<Texture>  bossHpTexture = Resources::Load<Texture>(L"BossHpBar", L"..\\Resources\\Texture\\bossBar.png");
		std::shared_ptr<Material> bossHpMaterial = std::make_shared<Material>();
		bossHpMaterial->SetShader(shader);
		bossHpMaterial->SetTexture(bossHpTexture);
		Resources::Insert(L"BossHpBarMaterial", bossHpMaterial);

		// Boss Hp Bar On
		std::shared_ptr<Texture>  bossHpOnTexture = Resources::Load<Texture>(L"BossHpBarOn", L"..\\Resources\\Texture\\bossBarOn.png");
		std::shared_ptr<Material> bossHpOnMaterial = std::make_shared<Material>();
		bossHpOnMaterial->SetShader(shader);
		bossHpOnMaterial->SetTexture(bossHpOnTexture);
		Resources::Insert(L"BossHpBarOnMaterial", bossHpOnMaterial);

		// Boss Hp Bar Off
		std::shared_ptr<Texture>  bossHpOffTexture = Resources::Load<Texture>(L"BossHpOffBar", L"..\\Resources\\Texture\\bossBarOff.png");
		std::shared_ptr<Material> bossHpOffMaterial = std::make_shared<Material>();
		bossHpOffMaterial->SetShader(shader);
		bossHpOffMaterial->SetTexture(bossHpOffTexture);
		Resources::Insert(L"BossHpBarOffMaterial", bossHpOffMaterial);


#pragma endregion

	}

	void Initialize()
	{

		LoadMesh();
		LoadBuffer();
		LoadShader();
		SetupState();
		LoadTexture();
		LoadMaterial();

	}
	void PushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}

	void BindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (Light* light : lights)
		{
			LightAttribute attribute = light->GetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->SetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->Bind(eShaderStage::VS, 13);
		lightsBuffer->Bind(eShaderStage::PS, 13);
	}

	void Render()
	{
		BindLights();

		for (Camera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->Render();
		}

		cameras.clear();
		lights.clear();
	}
	void renderer::Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}
}