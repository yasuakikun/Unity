#pragma once
#include "Enemy.h"
class EnemyFactory :
	public Enemy
{
public:
	EnemyFactory();
	~EnemyFactory();
	 
	Enemy *Crete( char *enemyname , Postion2f &p);
private:
	//std::map<ActionRect>
};

