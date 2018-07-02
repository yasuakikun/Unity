#include "Pike.h"
#include "DxLib.h"
#include "player.h"

Pike::Pike(Postion2f pos) : Enemy()
{
	this->pos = pos;
	currentActionName = "Attack";
	ReedActionFile("action/pike.act");
	PikeImg = LoadGraph(actionData.ImgFilePath.c_str());
	waitCount = 0;
	isTrun = false;

	updataer = &Pike::AttackUpdata;
}


Pike::~Pike()
{
	DeleteGraph(PikeImg);
}

void Pike::Draw()
{
	auto&  actInfo = actionData.actInfo[currentActionName];
	auto&  cut = actInfo.cuts[currentCutIndex];
	//auto& loop = actInfo.isLoop;
	auto&  rc = cut.rc;


	//Postion2f campos = camera.CalculatePosition(pos);

	DrawRectRotaGraph2(pos.x, pos.y,
		rc.Left(), rc.Top(),
		rc.Wight(), rc.Height(),
		cut.center.x,cut.center.y,
		2, 0, PikeImg,
		true,
		isTrun);//キャラ描画

	DebugDraw();
}

void Pike::Update()
{
}

void Pike::Update(Player &pl)
{
	(this->*updataer)(pl);
	pos += vel;
}

void Pike::Neutral()
{
	waitCount = 0;
	updataer = &Pike::NeutralUpdata;
}

void Pike::Attack()
{
	waitCount = 0;
	frame = 0;
	updataer = &Pike::AttackUpdata;
}

void Pike::NeutralUpdata(Player & pl)
{
	if (waitCount <= 0)
	{
		Attack();
	}
	else
	{
		--waitCount;
	}
	
}

void Pike::OnDamage(Player & pl)
{
	//ダメージない
}

void Pike::AttackUpdata(Player & pl)
{
	if (ProceedAnimationFrame())
	{
		Neutral();
	}
}


