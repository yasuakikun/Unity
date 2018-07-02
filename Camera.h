#pragma once
#include "CharaObject.h"
#include "Geometry.h"
#include "Stage.h"
#include <memory>

class Game;
class CharaObject;
class Stage;

class Camera
{
public:
	Camera(const Stage& _stage);
	~Camera();
	void Updata();
	//フォーカスすべきキャラクターオブジェクトをセット
	void SetFocus(std::shared_ptr<CharaObject> c);

	//カメラの補正
	Postion2f CalculatePosition(Postion2f cpos);

	//カメラの座標を返す
	const Postion2f& GetPostion()const;

	//現在見えている範囲を返す
	Rect& GetViewPort();

private:
	std::weak_ptr<CharaObject> focus;
	Postion2f pos;
	const Game& game;
	const Stage& stage;	//ステージ情報
	Rect rect;

	//const参照　引数として渡したやつはメモリーコピーが入る、サイズを軽減するため
	//ポインタの場合、中で書き換えるからポインタで渡す
	//後ろのconst　中身を書き換えないため、バグを出さないようにするための不定詞
	//位置を補正する。
	//重なってるぶぶんで
	//vovo

};

