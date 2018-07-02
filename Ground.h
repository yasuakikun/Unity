#pragma once
#include "Player.h"
//地面を表すクラス
//なんかしらファイルから地形データを読み込んで、現在の座標に対応する地面のY座標を返す
class Ground
{
public:
	Ground();
	~Ground();
	void GroundDraw();
	int GetCurrentGroundY();
};

