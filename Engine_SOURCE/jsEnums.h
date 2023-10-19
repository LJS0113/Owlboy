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
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType
	{
		BG,
		Scenery,
		MouseCursor,
		Ground,
		Wall,
		Artifact,
		Grid,
		Player,
		Monster,
		PlayerAttack,
		AttackRange,
		PlayerBullet,
		MonsterBullet,
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
		ComputeShader,
		AudioClip,
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
		AttackRange,
		Ground,
		Wall,
		Door,
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