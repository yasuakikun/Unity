#pragma once
#include "Geometry.h"
#include <string>
#include <vector>
#include <map>

//キャラ基底クラス
enum class RectType {
	anchor,//アンカー(0) 
	attack,//攻撃矩形(1) 
	damage//やられ矩形(2) 
};

//アクション情報
struct ActionRect
{
	RectType rt;	//矩形種別 
	Rect rc;		//矩形情報 
};

//切り抜き情報
struct CutInfo
{
	Rect rc;		//矩形
	Postion2 center;//中心点
	int duration;		//表示時間 1 = 4バイト　
	std::vector<ActionRect> actrects;//アクション矩形 
};//２８バイト+16バイト　４４バイト
  //アクション矩形を入れて４４バイトになる

typedef std::vector<CutInfo> CutInfo_t;//配列の部分

struct ActionInfo
{
	bool isLoop;//ループ
	CutInfo_t cuts;//カット
};

struct ActionData
{
	std::string ImgFilePath;
	std::map<std::string, ActionInfo> actInfo;	//アクション情報
};

class CharaObject
{
public:
	CharaObject();
	virtual ~CharaObject();
	virtual void Draw() = 0;
	//当たり判定
	std::vector<ActionRect>& GetActionRect();
	Rect GetActuralRectForAction(Rect& rc);
	const Postion2f GetPostion()const;
	bool GetDeadFlag()
	{
		return DeadFlag;
	}

	Postion2f pos;
	//自分の座標

protected:
	ActionData actionData;
	//今のアクション情報
	std::string currentActionName;
	int currentCutIndex;
    unsigned int Frame;
	int _graphH;

	CutInfo currentCut;//現在のカットオブジェクト 


	void ChangeAction(const char *ActionName);
	//アニメーションフレームを進める 
	bool ProceedAnimationFrame();
	void ReedActionFile(const char *action_path);
	void DebugDraw();

	bool isTrun;
	//自分の速度
	Vector2f vel;
	//死亡フラグ
	bool DeadFlag;

};

