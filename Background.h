#pragma once
#include "Geometry.h"
#include "Camera.h"
#include "CharaObject.h"

class Camera;
class Background
{
public:
	Background(Camera& cam);
	 ~Background();
	 //情報更新
	 void Update();
	 //背景描画
	 void Draw();
private:
	int BarTopH;
	int BarButtonH;

	int score;
	int bgImg1;
	int bgImg2;

	 int haikeiImg;
	 int haikei_turn_Img;
	 Camera& camera;
	 //ざひょう
	 Postion2f pos;
};

