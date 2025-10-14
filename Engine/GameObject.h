#pragma once

#include <string>
#include "Transform.h"
#include <list>

using std::string;
using std::list;

class GameObject
{
protected:
	list<GameObject *> childList_;
	Transform	transform_;
	GameObject*	pParent_;
	string	objectName_;

public:
	GameObject();
	GameObject(GameObject* parent, const string& name);
	virtual ~GameObject();

	virtual void Initialize() =0;
	virtual void Update() =0;
	virtual void Draw() =0;
	virtual void Release() =0;
	void DrawSub();
	template <class T>
	void Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}
};