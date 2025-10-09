#include "Player.h"
#include "Engine/Fbx.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), pFbx_(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pFbx_ = new Fbx();
	//本来はここでFbxのnullptrチェックをするべき
	pFbx_->Load("Oden.fbx");
	transform_.scale_.x = 0.7f;
	transform_.scale_.y = 0.7f;
	transform_.scale_.z = 0.7f;
}

void Player::Update()
{
	transform_.rotate_.y += 1.0f;
}

void Player::Draw()
{
	if (pFbx_)
	{
		pFbx_->Draw(transform_);
	}
}

void Player::Release()
{
	if (pFbx_)
	{
		pFbx_->Release();
		delete pFbx_;
		pFbx_ = nullptr;
	}
}
