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
	 //î•ñXV
	 void Update();
	 //”wŒi•`‰æ
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
	 //‚´‚Ğ‚å‚¤
	 Postion2f pos;
};

