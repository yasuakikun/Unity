#pragma once
#include "Player.h"
#include "Enemy.h"
#include "EnemyFactory.h"
#include "Camera.h"



class Player;
class Camera;

class DeadMen:

	public Enemy 
{
public:
	DeadMen(Postion2f pos);
	virtual~DeadMen();
	void Update();
	void Update(Player &pl);
	void Draw();
	//Player& player;
	UINT DeadMenImg;
	void(DeadMen::*updataer)(Player& pl);
	void NeutralUpdata(Player& pl);//ニュートラル状態
	void WalkUpdata(Player &pl);//歩き状態
	void OnDamage(Player &pl);
	void DamageUpdata(Player &pl);
	int waitCount;
	void DieUpdata(Player &pl);
private:
	int damageSE;
	//Camera& camera;
};

