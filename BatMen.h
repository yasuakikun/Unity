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
	void WaitUpdata(Player& pl);//�j���[�g�������
	void FlyUpdata(Player &pl);//�������
	void OnDamage(Player &pl);
	void DamageUpdata(Player &pl);
	void DieUpdata(Player &pl);

private:
	int birdSE;
	int damageSE;
	float Angle;//�p�x
	int waittime;
};

