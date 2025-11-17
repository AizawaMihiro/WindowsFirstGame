#include "PlayScene.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Engine//Input.h"
#include "Engine/SceneManager.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	//Player¶¬
	//Player* pPlayer = new Player(this);
	//pPlayer->Initialize();
	//childList_.push_back(pPlayer);

	Instantiate<Player>(this);
	Instantiate<Enemy>(this);
}

void PlayScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		Instantiate<Bullet>(this);
	}

	GameObject* enemy = FindObject("Enemy");

	if (enemy == nullptr && Input::IsKeyDown(DIK_C))
	{
		GameObject* sceneManager = FindObject("SceneManager");
		if (sceneManager)
		{
			((SceneManager*)sceneManager)->ChangeScene(SCENE_ID_CLEAR);
		}
	}
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
