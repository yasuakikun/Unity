#pragma once
#include "CharaObject.h"
class CollisionDetector:
	public CharaObject
{
public:
	CollisionDetector();
	~CollisionDetector();
	//pos�̒l�����Ă�����
	static bool IsCollided(Rect& rcA, Rect& rcB);
};

