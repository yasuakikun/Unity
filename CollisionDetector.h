#pragma once
#include "CharaObject.h"
class CollisionDetector:
	public CharaObject
{
public:
	CollisionDetector();
	~CollisionDetector();
	//posの値を入れてあげる
	static bool IsCollided(Rect& rcA, Rect& rcB);
};

