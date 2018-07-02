#include "DeadMen.h"
#include "DxLib.h"
#include "Camera.h"
#include "player.h"


DeadMen::DeadMen(Postion2f pos) : Enemy()
{
	this->pos = pos;
	currentActionName = "Walk";
	ReedActionFile("action/deadman.act");
	DeadMenImg = LoadGraph(actionData.ImgFilePath.c_str());
	damageSE = LoadSoundMem("se/e_gusha.mp3");
	waitCount = 0;
	isTrun = false;

	updataer = &DeadMen::NeutralUpdata;
}


DeadMen::~DeadMen()
{
	DeleteGraph(DeadMenImg);
}

void DeadMen::Update()
{
}


void DeadMen::Update(Player &pl)
{
	(this->*updataer)(pl);
	pos += vel;
}

void DeadMen::Draw() 
{
	auto&  actInfo = actionData.actInfo[currentActionName];
	auto&  cut = actInfo.cuts[currentCutIndex];
	auto&  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;

	//Postion2f campos = camera.CalculatePosition(pos);

	DrawRectRotaGraph2(pos.x,pos.y,
		rc.Left(), rc.Top(),
		rc.Wight(), rc.Height(),
		centerX, cut.center.y,
		2, 0, DeadMenImg,
		true,
		isTrun);//キャラ描画

	DebugDraw();
}

void DeadMen::NeutralUpdata(Player & pl)
{
	vel.x = 0;
	//振り向き判定をする
	if (pl.GetPostion().x <= pos.x)
	{
		isTrun = true;
		waitCount = 60;
		updataer = &DeadMen::WalkUpdata;
	}
	else {
		isTrun = false;
		waitCount = 60;
		updataer = &DeadMen::WalkUpdata;
	}
}

void DeadMen::WalkUpdata(Player& pl)
{
	vel.x = isTrun ? -1.0f : 1.0f;
	ProceedAnimationFrame();
	if (waitCount <= 0)
	{
		updataer = &DeadMen::NeutralUpdata;
	}
	else 
	{
		--waitCount;
	}
}

void DeadMen::OnDamage(Player &pl)
{
	ChangeAction("Damage");
	updataer = &DeadMen::DamageUpdata;
}

void DeadMen::DamageUpdata(Player &pl)
{
	vel.x = 0;
	if (ProceedAnimationFrame())
	{
		ChangeAction("Die");
		updataer = &DeadMen::DieUpdata;
		PlaySoundMem(damageSE, DX_PLAYTYPE_BACK);
		return;
	}
	//ダメージを受けたとき、移動させる
	vel.x = isTrun ? 10.0f : -10.0f;
}

void DeadMen::DieUpdata(Player & pl)
{
	vel.x = 0;
	if (ProceedAnimationFrame())
	{
		DeadFlag = true;
		DeleteGraph(DeadMenImg);
	}
}



