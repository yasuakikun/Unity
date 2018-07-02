#include <iostream>
#include "DxLib.h"
#include "Player.h"
#include "Peripheral.h"
#include "Game.h"

using namespace std;

int main() 
{
	Game& game = Game::Instance();
	game.Initalize();
	game.Run();
	game.Tarminete();
	//return 0;
}