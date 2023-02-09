#pragma once

namespace
{
	constexpr int CharChipX = 9;  // ��9���
	constexpr int CharChipY = 5;   // �c5���
	constexpr int CharChipAll = CharChipX * CharChipY; // ���v45��
}
namespace
{
	constexpr float Gravity = 0.3f;			//�d��
	constexpr float JumpPowerLvMax = 25.0f;	//�ő�W�����v��
	constexpr float JumpPowerLv5 = 12.0f;	//Lv5
	constexpr float JumpPowerLv4 = 10.0f;		//Lv4
	constexpr float JumpPowerLv3 = 8.0f;	//Lv3
	constexpr float JumpPowerLv2 = 7.0f;	//LV2
	constexpr float JumpPowerLv1 = 5.0f;	//�ŏ��W�����v��
	constexpr float MoveSpeed = 4.0f;		//�ړ����x
	//constexpr float MoveSpeed = 2.0f;		//��

	constexpr int ChargeTimeLvMax = 100;			//���߃W�����v
	constexpr int ChargeTimeLv5 = 60;			//���߃W�����v
	constexpr int ChargeTimeLv4 = 48;			//���߃W�����v
	constexpr int ChargeTimeLv3 = 36;			//���߃W�����v
	constexpr int ChargeTimeLv2 = 24;			//���߃W�����v
	constexpr int ChargeTimeLv1 = 12;			//���߃W�����v

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

	//�X�e�[�W�̏��
	void setStage(Map* map) { pmap = map; }
	int gameClear() { return clearFlag; }

	//Y���W�𑗂�
	int getPos() { return lineY; }

	int movePlayer(float MoveX, float MoveY);
	int mapHitCheck(float X, float Y, float& MoveX, float& MoveY);

private:
	Map* pmap;
	float x, y;		// �v���C���[�̍��W(���S���W)
	float fallSpeed;	// �v���C���[�̗������x
	bool jumpFlag;	// �v���C���[���W�����v�����A�̃t���O
	int	m_size;	// �摜�̃T�C�Y�i�c�������j
	int Cchip[CharChipAll];
	int jumpPower;	//�W�����v�p���[
	int lineY;		//Y���W

	bool moveFlag;	//�W�����v���ɓ����Ȃ�����t���O
	int directionJump = 0;	//�W�����v����
	int direction = 0;		//�ǂ̕����ɔ�Ԃ������߂�
	bool jumpAfterInterval;	//�W�����v��̃C���^�[�o�� 
	bool clearFlag = false;

	bool boundFlag;			//�ǂɓ����蔽�˂�����
};

