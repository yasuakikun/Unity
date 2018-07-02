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
	PlayerImg = LoadGraph(actionData.ImgFilePath.c_str());	//キャラ画像
	damageSE = LoadSoundMem("se/p_damage.wav");
	SlidingSE = LoadSoundMem("se/sliding.mp3");
	PunchSE = LoadSoundMem("se/punch-swing.mp3");
	pos = { 10.0f,340.0f };
	frametime = 0;


	//メンバ関数ポインタ
	updataer = &Player::NeutralUpdata;

}

Player::~Player()
{
	DeleteGraph(PlayerImg);
}

void Player::Draw()
{
	Game & game = Game::Instance();
	//読み込み
	auto  actInfo = actionData.actInfo[currentActionName];
	auto  cut = actInfo.cuts[currentCutIndex];
	auto  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;


	/*auto right = camera.GetViewPort().Right();
	auto left =	 camera.GetViewPort().Left();
	pos.x = min(max(pos.x, left),right);*/

	Postion2f campos = camera.CalculatePosition(pos);

	//回転したり拡大できる
	DrawRectRotaGraph2(campos.x,campos.y,
						rc.Left(),rc.Top(),
						rc.Wight(),rc.Height(),
						centerX,cut.center.y,
						Game::Instance().GetObjectScale(), 
						0, PlayerImg, 
						true, 
						isTrun);//キャラ描画
	DebugDraw();
}

void Player::Updata(const Peripheral &p)
{
	(this->*updataer)(p);

	pos += vel;

	//////地面から離れていたら重力を受ける
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
	//歩きアニメーションを再生
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
	//duration=カットの長さ

	ProceedAnimationFrame();
	
		//ジャンプの再生
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
	//参考演算子 falseだったら-5.0f,trueだったら5.0f
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
	//アニメーションが終わったらchangeacionをさせる

	if (ProceedAnimationFrame())
	{

		ChangeAction("Walk");
		updataer = &Player::NeutralUpdata;
		return;
	}
	
	//くらったとき、velの値を移動させる
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
	//参考演算子 falseだったら-5.0f,trueだったら5.0f
	vel.x = isTrun ? -3.0f : 3.0f;
}

void Player::Muteki()
{

}


void Player::MutekiUpdata(const Peripheral &p)
{
	//ダメージくらったときに無敵時間
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
	//中心座標
	DrawBox(campos.x - 2, campos.y - 2, campos.x + 2, campos.y + 2, 0xffffffff, true);
	//当たり矩形
	auto&  actInfo = actionData.actInfo[currentActionName];
	auto&  cut = actInfo.cuts[currentCutIndex];
	auto&  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;
	//中心の中を透けさせる
	for (auto& act : cut.actrects)
	{
		Rect rc = act.rc;
		rc = GetActuralRectForAction(rc);
		DrawBox(rc.Left(), rc.Top(), rc.Right(), rc.Botton(), 0xfffffffff,true);

	}
	DxLib::SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, (0));
}