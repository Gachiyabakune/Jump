#include "Map.h"
#include <DxLib.h>

namespace
{
	// マップデータ
	char MapData[NUM_MAP_Y][NUM_MAP_X] =
	{
		// 横24x18
		// マップ2
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,    5,  5,  5, 10, 10,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5, 10, 10,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5, 10, 10,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5, 10, 10,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			// マップ1
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5, 10, 10,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5, 10, 10,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,    5,  5,  5, 10, 10,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5, 10, 10,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5, 10, 10,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5, 10, 10,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},

			{10,  5,  5,  5,  5,   10, 10,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,    5,  5,  5,  5,  5,   5,  5,  5, 10},
			{10, 10, 10, 10, 10,   10, 10, 10, 10, 10,   10, 10, 10, 10, 10,   10, 10, 10, 10, 10,  10, 10, 10, 10},
	};

}
Map::Map()
{
}



void Map::init()
{
	offset = -Game::kScreenHight * (MapStage - 1);
	//offset = 0;

	//マップ
	LoadDivGraph("data/mapchip.png",
		MapChipAll,
		MapChipX, MapChipY,
		MapSize, MapSize,
		Mchip);
}

void Map::draw()
{
	for (int y = 0; y < NUM_MAP_Y; y++)
	{
		for (int x = 0; x < NUM_MAP_X; x++)
		{
			int posX = x * MapSize;
			int posY = y * MapSize + offset;
			// １は当たり判定チップを表しているので１のところだけ描画
			if (MapData[y][x] == 10)
			{
				DrawGraph(posX, posY, Mchip[10], FALSE);
			}
			else if (MapData[y][x] == 5)
			{
				DrawGraph(posX, posY, Mchip[5], FALSE);
				//DrawFormatString(posX, posY, GetColor(255, 255, 255), "10\n壁");
			}
		}
	}
}

int Map::GetChipParam(float X, float Y)
{
	int x, y;

	// 整数値へ変換
	x = (int)X / MapSize;
	y = (int)Y / MapSize;

	// マップからはみ出ていたら 0 を返す
	if (x >= NUM_MAP_X || y >= NUM_MAP_Y || x < 0 || y < 0) return 0;

	// 指定の座標に該当するマップの情報を返す
	return MapData[y][x];
}
