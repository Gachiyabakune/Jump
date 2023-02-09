#pragma once

namespace
{
	constexpr int CharChipX = 9;  // 横9種類
	constexpr int CharChipY = 5;   // 縦5種類
	constexpr int CharChipAll = CharChipX * CharChipY; // 合計45個
}
namespace
{
	constexpr float Gravity = 0.3f;			//重力
	constexpr float JumpPowerLvMax = 25.0f;	//最大ジャンプ力
	constexpr float JumpPowerLv5 = 12.0f;	//Lv5
	constexpr float JumpPowerLv4 = 10.0f;		//Lv4
	constexpr float JumpPowerLv3 = 8.0f;	//Lv3
	constexpr float JumpPowerLv2 = 7.0f;	//LV2
	constexpr float JumpPowerLv1 = 5.0f;	//最小ジャンプ力
	constexpr float MoveSpeed = 4.0f;		//移動速度
	//constexpr float MoveSpeed = 2.0f;		//仮

	constexpr int ChargeTimeLvMax = 100;			//ためジャンプ
	constexpr int ChargeTimeLv5 = 60;			//ためジャンプ
	constexpr int ChargeTimeLv4 = 48;			//ためジャンプ
	constexpr int ChargeTimeLv3 = 36;			//ためジャンプ
	constexpr int ChargeTimeLv2 = 24;			//ためジャンプ
	constexpr int ChargeTimeLv1 = 12;			//ためジャンプ

}
class Map;

class Player
{
public:
	Player();
	virtual ~Player();

	void init();
	void updata();
	void draw();

	//ステージの情報
	void setStage(Map* map) { pmap = map; }
	int gameClear() { return clearFlag; }

	//Y座標を送る
	int getPos() { return lineY; }

	int movePlayer(float MoveX, float MoveY);
	int mapHitCheck(float X, float Y, float& MoveX, float& MoveY);

private:
	Map* pmap;
	float x, y;		// プレイヤーの座標(中心座標)
	float fallSpeed;	// プレイヤーの落下速度
	bool jumpFlag;	// プレイヤーがジャンプ中か、のフラグ
	int	m_size;	// 画像のサイズ（縦横同じ）
	int Cchip[CharChipAll];
	int jumpPower;	//ジャンプパワー
	int lineY;		//Y座標

	bool moveFlag;	//ジャンプ中に動けなくするフラグ
	int directionJump = 0;	//ジャンプ方向
	int direction = 0;		//どの方向に飛ぶかを決める
	bool jumpAfterInterval;	//ジャンプ後のインターバル 
	bool clearFlag = false;

	bool boundFlag;			//壁に当たり反射したか
};

