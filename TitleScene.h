#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();
	void Updata();
	void Updata(const Peripheral &);
	//メンバ関数ポインタ
	void(TitleScene::*updataer)(const Peripheral&);
	void Fadein(const Peripheral &);
	void Fadeout(const Peripheral &);
private:
	//タイトル画像
	int TitleImg;
	//スタート画像
	int StartImg;
	//フェード用タイマ
	int wait;
	//フレームタイマ
	int frametime;
	//スタートタイム
	int StartTime;
};

