#pragma once
#include "Enemy.h"
#include "CharaObject.h"
#include "Player.h"
#include "Camera.h"
#include "Geometry.h"

class Player;
class Camera;

class Pike :
	public Enemy
{
public:
	Pike(Postion2f pos);
	virtual~Pike();
	void Draw();
	void Update();
	void Update(Player & pl);
	void(Pike::*updataer)(Player& pl);
	void NeutralUpdata(Player& pl);//ニュートラル状態]
	void AttackUpdata(Player &pl);//アタック状態
	void OnDamage(Player &pl);
	void Neutral();
	void Attack();
private:
	int waitCount;
	UINT PikeImg;
	int frame;
};

