#pragma once

namespace
{
	constexpr int CharChipX = 9;  // ��9���
	constexpr int CharChipY = 5;   // �c5���
	constexpr int CharChipAll = CharChipX * CharChipY; // ���v45��
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
	float x, y;		// �v���C���[�̍��W(���S���W)
	float fallSpeed;	// �v���C���[�̗������x
	bool jumpFlag;	// �v���C���[���W�����v�����A�̃t���O
	int	m_size;	// �摜�̃T�C�Y�i�c�������j
	int Cchip[CharChipAll];
	int m_offset;
};

