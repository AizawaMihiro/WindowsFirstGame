#include "GameObject.h"
#include <Windows.h>

GameObject::GameObject()
	:pParent_(nullptr), isDead_(false)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	:pParent_(parent), objectName_(name), isDead_(false)
{
	if (parent != nullptr)
	{
		transform_.pParent_ = &parent->transform_;
	}
}

GameObject::~GameObject()
{
}

void GameObject::DrawSub()
{
	this->Draw();

	//子オブジェクトの描画
	for (auto child : childList_)
	{
		child->DrawSub();
	}

	//for (auto itr = childList_.begin(); itr != childList_.end() ; itr++)
}

void GameObject::UpdateSub()
{
	transform_.Calclation();
	this->Update();

	//RoundRobin():

	//子オブジェクトの更新
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

	//削除フラグが立っているオブジェクトを削除
	for (auto itr = childList_.begin() ;itr != childList_.end();)
	{
		if ((*itr)->isDead_)
		{
			(*itr)->ReleaseSub();
			delete (*itr);
			itr = childList_.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

void GameObject::ReleaseSub()
{
	this->Release();
	//子オブジェクトの解放
	for (auto child : childList_)
	{
		child->ReleaseSub();
	}
	childList_.clear();
}

void GameObject::SetPosition(XMFLOAT3 position)
{
	transform_.position_ = position;
}

void GameObject::SetPosition(float x, float y, float z)
{
	transform_.position_ = XMFLOAT3(x, y, z);
}

GameObject* GameObject::GetRootJob()
{
	if (pParent_ == nullptr)
	{
		return this;
	}
	else
	{
		return pParent_->GetRootJob();
	}
}

GameObject* GameObject::FindChildObject(const string& name)
{
	if (this->objectName_ == name)
	{
		return this;//自分自身を返す
	}
	else
	{
		for (auto child : childList_)
		{
			GameObject* foundObject = child->FindChildObject(name);
			if (foundObject != nullptr)
			{
				return foundObject;
			}
		}
	}
	return nullptr;
}

GameObject* GameObject::FindObject(const string& name)
{
	GameObject* rootJob = GetRootJob();
	GameObject* foundObject = rootJob->FindChildObject(name);
	return foundObject;
}

void GameObject::AddCollider(SphereCollider* pCollider)
{
	pCollider_ = pCollider;
}

void GameObject::Collision(GameObject* pTarget)
{
	//this->pColliderとpTerget->pColliderが重なっているか確認する
	float thisR = this->pCollider_->GetRadius();
	float tarR = pTarget->pCollider_->GetRadius();
	float hitLength = (thisR + tarR) * (thisR + tarR);//距離の二乗

	XMFLOAT3 thisP = this->transform_.position_;
	XMFLOAT3 tarP = pTarget->transform_.position_;
	float dist = (thisP.x + tarP.x) * (thisP.x + tarP.x) + (thisP.y + tarP.y) * (thisP.y + tarP.y) + (thisP.z + tarP.z) * (thisP.z + tarP.z);
	if (hitLength >= dist)
	{
		//当たった際のリアクション
		MessageBox(0, "Cllide", "Collider", MB_OK);
	}

}

void GameObject::RoundRobin(GameObject* pTarget)
{
	//自分にコライダーがなければreturn
	//当たり判定ののち子オブジェクトとも当たり判定をする

	if (pCollider_ == nullptr)
	{
		return;
	}
	if (pTarget->pCollider_ != nullptr)
	{
		Collision(this);
		for (auto& itr : pTarget->childList_)
		{
			RoundRobin(itr);
		}
	}
}
