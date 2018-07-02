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
	//�t�H�[�J�X���ׂ��L�����N�^�[�I�u�W�F�N�g���Z�b�g
	void SetFocus(std::shared_ptr<CharaObject> c);

	//�J�����̕␳
	Postion2f CalculatePosition(Postion2f cpos);

	//�J�����̍��W��Ԃ�
	const Postion2f& GetPostion()const;

	//���݌����Ă���͈͂�Ԃ�
	Rect& GetViewPort();

private:
	std::weak_ptr<CharaObject> focus;
	Postion2f pos;
	const Game& game;
	const Stage& stage;	//�X�e�[�W���
	Rect rect;

	//const�Q�Ɓ@�����Ƃ��ēn������̓������[�R�s�[������A�T�C�Y���y�����邽��
	//�|�C���^�̏ꍇ�A���ŏ��������邩��|�C���^�œn��
	//����const�@���g�����������Ȃ����߁A�o�O���o���Ȃ��悤�ɂ��邽�߂̕s�莌
	//�ʒu��␳����B
	//�d�Ȃ��Ă�ԂԂ��
	//vovo

};

