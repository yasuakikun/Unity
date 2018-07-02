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

//�Q�[���S�̂��Ǘ�����7�N���X
//�V���O���g���p�^�[��
//main�̕��������
class Game
{
public:
	static Game& Instance() {
		static Game Instance;
		return Instance;
	}
	~Game();
	//�������n
	void Initalize();
	//���Ƀ��[�v������
	void Run();
	void Tarminete();

	const float GetObjectScale()const;
	void ChangeScene(Scene *scene);

	const ScreenSize& GetScreenSize();


private:
	Game();
	Game(const Game&);//�R�s�[�֎~
	Game& operator=(const Game&) {};//����֎~

	int haikeiImg;
	int bgImg3;
	int bgImg4;
	int FireImg;
	std::list<Enemy*>list;
	std::shared_ptr<Scene> _scene;
	ScreenSize size;

};

