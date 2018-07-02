#pragma once
#include "Peripheral.h"
//シーン管理のための基底クラス
//純粋仮想クラス
class Scene
{
public:
	Scene();
	virtual ~Scene();
	//シーン更新を行う
	//純粋仮想関数
	virtual	void Updata(const Peripheral &p) =0;
};

