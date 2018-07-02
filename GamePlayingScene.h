#pragma once
#include "Scene.h"
#include "Peripheral.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "Geometry.h"
#include "DxLib.h"
#include "Ground.h"
#include "HUD.h"
#include "DeadMen.h"
#include "Background.h"
#include "CollisionDetector.h"
#include "BatMen.h"
#include "TitleScene.h"
#include "Continue.h"
#include "Pike.h"
#include "Camera.h"
#include <memory>
#include <list>

class Stage;
class Camera;
class Background;
class Player;
class Ground;


class GamePlayingScene :
	public Scene
{
public:
	GamePlayingScene();
	~GamePlayingScene();
    void Updata(const Peripheral &);
	//メンバ関数ポインタ
	void(GamePlayingScene::*updataer)(const Peripheral&);
	void Fadein(const Peripheral &);
	void Fadeout(const Peripheral &);
	void NormalUpdata(const Peripheral &);

	Game& game;
	std::shared_ptr<Stage>stage;
	std::shared_ptr<Camera>camera;
	std::shared_ptr<Background> bg;
	std::shared_ptr<Player>player;
	std::shared_ptr<Ground>ground;


private:
	std::list<Enemy*>list;
	int HitStopTimer;
	int wait;
	int endtime;
	int starttime;
	int Fadetimer;
	//メンバ変数
	//Ground* ground;
	//Background* bg;
	//Player* player;
	//Camera* camera;
	//Stage* stage;
};

