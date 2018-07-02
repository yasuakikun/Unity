#pragma once
#include "Geometry.h"
#include <string>
#include <vector>
#include <map>

//�L�������N���X
enum class RectType {
	anchor,//�A���J�[(0) 
	attack,//�U����`(1) 
	damage//�����`(2) 
};

//�A�N�V�������
struct ActionRect
{
	RectType rt;	//��`��� 
	Rect rc;		//��`��� 
};

//�؂蔲�����
struct CutInfo
{
	Rect rc;		//��`
	Postion2 center;//���S�_
	int duration;		//�\������ 1 = 4�o�C�g�@
	std::vector<ActionRect> actrects;//�A�N�V������` 
};//�Q�W�o�C�g+16�o�C�g�@�S�S�o�C�g
  //�A�N�V������`�����ĂS�S�o�C�g�ɂȂ�

typedef std::vector<CutInfo> CutInfo_t;//�z��̕���

struct ActionInfo
{
	bool isLoop;//���[�v
	CutInfo_t cuts;//�J�b�g
};

struct ActionData
{
	std::string ImgFilePath;
	std::map<std::string, ActionInfo> actInfo;	//�A�N�V�������
};

class CharaObject
{
public:
	CharaObject();
	virtual ~CharaObject();
	virtual void Draw() = 0;
	//�����蔻��
	std::vector<ActionRect>& GetActionRect();
	Rect GetActuralRectForAction(Rect& rc);
	const Postion2f GetPostion()const;
	bool GetDeadFlag()
	{
		return DeadFlag;
	}

	Postion2f pos;
	//�����̍��W

protected:
	ActionData actionData;
	//���̃A�N�V�������
	std::string currentActionName;
	int currentCutIndex;
    unsigned int Frame;
	int _graphH;

	CutInfo currentCut;//���݂̃J�b�g�I�u�W�F�N�g 


	void ChangeAction(const char *ActionName);
	//�A�j���[�V�����t���[����i�߂� 
	bool ProceedAnimationFrame();
	void ReedActionFile(const char *action_path);
	void DebugDraw();

	bool isTrun;
	//�����̑��x
	Vector2f vel;
	//���S�t���O
	bool DeadFlag;

};

