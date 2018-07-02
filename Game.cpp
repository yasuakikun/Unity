#include "Game.h"
#include "Geometry.h"
#include "DxLib.h"
#include "Peripheral.h"
#include "Ground.h"
#include "Background.h"
#include "HUD.h"
#include "DeadMen.h"
#include "CollisionDetector.h"
#include "EnemyFactory.h"
#include "BatMen.h"
#include "Player.h"
#include "TitleScene.h"
#include "Scene.h"
#include <vector>
#include <memory>


using namespace std;

const Vector2f screensize = { 768,448 };

Game::Game()
{
	size.w = screensize.x;
	size.h = screensize.y;
}

Game::~Game()
{

}

//初期化処理
void Game::Initalize()
{
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(size.w, size.h, 32);
	DxLib::SetWindowTextA("スプラッターハウス");
	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);
	//DxLib::PlayMusic("Music/darkcity.mp3", DX_PLAYTYPE_BACK);


	FireImg = LoadGraph("img/blood.png");	//ファイヤー画像

	ChangeScene(new TitleScene());
}


//ループ
void Game::Run()
{
	Peripheral peripheral;
	while (DxLib::ProcessMessage() == 0) 
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{ 
			break;
		}
		ClearDrawScreen();
		peripheral.Update();
		_scene->Updata(peripheral);
		ScreenFlip();
	}
}


void Game::Tarminete()
{
	StopMusic();
	DxLib::DxLib_End();
}



const float Game::GetObjectScale() const
{
	return 2.0f;
}

void Game::ChangeScene(Scene *scene)
{
	_scene.reset(scene);
}

const ScreenSize& Game::GetScreenSize()
{
	return size;
}
