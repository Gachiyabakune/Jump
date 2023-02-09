#pragma once
#include "game.h"
#include "vec2.h"
#include "Player.h"
namespace
{
	// �}�b�v�`�b�v���[�h
	constexpr int MapSize = 32;   //�}�b�v�`�b�v�T�C�Y
	constexpr int MapChipX = 10;  // ��10���
	constexpr int MapChipY = 4;   // �c4���1
	constexpr int MapChipAll = MapChipX * MapChipY; // ���v40��
	constexpr int MapStage = 10;		//�X�e�[�W��
	constexpr int NUM_MAP_X = Game::kScreenWidth / MapSize; 
	constexpr int NUM_MAP_Y = (Game::kScreenHight / MapSize) * MapStage; 

}

class Player;

class Map
{
public:
	Map();
	virtual ~Map(){};
	void init();
	void updata();
	void draw();
	
	void setPlayer(Player* player) { pPlayer = player; }

	int getoffset() { return offset; }
	int GetChipParam(float X, float Y);
private:
	Player* pPlayer;
	int offset;
	int Mchip[MapChipAll];
	int nowStage;
	int mapChangeInterval;
	int skyH;
	int cloudH;
	int cloudH2;
};

