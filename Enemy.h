#pragma once
#include "CharaObject.h"

class Player;

class Enemy:
	public CharaObject
{
public:
	Enemy();
	virtual~Enemy();
	virtual void Update(Player& pl) = 0;
	virtual void Draw() = 0;
	virtual void OnDamage(Player& pl) = 0;
};

