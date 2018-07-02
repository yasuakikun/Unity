#pragma once
class Peripheral
{
public:
	Peripheral();
	~Peripheral();

	//const bool 
		//
	//const bool IsTrigger() const;
	//特定のボタンが押されている。
	//入力したいボタン
	bool IsPressing(int button)const;


	bool IsTrigger(int button)const;
	//入力更新、毎フレーム更新する
	void Update();
private:
	int padState;//現在の入力情報
	int lastpadState;//直前のフレーム入力状態

};

