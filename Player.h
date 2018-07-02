#pragma once
#include "CharaObject.h"
#include "DeadMen.h"
#include "Camera.h"
#include "Game.h"
#include "GamePlayingScene.h"
#include <string>

class GamePlayingScene;
class Peripheral;
class Camera;


//�A�N�V�������ɂ���đ���̎��ɕ���ς���
enum class AttackType 
{
	non,//�������Ȃ�0
	punch,//�p���`
	kick,//�L�b�N
	sliding,//�X���C�f�B���O
	swing,//�X�E�B���O
	srush,//�X���b�V��
	shot//�e������
};

class Player : public CharaObject
{ 
	friend GamePlayingScene;
public:
	Player(Camera& cam);
	~Player();
	void Draw();
	void Updata(const Peripheral &p);
	//���n������
	//groundline���n�_��Y���W
	void OnGround(int groundline);
	void DebugDraw();

public:
	//�����o�֐��|�C���^
	void (Player::*updataer)(const Peripheral&);
	//���
	void NeutralUpdata(const Peripheral&);//�j���[�g�������
	void JumpUpdata(const Peripheral&);//�W�����v���
	void WalkUpdata(const Peripheral&);//�������
	void CrouchUpdata(const Peripheral&);//���Ⴊ�ݏ��
	void PunchUpdata(const Peripheral&);//�p���`���
	void KickUpdata(const Peripheral&);//�L�b�N���
	void DamageUpdata(const Peripheral&);//�_���[�W���
	void GroundUpdata(const Peripheral&);//���n���
	void SlidingUpdata(const Peripheral&);//�X���C�f�B���O���
	void RiderUpdata(const Peripheral&);
	void MutekiUpdata(const Peripheral&);
	void DrawPos();
	void Jump();
	void Rider();
	void Crouch();
	void Punch();
	void Kick();
	void Sliding();
	void onDamage();
	void Muteki();

	////�t���[���̃A�j���[�V������1�i�߂� true false

	bool isArial; //���ł��邩�ǂ���
	AttackType attackType;
	int PlayerImg;
	Rect _rect;
	Camera& camera;
private:
	int waitTimer;
	int damageSE;
	int SlidingSE;
	int PunchSE;
	int frametime;
	bool wait;
	bool MutekiFlag;
	//�J�������炷
};

//public�̓N���C�A���g�ł����ĂׂȂ�
//private�͂��Ԃ�ł����Ăяo���Ȃ�
//protected�͌p�������N���C�A���g�ł����ĂׂȂ�