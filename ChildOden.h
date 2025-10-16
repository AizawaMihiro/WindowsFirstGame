#pragma once
#include "Engine/GameObject.h"

class Fbx;

class ChildOden :
    public GameObject
{
	Fbx* pFbx_;
public:
	ChildOden(GameObject* parent);
	~ChildOden();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

