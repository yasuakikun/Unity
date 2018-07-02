#include "Continue.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "GamePlayingScene.h"
#include "GameOverScene.h"



Continue::Continue()
{
	ContinueImg = LoadGraph("img/count.png");
	BotanImg = LoadGraph("img/Back.png");
	CountDown = 0;
}


Continue::~Continue()
{
}

void Continue::Updata()
{

}

void Continue::Updata(const Peripheral &p)
{
	ClearDrawScreen();

	//コンテニュー画像　切り取り
	DrawRectGraph(300, 150, 117 * ((CountDown++ / 90)% 5),159 * ((CountDown++ / 90) /  5) , 117, 159, ContinueImg, true, false);
	DrawGraph(250, 320, BotanImg, true);
	ScreenFlip();

	printf("コンテニュー\n");
	if (p.IsTrigger(PAD_INPUT_8) || CountDown >= 900)
	{
		Game::Instance().ChangeScene(new GameOverScene());
	}
}
