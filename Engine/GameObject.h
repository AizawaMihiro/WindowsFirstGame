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
	void UpdateSub();
	void ReleaseSub();

	void SetPosition(XMFLOAT3 position);
	void SetPosition(float x, float y, float z);
	
	void KillMe() { isDead_ = true; }

	GameObject* GetRootJob();
	GameObject* FindChildObject(const string& name);
	GameObject* FindObject(const string& name);

	template <class T>
	GameObject* Instantiate(GameObject* parent)
	{
		T* obj = new T(parent);
		obj->Initialize();
		childList_.push_back(obj);
		return obj;
	}

private:
	bool isDead_;
};