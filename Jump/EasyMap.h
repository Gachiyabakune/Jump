#pragma once
#include "game.h"
#include "vec2.h"
#include "Player2.h"
namespace
{
	// �}�b�v�`�b�v���[�h
	constexpr int ChipSize = 32;   //�}�b�v�`�b�v�T�C�Y
	constexpr int ChipX = 10;  // ��10���
	constexpr int ChipY = 4;   // �c4���1
	constexpr int ChipAll = ChipX * ChipY; // ���v40��
	constexpr int Stage = 3;		//�X�e�[�W��
	constexpr int MAP_X = 24;
	constexpr int MAP_Y = 18 * Stage;

}

class Player2;

class EasyMap
{
public:
	EasyMap();
	virtual ~EasyMap() {};
	void init();
	void updata();
	void draw();

	void clearUpdata();

	void setPlayer(Player2* player) { pPlayer = player; }

	int getoffset() { return offset; }
	int GetChipParam(float X, float Y);
private:
	Player2* pPlayer;
	int offset;
	int Mchip[ChipAll];
	int nowStage;
	int mapChangeInterval;
	int skyHandle;
	int cloudHandle;
	int cloudHandle2;

	float cloudX, cloudY;

};

