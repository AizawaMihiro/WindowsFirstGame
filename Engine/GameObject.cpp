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
		child->Draw();
		child->DrawSub();
	}

	//for (auto itr = childList_.begin(); itr != childList_.end() ; itr++)
}
