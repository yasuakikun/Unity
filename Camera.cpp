#include <cassert>
#include "Game.h"
#include "Player.h"
#include "Camera.h"
#include <DxLib.h>

Camera::Camera(const Stage& _stage) : game(Game::Instance()), stage(_stage)
{
}

Camera::~Camera()
{
}

void Camera::Updata()
{
	assert(!focus.expired());

	const auto& range = stage.GetStageRange();
	const auto& size = Game::Instance().GetScreenSize();
	pos = (focus.lock())->GetPostion();

	//ÉJÉÅÉâç¿ïWÇÃï‚ê≥
	if (pos.x - size.w / 2 < range.Left())
	{
		pos.x = (float)(range.Left() + size.w / 2);
	}
	else if (pos.x + size.w / 2 > range.Right())
	{
		pos.x = (float)(range.Right() - size.w / 2);
	}
}

void Camera::SetFocus(std::shared_ptr<CharaObject> c)
{
	focus = c;
}

Postion2f Camera::CalculatePosition(Postion2f cpos)
{
	const auto& size = Game::Instance().GetScreenSize();

	cpos.x = cpos.x - pos.x + size.w / 2;

	return cpos;
}

const Postion2f & Camera::GetPostion() const
{
	return pos;
}

Rect & Camera::GetViewPort()
{
	const auto& size = Game::Instance().GetScreenSize();

	rect.center.x = pos.x;
	rect.center.y = 0;

	rect.size = Size(size.w, size.h);

	return rect;
}
