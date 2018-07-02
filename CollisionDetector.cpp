#include "CollisionDetector.h"



CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::IsCollided(Rect& rcA,Rect& rcB)
{
	Rect a = rcA;
	Rect b = rcB;

	//‹éŒ`î•ñ‚Å‚â‚é@‚Ü‚½‚Í
	return abs(a.center.x - b.center.x) < (a.Wight() + b.Wight()) / 2 &&  abs(a.center.y - b.center.y) < (a.Height() + b.Height())/ 2;
}
