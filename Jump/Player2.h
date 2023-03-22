#pragma once

namespace
{
	constexpr int CChipX = 12;  // 横9種類
	constexpr int CChipY = 10;   // 縦5種類
	constexpr int CChipAll = CChipX * CChipY; // 合計45個
}
namespace
{
	constexpr float G = 0.3f;			//重力
	constexpr float LvMax = 12.5f;	//最大ジャンプ力
	constexpr float Lv5 = 12.0f;	//Lv5
	constexpr float Lv4 = 10.0f;		//Lv4
	constexpr float Lv3 = 8.0f;	//Lv3
	constexpr float Lv2 = 7.0f;	//LV2
	constexpr float Lv1 = 5.0f;	//最小ジャンプ力
	constexpr float Speed = 4.0f;		//移動速度
	//constexpr float MoveSpeed = 2.0f;		//仮

	constexpr int CTLvMax = 100;			//ためジャンプ
	constexpr int CTLv5 = 60;			//ためジャンプ
	constexpr int CTLv4 = 48;			//ためジャンプ
	constexpr int CTLv3 = 36;			//ためジャンプ
	constexpr int CTLv2 = 24;			//ためジャンプ
	constexpr int CTLv1 = 12;			//ためジャンプ

}
class EasyMap;

class Player2
{
public:
	Player2();
	virtual ~Player2();

	void init();
	void updata();
	void draw();

	void effect();
	void jump(float MoveX, float MoveY);
	void cAnimation(bool walk);
	//ステージの情報
	void setStage(EasyMap* map) { pEmap = map; }
	int gameClear() { return clearFlag; }

	//Y座標を送る
	int getPos() { return lineY; }

	int movePlayer(float MoveX, float MoveY);
	int mapHitCheck(float X, float Y, float& MoveX, float& MoveY);

private:
	EasyMap* pEmap;
	float x, y;		// プレイヤーの座標(中心座標)
	float fallSpeed;	// プレイヤーの落下速度

	int	m_size;	// 画像のサイズ（縦横同じ）
	int Cchip[CChipAll];
	int jumpPower;	//ジャンプパワー
	int lineY;		//Y座標
	int test;

	int directionJump = 0;	//ジャンプ方向
	int direction = 0;		//どの方向に飛ぶかを決める
	int chipNum = 0;		//キャラクターのアニメーションs
	int IdelInterval = 0;	//idelインターバル	

	bool idel;
	bool moveFlag;	//ジャンプ中に動けなくするフラグ
	bool jumpAfterInterval;	//ジャンプ後のインターバル 
	bool clearFlag;	//クリアしたかどうか
	bool charge;	//チャージしているかどうか
	bool jumpMotion = false;		//ジャンプモーション
	bool boundFlag;			//壁に当たり反射したか
	bool jumpFlag;	// プレイヤーがジャンプ中か、のフラグ
	bool revers;	//画像を反転させるか
	bool fallFlag;	//落下しているか

};

