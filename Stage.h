#pragma once
#include "Geometry.h"
#include <string>
#include <vector>

struct StageData {
	unsigned int identifier;
	unsigned int headerSize;
	unsigned int mapW;
	unsigned int mapH;
	unsigned char chipW;
	unsigned char chipH;
	unsigned char layCnt;
	unsigned char bitCnt;
};

class Stage
{
private:
	Rect stageRange;
	Rect mapSize;

	StageData header;

	std::vector<unsigned char> enemyData;

	int readX;

	void ReadFile(const char* filePath);

public:
	Stage();
	~Stage();

	const Rect& GetStageRange()const;

	const Rect& GetMapSize();

	std::vector<unsigned char> GetEnemySpawnRange(int first, int last);
};