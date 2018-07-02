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
	 //���X�V
	 void Update();
	 //�w�i�`��
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
	 //���Ђ傤
	 Postion2f pos;
};

