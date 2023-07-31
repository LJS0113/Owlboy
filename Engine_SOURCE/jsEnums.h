#pragma once

namespace js::enums
{
	enum class eComponentType
	{
		None,
		Transform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		RigidBody,
		Script,
		Light,
		Camera,
		End,
	};

	enum class eLayerType
	{
		BG,
		Ground,
		Grid,
		Player,
		Monster,
		Light,
		Camera,
		UI,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};

	enum class eColliderOwner
	{
		None,
		Player,
		Monster,
		Ground,
		Bullet,
		UI,
		End,
	};

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End,
	};
}