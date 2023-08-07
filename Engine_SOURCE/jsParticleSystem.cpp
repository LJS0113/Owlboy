#include "jsParticleSystem.h"
#include "jsMesh.h"
#include "jsMaterial.h"
#include "jsResources.h"
#include "jsTransform.h"
#include "jsGameObject.h"


namespace js
{
	ParticleSystem::ParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
	{
		std::shared_ptr<Mesh> mesh = Resources::Find<Mesh>(L"PointMesh");
		SetMesh(mesh);

		std::shared_ptr<Material> material= Resources::Find<Material>(L"ParticleMaterial");
		SetMaterial(material);

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			pos.x += rand() % 20;
			pos.y += rand() % 10;

			int sign = rand() % 2;
			if(sign == 0)
				pos.x *= -1.0f;

			sign = rand() % 2;
			if(sign == 0)
				pos.y *= -1.0f;

			particles[i].position = pos;
			particles[i].active = 1;
		}

		mBuffer = new graphics::StructedBuffer();
		mBuffer->Create(sizeof(Particle), 1000, eSRVTpye::None);
		mBuffer->SetData(particles, 1000);
	}

	ParticleSystem::~ParticleSystem()
	{
	}

	void ParticleSystem::Initialize()
	{
	}

	void ParticleSystem::Update()
	{
	}

	void ParticleSystem::LateUpdate()
	{
	}

	void ParticleSystem::Render()
	{
		GetOwner()->GetComponent<Transform>()->BindConstantBuffer();
		mBuffer->Bind(eShaderStage::VS, 14);
		mBuffer->Bind(eShaderStage::GS, 14);
		mBuffer->Bind(eShaderStage::PS, 14);

		GetMaterial()->Binds();
		GetMesh()->RenderInstanced(1000);
	}

}