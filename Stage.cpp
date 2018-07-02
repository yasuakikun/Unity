#include "Stage.h"
#include <DxLib.h>

Stage::Stage() : readX(0)
{
	ReadFile("Stage/stage1.fmf");

	stageRange.center = { (int)((header.chipW * header.mapW)), 0 };
	stageRange.size = { (int)((header.chipW * 2) * header.mapW), 0 };

	mapSize.center = { 0, 0 };
	mapSize.size = { (int)header.mapW, (int)header.mapH };
}

Stage::~Stage()
{
}

void Stage::ReadFile(const char * filePath)
{
	int h = FileRead_open(filePath);

	//�p�X
	FileRead_read(&header, sizeof(header), h);

	//�z�u�f�[�^�̓ǂݍ���
	std::vector<unsigned char> range(header.mapW * header.mapH);
	FileRead_read(&range[0], range.size(), h);

	FileRead_close(h);

	enemyData.resize(range.size());

	for (int y = 0; y < header.mapH; y++)
	{
		for (int x = 0; x < header.mapW; x++)
		{
			enemyData[x * header.mapH + y] = range[y * header.mapW + x];
		}
	}
}

const Rect & Stage::GetStageRange() const
{
	return stageRange;
}

const Rect & Stage::GetMapSize()
{
	return mapSize;
}

std::vector<unsigned char> Stage::GetEnemySpawnRange(int first, int last)
{
	int Left = max(first / (header.chipW * 2), readX);
	int Right = last / (header.chipW * 2);

	if (Right <= readX)
	{
		//�ǂݍ��ݔ͈͂��Ȃ������ꍇ�ǂݍ��݂Ȃ��ɂ���
		return std::vector<unsigned char>();
	}

	auto idxL = Left * header.mapH;
	auto idxR = Right * header.mapH;
	auto begin = enemyData.begin() + idxL;
	auto end = enemyData.begin();

	if (idxR >= enemyData.size())
	{
		end = enemyData.end();
	}
	else
	{
		end = enemyData.begin() + idxR;
	}

	readX = Right;	//�ǂݍ����ő�

	return std::vector<unsigned char>(begin, end); 
}
