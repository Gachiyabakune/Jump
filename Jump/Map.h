#pragma once
#include "game.h"
#include "vec2.h"
#include "Player.h"
namespace
{
	// マップチップロード
	constexpr int MapSize = 32;  //マップチップサイズ
	constexpr int MapChipX = 10;  // 横10種類
	constexpr int MapChipY = 4;   // 縦4種類1
	constexpr int MapChipAll = MapChipX * MapChipY; // 合計40個
	constexpr int MapStage = 2;		//ステージ数
	constexpr int NUM_MAP_X = Game::kScreenWidth / MapSize; // 32x24=640
	constexpr int NUM_MAP_Y = (Game::kScreenHight / MapSize) * MapStage; // 32x18=480

}
class Map
{
public:
	Map();
	virtual ~Map(){};
	void init();
	void updata() {};
	void draw();
	int getoffset() { return offset; }
	int GetChipParam(float X, float Y);
private:
	int offset;
	int Mchip[MapChipAll];
};

