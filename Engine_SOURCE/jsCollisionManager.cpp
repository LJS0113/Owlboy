#include "jsCollisionManager.h"
#include "jsScene.h"
#include "jsSceneManager.h"
#include "jsLayer.h"
#include "jsGameObject.h"
#include "jsCollider2D.h"
#include "jsResources.h"
#include "jsMesh.h"

namespace js
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::Update()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[row] == true)
				{
					LayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* activeScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts = activeScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights = activeScene->GetLayer(right).GetGameObjects();

		for (GameObject* leftObj : lefts)
		{
			Collider2D* leftCol = leftObj->GetComponent<Collider2D>();
			if (leftCol == nullptr)
				continue;
			if (leftObj->GetState() != GameObject::eState::Active)
				continue;

			for (GameObject* rightObj : rights)
			{
				Collider2D* rightCol = rightObj->GetComponent<Collider2D>();
				if (rightCol == nullptr)
					continue;
				if (rightObj->GetState() != GameObject::eState::Active)
					continue;
				if (left == right)
					continue;
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->GetColliderID();
		id.right = right->GetColliderID();

		// 충돌정보를 가져온다.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (Intersect(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				// 최초 충돌
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			}
			else
			{
				// 충돌 중
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌X
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false;
			}
		}

	}

	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		// 네모 네모 충돌
		// 분리축 이론

		// To do... (숙제)
		// 분리축이 어렵다 하시는분들은

		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector3 leftAxis[2] = { leftTr->Right(), leftTr->Up() };
		Vector3 rightAxis[2] = { rightTr->Right(), rightTr->Up() };

		Vector3 diffLen = leftTr->GetPosition() - rightTr->GetPosition();

		if (leftAxis[0] == Vector3::Zero) return false;

		for (int i = 0; i < 2; ++i)
		{
			Vector3 axisX = leftAxis[i];

			float distance = abs(diffLen.Dot(axisX));
			float diff = 0.f;
			diff += abs(axisX.Dot(leftTr->Up() * leftTr->GetScale().y * 0.5f));
			diff += abs(axisX.Dot(leftTr->Right() * leftTr->GetScale().x * 0.5f));
			diff += abs(axisX.Dot(rightTr->Up() * rightTr->GetScale().y * 0.5f));
			diff += abs(axisX.Dot(rightTr->Right() * rightTr->GetScale().x * 0.5f));

			if (diff < distance)
				return false;
		}

		for (int i = 0; i < 2; ++i)
		{
			Vector3 axisX = rightAxis[i];

			float distance = abs(diffLen.Dot(axisX));
			float diff = 0.f;
			diff += abs(axisX.Dot(leftTr->Up() * leftTr->GetScale().y * 0.5f));
			diff += abs(axisX.Dot(leftTr->Right() * leftTr->GetScale().x * 0.5f));
			diff += abs(axisX.Dot(rightTr->Up() * rightTr->GetScale().y * 0.5f));
			diff += abs(axisX.Dot(rightTr->Right() * rightTr->GetScale().x * 0.5f));

			if (diff < distance)
				return false;
		}

		// 원 - 원 충돌
		leftTr = left->GetOwner()->GetComponent<Transform>();
		rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector3 leftPos = leftTr->GetPosition();
		Vector3 rightPos = rightTr->GetPosition();

		std::shared_ptr<Mesh> debugMesh = Resources::Find<Mesh>(L"DebugCircle");
		float radius = debugMesh->GetRadius();
		float leftRadius = radius * leftTr->GetScale().x;
		float rightRadius = radius * rightTr->GetScale().x;


		float distance = pow(abs(leftPos.x - rightPos.x), 2) + pow(abs(leftPos.y - rightPos.y), 2);
		if (distance <= leftRadius + rightRadius)
			return true;

		return false;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}

}