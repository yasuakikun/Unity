#include "Ground.h"
#include "Geometry.h"

const int groundline = 340;

Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::GroundDraw()
{
	DxLib::DrawLine(0, 340, 768, 340, 0xffffffff, true);
}

int Ground::GetCurrentGroundY()
{
	return groundline;
}



