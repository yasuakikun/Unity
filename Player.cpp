#include "Player.h"
#include "DxLib.h"
#include "Peripheral.h"
#include <cassert>
#include "Game.h"

const float g = 0.5f;
const float vel_x = 2.0f;
const char *action_path = "action/player.act";


Player::Player(Camera& cam) : CharaObject(),camera(cam), isArial(false), waitTimer(0), wait(false),MutekiFlag(false)
{
	currentActionName = "Walk";
	ReedActionFile(action_path);
	PlayerImg = LoadGraph(actionData.ImgFilePath.c_str());	//�L�����摜
	damageSE = LoadSoundMem("se/p_damage.wav");
	SlidingSE = LoadSoundMem("se/sliding.mp3");
	PunchSE = LoadSoundMem("se/punch-swing.mp3");
	pos = { 10.0f,340.0f };
	frametime = 0;


	//�����o�֐��|�C���^
	updataer = &Player::NeutralUpdata;

}

Player::~Player()
{
	DeleteGraph(PlayerImg);
}

void Player::Draw()
{
	Game & game = Game::Instance();
	//�ǂݍ���
	auto  actInfo = actionData.actInfo[currentActionName];
	auto  cut = actInfo.cuts[currentCutIndex];
	auto  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;


	/*auto right = camera.GetViewPort().Right();
	auto left =	 camera.GetViewPort().Left();
	pos.x = min(max(pos.x, left),right);*/

	Postion2f campos = camera.CalculatePosition(pos);

	//��]������g��ł���
	DrawRectRotaGraph2(campos.x,campos.y,
						rc.Left(),rc.Top(),
						rc.Wight(),rc.Height(),
						centerX,cut.center.y,
						Game::Instance().GetObjectScale(), 
						0, PlayerImg, 
						true, 
						isTrun);//�L�����`��
	DebugDraw();
}

void Player::Updata(const Peripheral &p)
{
	(this->*updataer)(p);

	pos += vel;

	//////�n�ʂ��痣��Ă�����d�͂��󂯂�
	if (isArial) 
	{
		vel.y += g;
	}
	else {
	}
}

void Player::NeutralUpdata(const Peripheral &p)
{
	vel.x = 0;
	//�����A�j���[�V�������Đ�
	if (p.IsPressing(PAD_INPUT_RIGHT)){
		pos.x += 2;
		isTrun = false;
		updataer = &Player::WalkUpdata;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT)){
		pos.x -= 2;
		isTrun = true;
		updataer = &Player::WalkUpdata;
	}
	if (p.IsTrigger(PAD_INPUT_DOWN))
	{
		Crouch();
	}

	if (p.IsTrigger(PAD_INPUT_2))
	{
		Punch();
	}

	if (!isArial)
	{
		if (p.IsTrigger(PAD_INPUT_1))
		{
			Jump();
		}
	}
}

void Player::WalkUpdata(const Peripheral &p)
{
	vel.x = 0;
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		pos.x += 2;
		isTrun = false;
	}
	else if (p.IsPressing(PAD_INPUT_LEFT))
	{
		pos.x -= 2;
		isTrun = true;
	}
	else
	{
		updataer = &Player::NeutralUpdata;
	}

	ProceedAnimationFrame();

	if (!isArial)
	{
		if (p.IsTrigger(PAD_INPUT_1))
		{
			Jump();
		}
	}

	if (p.IsTrigger(PAD_INPUT_2))
	{
		Punch();
	}
}

void Player::Jump()
{
	vel.y = -12.0f;
	isArial = true;
	ChangeAction("Jump");
	updataer = &Player::JumpUpdata;
}

void Player::JumpUpdata(const Peripheral &p)
{
	//duration=�J�b�g�̒���

	ProceedAnimationFrame();
	
		//�W�����v�̍Đ�
		if (p.IsPressing(PAD_INPUT_RIGHT)) {
			pos.x += vel_x;
			isTrun = false;
		}
		else if (p.IsPressing(PAD_INPUT_LEFT)) {
			pos.x -= vel_x;
			isTrun = true;
		}

		if (p.IsPressing(PAD_INPUT_DOWN))
		{
			ChangeAction("Crouch");
			updataer = &Player::CrouchUpdata;
		}

		if (isArial)
		{
			if (p.IsTrigger(PAD_INPUT_2))
			{
				Punch();
			}
		}
		if (p.IsPressing(PAD_INPUT_3))
		{
			Rider();
		}
}

void Player::Crouch()
{
	ChangeAction("Crouch");
	updataer = &Player::CrouchUpdata;

}

void Player::CrouchUpdata(const Peripheral &p)
{
	ProceedAnimationFrame();
	if (p.IsPressing(PAD_INPUT_RIGHT))
	{
		isTrun = false;

	}
	else if (p.IsTrigger(PAD_INPUT_LEFT))
	{
		isTrun = true;
	}

	if (!p.IsPressing(PAD_INPUT_DOWN))
	{
		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
	}
	else
	{
		if (p.IsTrigger(PAD_INPUT_2))
		{
			Kick();
		}
	}

	if (!isArial) 
	{
		if (p.IsTrigger(PAD_INPUT_1))
		{
			Jump();
		}
	}
}

void Player::Punch()
{
	ChangeAction("Punch");
	updataer = &Player::PunchUpdata;
	PlaySoundMem(PunchSE,DX_PLAYTYPE_BACK);
}

void Player::PunchUpdata(const Peripheral &p)
{
	if (ProceedAnimationFrame())
	{
		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
	}
}

void Player::OnGround(int groundline)
{
	vel.y = 0;
	pos.y = groundline;
	isArial = false;
	ChangeAction("Ground");
	updataer = &Player::GroundUpdata;
}


void Player::GroundUpdata(const Peripheral &p)
{
	if (ProceedAnimationFrame())
	{
		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
	}
	if (p.IsPressing(PAD_INPUT_DOWN))
	{
		if (p.IsTrigger(PAD_INPUT_2))
		{
			Sliding();
		}
	}
}

void Player::Kick()
{
	ChangeAction("Kick");
	updataer = &Player::KickUpdata;

}

void Player::KickUpdata(const Peripheral &)
{
	if (ProceedAnimationFrame())
	{
		ChangeAction("Crouch");
		updataer = &Player::CrouchUpdata;
	}

}

void Player::Sliding()
{
	ChangeAction("Sliding");
	updataer = &Player::SlidingUpdata;
	PlaySoundMem(SlidingSE, DX_PLAYTYPE_BACK);
	
}

void Player::SlidingUpdata(const Peripheral &)
{
	vel.x = 0;
	if (ProceedAnimationFrame()) 
	{
		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
		return;
	}
	//�Q�l���Z�q false��������-5.0f,true��������5.0f
	vel.x = isTrun ? -5.0f : 5.0f;
}

void Player::onDamage()
{
	ChangeAction("Damage");
	updataer = &Player::DamageUpdata;
	waitTimer = 30;
	PlaySoundMem(damageSE, DX_PLAYTYPE_BACK);
}

void Player::DamageUpdata(const Peripheral &p)
{
	vel.x = 0;
	frametime++;
	//�A�j���[�V�������I�������changeacion��������

	if (ProceedAnimationFrame())
	{

		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
		return;
	}
	
	//��������Ƃ��Avel�̒l���ړ�������
	vel.x = isTrun ? 3.0f :	-3.0f;
}

void Player::Rider()
{
	ChangeAction("Sliding");
	updataer = &Player::RiderUpdata;
	PlaySoundMem(SlidingSE, DX_PLAYTYPE_BACK);
}

void Player::RiderUpdata(const Peripheral &p)
{
	vel.x = 0;
	if (ProceedAnimationFrame())
	{
		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
		return;
	}
	//�Q�l���Z�q false��������-5.0f,true��������5.0f
	vel.x = isTrun ? -3.0f : 3.0f;
}

void Player::Muteki()
{

}


void Player::MutekiUpdata(const Peripheral &p)
{
	//�_���[�W��������Ƃ��ɖ��G����
}

void Player::DrawPos()
{
	DrawFormatString(100, 150, GetColor(255, 255, 0), "%d",pos.x);
	DrawFormatString(100, 170, GetColor(255, 255, 0), "%d",pos.y);
}

void Player::DebugDraw()
{
	Game& game = Game::Instance();
	Postion2f campos = camera.CalculatePosition(pos);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (64));
	//���S���W
	DrawBox(campos.x - 2, campos.y - 2, campos.x + 2, campos.y + 2, 0xffffffff, true);
	//�������`
	auto&  actInfo = actionData.actInfo[currentActionName];
	auto&  cut = actInfo.cuts[currentCutIndex];
	auto&  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;
	//���S�̒��𓧂�������
	for (auto& act : cut.actrects)
	{
		Rect rc = act.rc;
		rc = GetActuralRectForAction(rc);
		DrawBox(rc.Left(), rc.Top(), rc.Right(), rc.Botton(), 0xfffffffff,true);

	}
	DxLib::SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, (0));
}