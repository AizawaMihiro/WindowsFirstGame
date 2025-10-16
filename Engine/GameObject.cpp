#include "GameObject.h"

GameObject::GameObject()
	:pParent_(nullptr)
{
}

GameObject::GameObject(GameObject* parent, const string& name)
	:pParent_(parent),objectName_(name)
{
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
	this->Update();
	//�q�I�u�W�F�N�g�̍X�V
	for (auto child : childList_)
	{
		child->UpdateSub();
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
