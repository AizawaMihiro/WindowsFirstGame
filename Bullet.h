#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fbx.h"

class Bullet :
    public GameObject
{
public:
    Bullet(GameObject* parent);
    ~Bullet();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
    void onCollision(GameObject* pTerget) override;
private:
    Fbx* pFbx_;
};

