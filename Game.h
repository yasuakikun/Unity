#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "Geometry.h"
#include <list>
#include <memory>

struct ScreenSize
{
	int w;
	int h;
};

//ゲーム全体を管理する7クラス
//シングルトンパターン
//mainの分をいれる
class Game
{
public:
	static Game& Instance() {
		static Game Instance;
		return Instance;
	}
	~Game();
	//初期化系
	void Initalize();
	//中にループが入る
	void Run();
	void Tarminete();

	const float GetObjectScale()const;
	void ChangeScene(Scene *scene);

	const ScreenSize& GetScreenSize();


private:
	Game();
	Game(const Game&);//コピー禁止
	Game& operator=(const Game&) {};//代入禁止

	int haikeiImg;
	int bgImg3;
	int bgImg4;
	int FireImg;
	std::list<Enemy*>list;
	std::shared_ptr<Scene> _scene;
	ScreenSize size;

};

