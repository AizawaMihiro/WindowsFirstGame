#include "Bullet.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet")
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	pFbx_ = new Fbx;
	pFbx_->Load("Bulet.fbx");
	transform_.position_ = FindObject("Player")->GetPosition();
	transform_.scale_ = { 0.5f,0.5f,0.5f };

	SphereCollider* col = new SphereCollider(0.25f);
	AddCollider(col);
}

void Bullet::Update()
{
	transform_.position_.z += 0.2f;
	if (transform_.position_.z >= 75.0f) {
		SetDeadFlag(true);
	}
}

void Bullet::Draw()
{
	pFbx_->Draw(transform_);
}

void Bullet::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}

void Bullet::onCollision(GameObject* pTerget)
{
	if (pTerget->GetObjectName() == "Enemy")
	{
		SetDeadFlag(true);
	}
}
