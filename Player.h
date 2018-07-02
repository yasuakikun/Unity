#pragma once
#include "CharaObject.h"
#include "DeadMen.h"
#include "Camera.h"
#include "Game.h"
#include "GamePlayingScene.h"
#include <string>

class GamePlayingScene;
class Peripheral;
class Camera;


//アクション情報によって相手の死に方を変える
enum class AttackType 
{
	non,//何もしない0
	punch,//パンチ
	kick,//キック
	sliding,//スライディング
	swing,//スウィング
	srush,//スラッシュ
	shot//弾を撃つ
};

class Player : public CharaObject
{ 
	friend GamePlayingScene;
public:
	Player(Camera& cam);
	~Player();
	void Draw();
	void Updata(const Peripheral &p);
	//着地したぜ
	//groundline着地点のY座標
	void OnGround(int groundline);
	void DebugDraw();

public:
	//メンバ関数ポインタ
	void (Player::*updataer)(const Peripheral&);
	//状態
	void NeutralUpdata(const Peripheral&);//ニュートラル状態
	void JumpUpdata(const Peripheral&);//ジャンプ状態
	void WalkUpdata(const Peripheral&);//歩き状態
	void CrouchUpdata(const Peripheral&);//しゃがみ状態
	void PunchUpdata(const Peripheral&);//パンチ状態
	void KickUpdata(const Peripheral&);//キック状態
	void DamageUpdata(const Peripheral&);//ダメージ状態
	void GroundUpdata(const Peripheral&);//着地状態
	void SlidingUpdata(const Peripheral&);//スライディング状態
	void RiderUpdata(const Peripheral&);
	void MutekiUpdata(const Peripheral&);
	void DrawPos();
	void Jump();
	void Rider();
	void Crouch();
	void Punch();
	void Kick();
	void Sliding();
	void onDamage();
	void Muteki();

	////フレームのアニメーションを1進める true false

	bool isArial; //飛んでいるかどうか
	AttackType attackType;
	int PlayerImg;
	Rect _rect;
	Camera& camera;
private:
	int waitTimer;
	int damageSE;
	int SlidingSE;
	int PunchSE;
	int frametime;
	bool wait;
	bool MutekiFlag;
	//カメラくらす
};

//publicはクライアントでしか呼べない
//privateはじぶんでしか呼び出せない
//protectedは継承したクライアントでしか呼べない