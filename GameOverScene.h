#pragma once
#include "Scene.h"
#include "Peripheral.h"
#include "TitleScene.h"
#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "Continue.h"
#include "GamePlayingScene.h"

class GameOverScene :
	public Scene
{
public:
	GameOverScene();
	~GameOverScene();
	void Updata();
	void Updata(const Peripheral&);
	//メンバ関数ポインタ
	void(GameOverScene::*updataer)(const Peripheral&);
	void Fadein(const Peripheral &);
	void Fadeout(const Peripheral &);
private:
	int GOImg;
	int EndTime;
};

