#include "Map.h"
#include <DxLib.h>
#include "Player.h"

namespace
{
	// マップデータ
	int MapData[NUM_MAP_Y][NUM_MAP_X] =
	{
		// 横24x18
		//マップ11(予備)
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,156,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176},
		{15,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,15},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		// マップ10
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,156,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176, 28, 28, 28, 28, 28, 28, 28,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176, 28,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,176,176, 28,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 28,176, 28,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176, 28,176,176,176, 28,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176, 28,176,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176, 28,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		//マップ9
		{31,176,176, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,31},
		{31,176,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176,176,31},
		{31, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,176,176,31},
		{31,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,31},
		{31,176,176, 28, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,31},
		{31,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176,176,176,176,176,176,31},
		{31, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,176,176, 12, 14,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 29, 30,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 45, 46,176,176,176,31},
		//マップ8
		{31,176,176,176,176,176, 15,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176, 31, 12, 14,176,176,176,176, 12, 14,176,176,176,176,176,176,176,176,31},
		{31, 28,176,176,176,176, 47,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176, 28,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176,176, 28,176,176,176,31},
		{31,176,176, 12, 13, 14,176,176,176,176,176,176,176,176, 28,176,176, 28,176,176, 28,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176, 28, 28, 28,176,176, 28,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 28,176,176, 28, 28, 28, 28, 28,176,176, 28,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176, 28, 28, 28,176,176, 28,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176, 28,176,176, 28,176,176,31},
		{31,176, 12, 13, 14,176,176,176,176,176,176,176,176,176,176, 28,176,176,176, 28,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176, 28,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176, 28, 15, 28,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176, 28, 31, 28,176,176,176,176,176,176,176,176,176,176,31},
		//マップ7
		{31,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 47,176,176,176,176,176,176,176,176,176,176,176,31},
		{31, 12, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 15,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176, 12, 13, 14,176,176, 31,176,176, 12, 14,176, 12, 14,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 47,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 12, 14,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176, 12, 14,176,176,176, 12, 14,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		//マップ6
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31, 12, 14,176,176, 28,176, 28,176, 28,176, 28,176, 12, 13, 14,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 15,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 12, 14,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176, 47, 12, 13, 14,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 12, 14,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176, 28,176,176,176,176,176, 28,176,176,176,176,176,176,31},
		{31,176,176,176,176, 12, 13, 14,176,176,176, 28,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		//マップ5
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176, 12, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176, 12, 13, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176, 28,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,47},
		{31,176,176,176,176,176,176,176,176,176,176,176, 15, 12, 13, 13, 13, 13, 13, 14,176,176, 28,15},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 29, 30, 12, 14, 29, 30,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 45, 46,176,176, 45, 46,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 29, 30,176,176, 29, 30,176,176,31},
		//マップ4
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 45, 46,176,176, 45, 46,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 29, 30,176,176, 29, 30,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 45, 46,176,176, 45, 46,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 12, 13, 13, 14, 15,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31, 12, 13, 14,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 47,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176, 28,176,176,176, 28,176,176,176, 28, 15, 12, 13, 13, 14,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		//マップ3
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 12, 13, 13, 14, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31, 12, 13, 13, 14,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176, 31,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176, 12, 13, 13, 14, 47,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 31,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176, 47, 12, 13, 13, 14,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 12, 13, 13, 13, 13, 13, 13,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176, 12, 14,176,176,176,176,176,176,176,176,31},
		//マップ2
		{31,176,176,176,176,176,176,176,176,176,176,176,176, 29, 30,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176, 45, 46,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176, 176, 12, 13, 13, 13, 13,13, 14,176,176,176,176,176,176,176,176,31},
		{31, 12, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176, 28,176,176, 12, 14,176,176, 12, 14,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 12, 14,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176, 12, 14,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176, 12, 13, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		//マップ1
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176, 12, 14,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,31},
		{31,  8,176,176,176,176,176,176,176,176, 12, 13, 13, 14,176,176,176,176,176,176,176,176,  6,31},
		{31,  6,  8,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,  6,  8,31},
		{31, 22,  6,  8,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,176,  6,  8, 24,31},
		{31, 22, 22,  6,  8,176,176,176,176,176,176,176,176,176,176,176,176,176,176,  6,  8, 24, 24,31},
		{31, 22, 22, 22,  6,  8,176,176,176,176,176,176,176,176,176,176,176,176,  6,  8, 24, 24, 24,31},
		{31, 22, 22, 22, 22,  6,  8,176,176,176,176,176,176,176,176,176,176,  6,  8, 24, 24, 24, 24,31},
		{31, 22, 22, 22, 22, 22,  6,  8,176,176,176,176,176,176,176,176,  6,  8, 24, 24, 24, 24, 24,31},
		{31, 22, 22, 22, 22, 22, 22,  6,  8,176,176,176,176,176,176,  6,  8, 24, 24, 24, 24, 24, 24,31},
		{47, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14,47},

	};

	constexpr float kScrollSpeed = 0.5f;
}

Map::Map() : 
	offset(0),
	mapChangeInterval(0),
	nowStage(0),
	cloudX(0),
	cloudY(0),
	pPlayer(nullptr)
{
}

void Map::init()
{
	//開始時にいるステージ
	nowStage = 1;

	//マップ
	LoadDivGraph("data/b.jpg",
		MapChipAll,
		MapChipX, MapChipY,
		MapSize, MapSize,
		Mchip);
	
	skyH = LoadGraph("data/sora.png");
	cloudH = LoadGraph("data/cloud.png");
	cloudH2 = LoadGraph("data/kumoscroll.png");
}

void Map::updata()
{
	/*雲がスクロールする処理*/
	cloudX -= kScrollSpeed;
	if (cloudX < -Game::kScreenWidth)
	{
		cloudX = 0;
	}
	//下画面から上画面
	bool typeA = pPlayer->getPos() < 0 - MapSize && mapChangeInterval >= 60;
	//上画面から下画面
	bool typeB = pPlayer->getPos() >= Game::kScreenHight && mapChangeInterval >= 6;	//インターバル0.1秒

	//今いるステージで切り分ける
	switch (nowStage)
	{
	case 1:	//ステージ1
		offset = -Game::kScreenHight * (MapStage - 1);
		mapChangeInterval++;
		if (typeA)
		{
			//一つ上のステージに上がる
			nowStage = 2;
			mapChangeInterval = 0;
		}
		break;
	case 2:	//ステージ2
		offset = -Game::kScreenHight * (MapStage - 2);
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
		offset = -Game::kScreenHight * (MapStage - 3);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 4;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 2;
			mapChangeInterval = 0;
		}
		break;
	case 4:	//ステージ4
		offset = -Game::kScreenHight * (MapStage - 4);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 5;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 3;
			mapChangeInterval = 0;
		}
		break;
	case 5:	//ステージ5
		offset = -Game::kScreenHight * (MapStage - 5);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 6;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 4;
			mapChangeInterval = 0;
		}
		break;
	case 6:	//ステージ6
		offset = -Game::kScreenHight * (MapStage - 6);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 7;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 5;
			mapChangeInterval = 0;
		}
		break;
	case 7:	//ステージ5
		offset = -Game::kScreenHight * (MapStage - 7);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 8;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 6;
			mapChangeInterval = 0;
		}
		break;
	case 8:	//ステージ5
		offset = -Game::kScreenHight * (MapStage - 8);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 9;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 7;
			mapChangeInterval = 0;
		}
		break;
	case 9:	//ステージ5
		offset = -Game::kScreenHight * (MapStage - 9);
		mapChangeInterval++;
		if (typeA)
		{
			nowStage = 10;
			mapChangeInterval = 0;
		}
		if (typeB)
		{
			nowStage = 8;
			mapChangeInterval = 0;
		}
		break;
	case 10:	//ステージ5
		offset = -Game::kScreenHight * (MapStage - 10);
		mapChangeInterval++;

		if (typeB)
		{
			nowStage = 9;
			mapChangeInterval = 0;
		}
		break;
	default:
		break;
	}
}

void Map::draw()
{
	DrawGraph(0, 0, skyH, false);
	DrawGraph(cloudX, cloudY, cloudH2, true);
	for (int y = 0; y < NUM_MAP_Y; y++)
	{
		for (int x = 0; x < NUM_MAP_X; x++)
		{
			int posX = x * MapSize;
			int posY = y * MapSize + offset;
			int idx = MapData[y][x];
			DrawGraph(posX, posY, Mchip[idx], FALSE);
			//2は当たり判定チップを表しているので2のところだけ描画
			//if (MapData[y][x] == 2)
			//{
			//	DrawGraph(posX, posY, Mchip[17], FALSE);
			//}
			////3はゴール
			//else if (MapData[y][x] == 3)
			//{
			//	DrawGraph(posX, posY, Mchip[9], FALSE);
			//}
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
