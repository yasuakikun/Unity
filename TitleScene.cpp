#include "TitleScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "GamePlayingScene.h"

TitleScene::TitleScene()
{
	TitleImg = LoadGraph("img/title.png");
	StartImg = LoadGraph("img/gamestart.png");
	wait = 60;
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	//最初の画面
	updataer = &TitleScene::Fadein;
	frametime = 0;
	StartTime = 150;
}


TitleScene::~TitleScene()
{
}

void TitleScene::Updata()
{
}


void TitleScene::Updata(const Peripheral &p)
{
	(this->*updataer)(p);

	printf("タイトル\n");
}

void TitleScene::Fadein(const Peripheral &p)
{
	frametime++;
	static int blend = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend++);	//フェードイン
	//画像表示
	DrawGraph(0, 0, TitleImg, true);
	//点滅させる
	if (frametime % 60 <= 30)
	{
		DrawGraph(170, 300, StartImg, true);
	}


	if (p.IsTrigger(PAD_INPUT_8))
	{
		updataer = &TitleScene::Fadeout;
	}
}

void TitleScene::Fadeout(const Peripheral &p)
{

	static int blend = 150;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,blend--);	//フェードアウト
	DrawGraph(0, 0, TitleImg, true);

	//バー描画
	DrawGraph(170, 300, StartImg, true);
	

	StartTime--;

	if (StartTime  == 0)
	{
		Game::Instance().ChangeScene(new GamePlayingScene());
	}
}
