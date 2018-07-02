#pragma once
#include "Scene.h"
#include "Peripheral.h"
class Continue :
	public Scene
{
public:
	Continue();
	~Continue();
	void Updata();
	void Updata(const Peripheral &);
private:
	int ContinueImg;
	int BotanImg;
	int CountDown;
};