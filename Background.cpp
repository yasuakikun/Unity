#include "Background.h"
#include "DxLib.h"
#define BACK_SIZE_X 574

const Vector2 bg_size = { 576, 488 };

Background::Background(Camera& cam) :camera(cam)
{
	haikeiImg = LoadGraph("img/splatterhouse.png");	//�w�i�摜
	haikei_turn_Img = haikeiImg;
	bgImg1 = LoadGraph("img/bar_top.png"); //�X�R�A�o�[
	bgImg2 = LoadGraph("img/bar_bottom_bk.png");//���C�t�o�[
}


Background::~Background()
{
	DeleteGraph(haikeiImg);
}

void Background::Update()
{

}

void Background::Draw(void)
{ 
	auto scroll = camera.GetViewPort().Left();	//���[�X�N���[���l
	scroll %= 1152;
	DrawRotaGraph(0 - scroll, 216, 1.0f, 0.0f, haikeiImg, false, true);
	DrawRotaGraph(576 - scroll, 216, 1.0f, 0.0f, haikei_turn_Img, false);
	DrawRotaGraph(1152 - scroll, 216, 1.0f, 0.0f, haikeiImg, false, true);
	DrawRotaGraph(1152 + 576 - scroll, 216, 1.0f, 0.0f,haikei_turn_Img, false);

	DxLib::DrawGraph(0, 0, bgImg1, true);
	DxLib::DrawGraph(0, 448 - 64, bgImg2, true);
}
