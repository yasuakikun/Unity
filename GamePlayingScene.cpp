#include "GamePlayingScene.h"

GamePlayingScene::GamePlayingScene() : game(Game::Instance())
{
	//endtime = 150;
	//スタートたいまー
	starttime = 180;
	//フェードタイマー
	Fadetimer = 255;
	updataer = &GamePlayingScene::Fadein;
	//ブレンドモード
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//初期化
	ground.reset(new Ground());
	stage.reset(new Stage());
	camera.reset(new Camera(*camera));
	bg.reset(new Background(*camera));
	player.reset(new Player(*camera));


	stage = std::make_shared<Stage>();
	camera = std::make_shared<Camera>(*stage);
	bg = std::make_shared<Background>(*camera);
	player = std::make_shared<Player>(*camera);
	ground = std::make_shared<Ground>();

	camera->SetFocus(player);

	camera->Updata();



	//関数で分けて、コンストラクタでpush＿backする
	//敵の量産
	//デッドマン
	list.push_back(new DeadMen({ 400, 340 }));
	list.push_back(new DeadMen({ 600, 340 }));
	list.push_back(new DeadMen({ 800, 340 }));
	//バットマン
	list.push_back(new BatMen({ 600, 100 }));
	list.push_back(new BatMen({ 1000, 100 }));
	//スパイク
	list.push_back(new Pike({ 500, 100 }));
}


GamePlayingScene::~GamePlayingScene()
{
	//ゲーム終わったらリストを消す
	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		delete *itr;
	}
}

void GamePlayingScene::Updata(const Peripheral &p)
{

	//int frame = 0;
	bg->Draw();
	player->Draw();


	bg->Update();
	//エフェクト
	//DxLib::DrawRectGraph(0, 0, ((frame) % 10) * 30, ((frame) % 10) * 30, 256,256, FireImg, true, false);
	
	player->Updata(p);

	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		(*itr)->Draw();
		(*itr)->Update(*player);
	}

	//地面の位置
	auto groundy = ground->GetCurrentGroundY();

	if (player->GetPostion().y > groundy)
	{
		player->OnGround(groundy);
	}

	//当たったら時の処理をしている
	for (auto& a : player->GetActionRect())
	{
		for (auto itr = list.begin(); itr != list.end(); ++itr)
		{
			for (auto& b : (*itr)->GetActionRect())
			{
				if (a.rt == RectType::attack && b.rt == RectType::damage)
				{
					if (CollisionDetector::IsCollided((Rect&)player->GetActuralRectForAction(a.rc), (Rect&)(*itr)->GetActuralRectForAction(b.rc)))
					{
						(*itr)->OnDamage(*player);
					}
				}
				if (a.rt == RectType::damage && b.rt == RectType::attack)
				{
					if (CollisionDetector::IsCollided((Rect&)player->GetActuralRectForAction(a.rc), (Rect&)(*itr)->GetActuralRectForAction(b.rc)))
					{
						player->onDamage();
					}
				}
			}
		}
	}

	camera->Updata();

	//死んだときリストを消す
	for (auto itr = list.begin(); itr != list.end();)
	{
		if ((*itr)->GetDeadFlag())
		{
			delete *itr;
			itr = list.erase(itr);
		}
		else
		{
			++itr;
		}
	}

	//敵のリストの数がわかる
	DrawFormatString(60, 20, GetColor(255, 255, 255), "リストの数 %d", list.size());

	//一秒間time
	static int b = 0;
	DrawFormatString(300, 20, GetColor(255, 255, 255), "%d",b);
	++b;

	player->DrawPos();

	ground->GroundDraw();

	//frame = (frame + 1) % 30;
	//毎フレーム書く
	printf("ゲーム中\n");

	//w押したらフェードアウト
	if (p.IsTrigger(PAD_INPUT_8))
	{
		updataer = &GamePlayingScene::Fadeout;
	}
	//メンバ関数ポインタ
	(this->*updataer)(p);
}


void GamePlayingScene::Fadein(const Peripheral &p)
{
	Fadetimer = max(Fadetimer -1, 0);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fadetimer);
	DrawBox(0,0,768,448,0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (Fadetimer <= 0)
	{
		updataer = &GamePlayingScene::NormalUpdata;
	}
}

void GamePlayingScene::NormalUpdata(const Peripheral &p)
{
}

void GamePlayingScene::Fadeout(const Peripheral &p)
{
	//maxの反対min
	Fadetimer = min(Fadetimer + 1, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fadetimer);
	DrawBox(0, 0, 768, 448, 0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//タイマーが255になったら画面以降
	if (Fadetimer >= 255) 
	{
		Game::Instance().ChangeScene(new Continue());
	}
}

//いきなりはじまらないで、最初の３秒は動けない