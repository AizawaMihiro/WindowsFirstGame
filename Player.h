#pragma once
#include "Engine/GameObject.h"

class Fbx;
class ChildOden;

class Player :
    public GameObject
{
	Fbx* pFbx_;
	ChildOden* pRChildOden_;
	ChildOden* pLChildOden_;

public:
	Player(GameObject* parent);
	~Player();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

