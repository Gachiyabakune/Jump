#include "EasyMap.h"
#include <DxLib.h>
#include "Player.h"

namespace
{
	// マップデータ
	int MapData[MAP_Y][MAP_X] =
	{
		// マップ3,
		{15,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,    176,	176,	176,	176,	176,	15},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,    176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	156,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	 12,	 13,	 13,	 13,	 13,	 13,	 13,	 14,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},

		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	 12,	 14,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176, 12, 13, 14,	176,	176,	176,	176,	176,	176,	 12,	 13,	 14,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31, 12, 13, 13,	 14,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	 12,	 13,	 13,	 14,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176, 12, 13, 13,	 13,	 13,     13,	 13,	 13,	 13,	 13,	 13,	 14,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},

		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31, 12, 13, 14,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	 12,	 13,	 14,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176, 12, 13, 14,176,	176,	176,	176,	176,	176,	176,	176,	 12,	 13,	 14,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	 12,     13,	 13,	 14,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,176,176,176,	176,176,176,176,176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	176,	31},
		{31,  6,  7,  7,	  7,  7,  7,  8,176,	176,	176,	176,	176,	176,	176,	176,	  6,	  7,	  7,	  7,	  7,	  7,	  8,	31},
		{31, 23, 23, 23,	 23, 23, 23, 24,176,	176,	176,	176,	176,	176,	176,	176,	 22,	 23,	 23,	 23,	 23,	 23,	 23,	31},
		{31, 23, 23, 23,	 23, 23, 23, 24,176,	176,	176,	176,	176,	176,	176,	176,	 22,	 23,	 23,	 23,	 23,	 23,	 23,	31},
		{31, 23, 23, 23,	 23, 23, 23, 24,176,	176,	176,	176,	176,	176,	176,	176,	 22,	 23,	 23,	 23,	 23,	 23,	 23,	31},
		{47, 12, 13, 13,	 13, 13, 13, 13, 13,	 13,	 13,     13,	 13,	 13,	 13,	 13,	 13,	 13,	 13,	 13,	 13,	 13,	 14,	47},

	};

	//雲のスクロールスピード
	constexpr float kScrollSpeed = 0.5f;
}
EasyMap::EasyMap() :
	offset(0),
	mapChangeInterval(0),
	nowStage(0),
	cloudX(0),
	cloudY(0),
	skyHandle(-1),
	cloudHandle(-1),
	cloudHandle2(-1),
	pPlayer(nullptr)
{
	for (int i = 0; i < 176; i++)
	{
		Mchip[i] = 0;
	}
	for (int i = 0; i < 26; i++)
	{
		goolChip[i] = 0;
	}
}



void EasyMap::init()
{
	//開始時にいるステージ
	nowStage = 1;

	//フラッグ
	/*LoadDivGraph("data/flag.png",
		26,
		26, 1,
		32, 32,
		goolChip);*/
		//マップ
	//LoadDivGraph("data/mapchip.png",
	//	40,
	//	10, 4,
	//	32, 32,
	//	goolChip);
	//マップ
	LoadDivGraph("data/b.jpg",
		ChipAll,
		ChipX, ChipY,
		ChipSize, ChipSize,
		Mchip);


	//背景
	skyHandle = LoadGraph("data/sora.png");
	cloudHandle = LoadGraph("data/cloud.png");
	cloudHandle2 = LoadGraph("data/kumoscroll.png");
}

void EasyMap::updata()
{
	/*雲がスクロールする処理*/
	cloudX -= kScrollSpeed;
	if (cloudX < -Game::kScreenWidth)
	{
		cloudX = 0;
	}
	
	//下画面から上画面 上に上がる
	bool typeA = pPlayer->getPos() < 0 - ChipSize && mapChangeInterval >= 60;
	//上画面から下画面 下に下がる
	bool typeB = pPlayer->getPos() >= Game::kScreenHight && mapChangeInterval >= 6;	//インターバル0.1秒

	//今いるステージで切り分ける
	switch (nowStage)
	{
	case 1:	//ステージ1
		offset = -Game::kScreenHight * (Stage - 1);
		mapChangeInterval++;
		if (typeA)
		{
			//一つ上のステージに上がる
			nowStage = 2;
			mapChangeInterval = 0;
		}
		break;
	case 2:	//ステージ2
		offset = -Game::kScreenHight * (Stage - 2);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 3;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			//一つ下のステージに下がる
			nowStage = 1;
			mapChangeInterval = 0;
		}
		break;
	case 3:	//ステージ3
		offset = -Game::kScreenHight * (Stage - 3);
		mapChangeInterval++;
		if (typeB)
		{
			nowStage = 2;
			mapChangeInterval = 0;
		}
		break;
	}
}

void EasyMap::draw()
{
	DrawGraph(0, 0, skyHandle, false);
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			int posX = x * ChipSize;
			int posY = y * ChipSize + offset;
			int idx = MapData[y][x];
			//if (idx != 156)
			{
				DrawGraph(posX, posY, Mchip[idx], FALSE);
			}
		/*	else if(idx == 156)
			{
				DrawGraph(posX, posY, goolChip[21], FALSE);
			}*/
		}
	}
}

void EasyMap::clearUpdata()
{
	offset++;	//上にずらす
}

int EasyMap::GetChipParam(float X, float Y)
{
	int x, y;

	// 整数値へ変換
	x = (int)X / ChipSize;
	y = (int)Y / ChipSize;

	// マップからはみ出ていたら 0 を返す
	if (x >= MAP_X || y >= MAP_Y || x < 0 || y < 0) return 0;

	// 指定の座標に該当するマップの情報を返す
	return MapData[y][x];
}
