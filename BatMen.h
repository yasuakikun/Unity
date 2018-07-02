#pragma once
#include "Enemy.h"
#include "batMen.h"
#include "Player.h"
#include "Ground.h"
class Player;

class BatMen :
	public Enemy
{
public:
	BatMen(Postion2f pos);
	virtual~BatMen();
	void Update();
	void Update(Player &pl);
	void Draw();
	//Player& player;
	UINT BatMenImg;
	void(BatMen::*updataer)(Player& pl);
	void WaitUpdata(Player& pl);//ニュートラル状態
	void FlyUpdata(Player &pl);//歩き状態
	void OnDamage(Player &pl);
	void DamageUpdata(Player &pl);
	void DieUpdata(Player &pl);

private:
	int birdSE;
	int damageSE;
	float Angle;//角度
	int waittime;
};

