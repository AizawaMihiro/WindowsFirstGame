#pragma once
#include "GameObject.h"

class SceneManager :
	public GameObject
{
public:
	SceneManager();
	~SceneManager();
	void Initialize();
	void Update();
	void Draw();
	void Release();
};

