#include "Enemy.h"
#include "Engine/Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Oden.fbx");
	pCollider_ = new SphereCollider(3.0f);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
}

void Enemy::Release()
{
}
