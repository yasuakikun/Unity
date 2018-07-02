#include "CharaObject.h"
#include "DxLib.h"
#include "Peripheral.h"
#include <cassert>
#include "Game.h"

CharaObject::CharaObject() : Frame(0),currentCutIndex(0),isTrun(false),pos(0,0), vel(0, 0),DeadFlag(false)
{

}

void CharaObject::ChangeAction(const char *ActionName)
{
	Frame = 0;
	currentActionName = ActionName;
	currentCutIndex = 0;
}

bool CharaObject::ProceedAnimationFrame()
{
	if (Frame < actionData.actInfo[currentActionName].cuts[currentCutIndex].duration)
	{
		++Frame;
	}
	else
	{
		Frame = 0;
		if (currentCutIndex < actionData.actInfo[currentActionName].cuts.size() - 1)
		{
			++currentCutIndex;
		}
		else
		{
			if (actionData.actInfo[currentActionName].isLoop)
			{
				currentCutIndex = 0;
			}
			else
			{
				return true;
			}
		}
	}
	return false;
}

void CharaObject::ReedActionFile(const char *actionPath)
{
	int h = DxLib::FileRead_open(actionPath, false);
	float ver = 0.0f;
	DxLib::FileRead_read(&ver, sizeof(ver), h);
	assert(ver == 1.01f);

	int imgpathsize = 0;
	DxLib::FileRead_read(&imgpathsize, sizeof(imgpathsize), h);
	std::string imgPath = "";
	imgPath.resize(imgpathsize);
	std::string actPath = actionPath;
	auto ipos = actPath.find_last_of('/') + 1;
	//fopen
	DxLib::FileRead_read(&imgPath[0], imgpathsize, h);

	actionData.ImgFilePath = actPath.substr(0, ipos) + imgPath;

	int actionCount = 0;
	DxLib::FileRead_read(&actionCount, sizeof(actionCount), h);

	for (int i = 0; i < actionCount; ++i)
	{
		int actionNameSize = 0;
		DxLib::FileRead_read(&actionNameSize, sizeof(actionNameSize), h);


		std::string actionName;
		actionName.resize(actionNameSize);
		DxLib::FileRead_read(&actionName[0], actionName.size(), h);

		ActionInfo actInfo;
		//���[�v����1�o�C�g
		DxLib::FileRead_read(&actInfo.isLoop, sizeof(actInfo.isLoop), h);

		//�J�b�g�f�[�^�̓ǂݍ���
		int CutCount = 0;
		DxLib::FileRead_read(&CutCount, sizeof(CutCount), h);
		actInfo.cuts.resize(CutCount);

		for (int i = 0; i < CutCount; ++i)
		{
			//�S�S�o�C�g����P�U�o�C�g���Ђ��Ă�
			DxLib::FileRead_read(&actInfo.cuts[i], sizeof(actInfo.cuts[i]) - sizeof(actInfo.cuts[i].actrects), h);

			//�A�N�V������`�̂�݂���
			int actRectCount = 0;
			DxLib::FileRead_read(&actRectCount, sizeof(actRectCount), h);
			if (actRectCount == 0)
			{
				continue;
			}
			actInfo.cuts[i].actrects.resize(actRectCount);
			//�A�N�V������`�̂O���擪�ɂȂ�A�擪����͂���
			DxLib::FileRead_read(&actInfo.cuts[i].actrects[0], actRectCount * sizeof(ActionRect), h);
		}
		//�A�N�V�����}�b�v�ɓo�^
		actionData.actInfo[actionName] = actInfo;
	}
	DxLib::FileRead_close(h);
}

 CharaObject::~CharaObject()
{
}

 void CharaObject::DebugDraw()
 {
	 Game& game = Game::Instance();
 	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (64));
 	//���S���W
 	DrawBox(pos.x - 2, pos.y - 2, pos.x + 2, pos.y + 2, 0xffffffff, true);
 	//�������`
 	auto&  actInfo = actionData.actInfo[currentActionName];
 	auto&  cut = actInfo.cuts[currentCutIndex];
 	auto&  rc = cut.rc;
 	auto centerX = isTrun ? rc.Wight() - cut.center.x : cut.center.x;
 	//���S�̒��𓧂�������
 	for (auto& act : cut.actrects)
 	{
 		Rect rc = act.rc;
		rc = GetActuralRectForAction(rc);
		//Postion2f campos = camera.CalculatePosition(pos);
 		DrawBox(rc.Left(),rc.Top(),rc.Right(), rc.Botton(), 0xfffffffff,true);
 
 	}
 	DxLib::SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, (0));
 }

std::vector<ActionRect>& CharaObject::GetActionRect()
 {
	 return actionData.actInfo[currentActionName].cuts[currentCutIndex].actrects;
 }
		 

 Rect CharaObject::GetActuralRectForAction(Rect& rc)
 {
	 Game &game = Game::Instance();
	 Rect rct = rc;
	 rct.center.x = isTrun ? -rct.center.x : rct.center.x;
	 rct.center.x = pos.x + (rct.center.x * 2.0f);
	 rct.center.y = pos.y + (rct.center.y * 2.0f);
	 rct.SetWidth(2);
	 rct.SetHeight(2);

	 return rct;
 }

 const Postion2f CharaObject::GetPostion() const
 {
	 return pos;
 }
