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
	//�����o�֐��|�C���^
	void(TitleScene::*updataer)(const Peripheral&);
	void Fadein(const Peripheral &);
	void Fadeout(const Peripheral &);
private:
	//�^�C�g���摜
	int TitleImg;
	//�X�^�[�g�摜
	int StartImg;
	//�t�F�[�h�p�^�C�}
	int wait;
	//�t���[���^�C�}
	int frametime;
	//�X�^�[�g�^�C��
	int StartTime;
};

