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

	//子オブジェクトの描画
	for (auto child : childList_)
	{
		child->DrawSub();
	}

	//for (auto itr = childList_.begin(); itr != childList_.end() ; itr++)
}

void GameObject::UpdateSub()
{
	this->Update();
	//子オブジェクトの更新
	for (auto child : childList_)
	{
		child->UpdateSub();
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
