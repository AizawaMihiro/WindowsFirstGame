#include "GameObject.h"

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

	//�q�I�u�W�F�N�g�̕`��
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
	//�q�I�u�W�F�N�g�̍X�V
	for (auto child : childList_)
	{
		child->UpdateSub();
	}

	//�폜�t���O�������Ă���I�u�W�F�N�g���폜
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
	//�q�I�u�W�F�N�g�̉��
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
