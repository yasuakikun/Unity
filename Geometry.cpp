#include "Geometry.h"



Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

Rect::Rect()
{
}

Rect::Rect(int x, int y, int w, int h)
{
}

Rect::Rect(Postion2 &pos, Size &size)
{
}

const int Rect::Left() const//��
{
	return center.x - size.w / 2;
}

const int Rect::Top() const//��
{
	return center.y - size.h / 2;
}

const int Rect::Right() const//�E
{
	return center.x + size.w / 2;
}

const int Rect::Botton() const//��
{
	return center.y + size.h / 2;
}

const int Rect::Wight() const
{
	return size.w;
}

const int Rect::Height() const
{
	return size.h;
}


void Rect::Draw(unsigned int color /*= 0xffffffff*/)
{
	DrawBox(Left(), Top(), Right(), Botton(),color,true);
}

void Rect::Draw(const Vector2 &offset, unsigned int color /*= 0xffffffff*/)
{
	DrawBox(Left() + offset.x, Top() + offset.y, Right() + offset.x, Botton() + offset.y, color, true);
}

Size::Size()
{
}
