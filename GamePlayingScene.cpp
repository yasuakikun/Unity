#include "GamePlayingScene.h"

GamePlayingScene::GamePlayingScene() : game(Game::Instance())
{
	//endtime = 150;
	//�X�^�[�g�����܁[
	starttime = 180;
	//�t�F�[�h�^�C�}�[
	Fadetimer = 255;
	updataer = &GamePlayingScene::Fadein;
	//�u�����h���[�h
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//������
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



	//�֐��ŕ����āA�R���X�g���N�^��push�Qback����
	//�G�̗ʎY
	//�f�b�h�}��
	list.push_back(new DeadMen({ 400, 340 }));
	list.push_back(new DeadMen({ 600, 340 }));
	list.push_back(new DeadMen({ 800, 340 }));
	//�o�b�g�}��
	list.push_back(new BatMen({ 600, 100 }));
	list.push_back(new BatMen({ 1000, 100 }));
	//�X�p�C�N
	list.push_back(new Pike({ 500, 100 }));
}


GamePlayingScene::~GamePlayingScene()
{
	//�Q�[���I������烊�X�g������
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
	//�G�t�F�N�g
	//DxLib::DrawRectGraph(0, 0, ((frame) % 10) * 30, ((frame) % 10) * 30, 256,256, FireImg, true, false);
	
	player->Updata(p);

	for (auto itr = list.begin(); itr != list.end(); ++itr)
	{
		(*itr)->Draw();
		(*itr)->Update(*player);
	}

	//�n�ʂ̈ʒu
	auto groundy = ground->GetCurrentGroundY();

	if (player->GetPostion().y > groundy)
	{
		player->OnGround(groundy);
	}

	//���������玞�̏��������Ă���
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

	//���񂾂Ƃ����X�g������
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

	//�G�̃��X�g�̐����킩��
	DrawFormatString(60, 20, GetColor(255, 255, 255), "���X�g�̐� %d", list.size());

	//��b��time
	static int b = 0;
	DrawFormatString(300, 20, GetColor(255, 255, 255), "%d",b);
	++b;

	player->DrawPos();

	ground->GroundDraw();

	//frame = (frame + 1) % 30;
	//���t���[������
	printf("�Q�[����\n");

	//w��������t�F�[�h�A�E�g
	if (p.IsTrigger(PAD_INPUT_8))
	{
		updataer = &GamePlayingScene::Fadeout;
	}
	//�����o�֐��|�C���^
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
	//max�̔���min
	Fadetimer = min(Fadetimer + 1, 255);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fadetimer);
	DrawBox(0, 0, 768, 448, 0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//�^�C�}�[��255�ɂȂ������ʈȍ~
	if (Fadetimer >= 255) 
	{
		Game::Instance().ChangeScene(new Continue());
	}
}

//�����Ȃ�͂��܂�Ȃ��ŁA�ŏ��̂R�b�͓����Ȃ�