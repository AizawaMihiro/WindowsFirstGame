#include "TestScene.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent, "TestScene")
{
	hModel_ = Model::Load("cube.fbx");
	assert(hModel_ >= 0);
	transform_.position_.y = -2.0f;
}

TestScene::~TestScene()
{
}

void TestScene::Initialize()
{
}

void TestScene::Update()
{
	transform_.rotate_.y += 2.0f;

	//�X�y�[�X�L�[�������ꂽ��SceneManager���擾
	//�����ăV�[����؂�ւ���
	if (Input::IsKeyDown(DIK_SPACE))
	{
		GameObject* sceneManager = FindObject("SceneManager");
		if (sceneManager)
		{
			((SceneManager*)sceneManager)->ChangeScene(SCENE_ID_PLAY);
		}
	}

}

void TestScene::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TestScene::Release()
{
}
