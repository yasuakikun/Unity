#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
	GOImg = LoadGraph("img/gameover.png");
	updataer = &GameOverScene::Fadein;
	EndTime = 150;
}


GameOverScene::~GameOverScene()
{
}

void GameOverScene::Updata()
{
}

void GameOverScene::Updata(const Peripheral & p)
{
	(this->*updataer)(p);
	printf("ゲームオーバー\n");
}

void GameOverScene::Fadein(const Peripheral &p)
{
	ClearDrawScreen();
	static int blend = 0;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend++);	//フェードイン
	DrawGraph(180, 100, GOImg, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	ScreenFlip();
	printf("ゲームオーバー\n");
	if (p.IsTrigger(PAD_INPUT_8))
	{
		updataer = &GameOverScene::Fadeout;
	}

}

void GameOverScene::Fadeout(const Peripheral &)
{
	ClearDrawScreen();
	static int blend = 150;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, blend--);	//フェードイン
	DrawGraph(180, 100, GOImg, true);
	ScreenFlip();
	EndTime--;

	if (EndTime <= 0)
	{
		Game::Instance().ChangeScene(new TitleScene());
	}

}
