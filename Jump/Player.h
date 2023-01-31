#pragma once

namespace
{
	constexpr int CharChipX = 9;  // 横9種類
	constexpr int CharChipY = 5;   // 縦5種類
	constexpr int CharChipAll = CharChipX * CharChipY; // 合計45個
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

	void setStage(Map* map) { pmap = map; }

	int movePlayer(float MoveX, float MoveY);
	int mapHitCheck(float X, float Y, float& MoveX, float& MoveY);

private:
	Map* pmap;
	float x, y;		// プレイヤーの座標(中心座標)
	float fallSpeed;	// プレイヤーの落下速度
	bool jumpFlag;	// プレイヤーがジャンプ中か、のフラグ
	int	m_size;	// 画像のサイズ（縦横同じ）
	int Cchip[CharChipAll];
	int m_offset;
};

