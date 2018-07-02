#include "Peripheral.h"
#include "DxLib.h"


Peripheral::Peripheral()
{
}


Peripheral::~Peripheral()
{
}

bool Peripheral::IsPressing(int button) const
{
	return padState &button;
}

bool Peripheral::IsTrigger(int button) const
{
	return (padState &button) && !(lastpadState & button);
}

void Peripheral::Update()
{
	lastpadState = padState;
	padState = DxLib::GetJoypadInputState(DX_INPUT_KEY_PAD1);
}
