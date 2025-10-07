#pragma once
#include "GameObject.h"

class RootJob : GameObject
{
public:
	RootJob(GameObject* parent);
	~RootJob();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};
