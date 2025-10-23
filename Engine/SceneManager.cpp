#include "SceneManager.h"
#include "Direct3D.h"
#include "../Playscene.h"
#include "../TestScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent, "SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	if (currentSceneID_ != nextSceneID_)
	{
		//�V�[���؂�ւ�����
		auto scene = childList_.front();//���݂̃V�[���擾
		scene->ReleaseSub();//�q�I�u�W�F�N�g���
		SAFE_DELETE(scene);//�V�[���I�u�W�F�N�g�폜
		childList_.clear();//�q�I�u�W�F�N�g���X�g�N���A


		switch (nextSceneID_)
		{
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);
			break;
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);
			break;
		case SCENE_ID_MAX:
			break;
		default:
			break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}

void SceneManager::ChangeScene(SCENE_ID nextSceneID)
{
	nextSceneID_ = nextSceneID;
}
