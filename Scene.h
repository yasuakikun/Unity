#pragma once
#include "Peripheral.h"
//�V�[���Ǘ��̂��߂̊��N���X
//�������z�N���X
class Scene
{
public:
	Scene();
	virtual ~Scene();
	//�V�[���X�V���s��
	//�������z�֐�
	virtual	void Updata(const Peripheral &p) =0;
};

