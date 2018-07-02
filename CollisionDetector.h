#pragma once
#include "CharaObject.h"
class CollisionDetector:
	public CharaObject
{
public:
	CollisionDetector();
	~CollisionDetector();
	//pos‚Ì’l‚ð“ü‚ê‚Ä‚ ‚°‚é
	static bool IsCollided(Rect& rcA, Rect& rcB);
};

