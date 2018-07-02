#include "BatMen.h"
#include "DxLib.h"
#include "player.h"


BatMen::BatMen(Postion2f pos) : Enemy()
{
	this->pos = pos;
	currentActionName = "Fly";
	ReedActionFile("action/bat.act");
	BatMenImg = LoadGraph(actionData.ImgFilePath.c_str());
	damageSE = LoadSoundMem("se/bird_damage.mp3");
	birdSE = LoadSoundMem("se/habataki.mp3");
	waittime = 0;
	isTrun = false;

	updataer = &BatMen::WaitUpdata;
}


BatMen::~BatMen()
{
	DeleteGraph(BatMenImg);
}

void BatMen::Update()
{
}

void BatMen::Update(Player & pl)
{
	(this->*updataer)(pl);
}

void BatMen::Draw()
{

	auto&  actInfo = actionData.actInfo[currentActionName];
	auto&  cut = actInfo.cuts[currentCutIndex];
	auto&  rc = cut.rc;
	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;

	DrawRectRotaGraph2(pos.x, pos.y,
		rc.Left(), rc.Top(),
		rc.Wight(), rc.Height(),
		centerX, cut.center.y,
		2, 0, BatMenImg,
		true,
		isTrun);//キャラ描画

	DebugDraw();
}

void BatMen::WaitUpdata(Player &pl)
{
	updataer = &BatMen::FlyUpdata;
	//リッカーのｘがバットマンのｘ座標より大きかったら
	//反転だけ
	if (pl.GetPostion().x < pos.x)
	{
		isTrun = true;
	}
	else 
	{
		isTrun = false;
	}

}

void BatMen::FlyUpdata(Player & pl)
{
	vel.y = sin(Angle)*3.0f;
	Angle = 0.1;
	PlaySoundMem(birdSE, DX_PLAYTYPE_BACK);
	ProceedAnimationFrame();

	//プレイヤーの座標がバットよりも大きかったら
	if (pl.GetPostion().y - 90 >= pos.y)
	{
		updataer = &BatMen::WaitUpdata;
		//上下に揺れながら飛ばせる sinを掛けてあげる
		pos.y += 1;
	}

	if (pl.GetPostion().x < pos.x)
	{
		updataer = &BatMen::WaitUpdata;
		pos.x -= 2.0f;
	}
	else
	{
		updataer = &BatMen::WaitUpdata;
		pos.x += 2.0f;
	}
}

void BatMen::OnDamage(Player & pl)
{
	ChangeAction("Damage");
	updataer = &BatMen::DamageUpdata;
	PlaySoundMem(damageSE, DX_PLAYTYPE_BACK);
	waittime = 15;

}

void BatMen::DamageUpdata(Player & pl)
{
	//地面についたときに消す
	if (pos.y == 340)//340だった時
	{
		ChangeAction("Die");
		updataer = &BatMen::DieUpdata;
		return;
	}
	else
	{
		pos.y += 1.0f;
	}
}


void BatMen::DieUpdata(Player & pl)
{
	//ここを地面についた時に消すように帰る
	if (ProceedAnimationFrame())
	{
		DeadFlag = true;
		DeleteGraph(BatMenImg);
	}
}


