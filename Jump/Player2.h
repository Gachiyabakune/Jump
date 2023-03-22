#pragma once

namespace
{
	constexpr int CChipX = 12;  // ��9���
	constexpr int CChipY = 10;   // �c5���
	constexpr int CChipAll = CChipX * CChipY; // ���v45��
}
namespace
{
	constexpr float G = 0.3f;			//�d��
	constexpr float LvMax = 12.5f;	//�ő�W�����v��
	constexpr float Lv5 = 12.0f;	//Lv5
	constexpr float Lv4 = 10.0f;		//Lv4
	constexpr float Lv3 = 8.0f;	//Lv3
	constexpr float Lv2 = 7.0f;	//LV2
	constexpr float Lv1 = 5.0f;	//�ŏ��W�����v��
	constexpr float Speed = 4.0f;		//�ړ����x
	//constexpr float MoveSpeed = 2.0f;		//��

	constexpr int CTLvMax = 100;			//���߃W�����v
	constexpr int CTLv5 = 60;			//���߃W�����v
	constexpr int CTLv4 = 48;			//���߃W�����v
	constexpr int CTLv3 = 36;			//���߃W�����v
	constexpr int CTLv2 = 24;			//���߃W�����v
	constexpr int CTLv1 = 12;			//���߃W�����v

}
class EasyMap;

class Player2
{
public:
	Player2();
	virtual ~Player2();

	void init();
	void updata();
	void draw();

	void effect();
	void jump(float MoveX, float MoveY);
	void cAnimation(bool walk);
	//�X�e�[�W�̏��
	void setStage(EasyMap* map) { pEmap = map; }
	int gameClear() { return clearFlag; }

	//Y���W�𑗂�
	int getPos() { return lineY; }

	int movePlayer(float MoveX, float MoveY);
	int mapHitCheck(float X, float Y, float& MoveX, float& MoveY);

private:
	EasyMap* pEmap;
	float x, y;		// �v���C���[�̍��W(���S���W)
	float fallSpeed;	// �v���C���[�̗������x

	int	m_size;	// �摜�̃T�C�Y�i�c�������j
	int Cchip[CChipAll];
	int jumpPower;	//�W�����v�p���[
	int lineY;		//Y���W
	int test;

	int directionJump = 0;	//�W�����v����
	int direction = 0;		//�ǂ̕����ɔ�Ԃ������߂�
	int chipNum = 0;		//�L�����N�^�[�̃A�j���[�V����s
	int IdelInterval = 0;	//idel�C���^�[�o��	

	bool idel;
	bool moveFlag;	//�W�����v���ɓ����Ȃ�����t���O
	bool jumpAfterInterval;	//�W�����v��̃C���^�[�o�� 
	bool clearFlag;	//�N���A�������ǂ���
	bool charge;	//�`���[�W���Ă��邩�ǂ���
	bool jumpMotion = false;		//�W�����v���[�V����
	bool boundFlag;			//�ǂɓ����蔽�˂�����
	bool jumpFlag;	// �v���C���[���W�����v�����A�̃t���O
	bool revers;	//�摜�𔽓]�����邩
	bool fallFlag;	//�������Ă��邩

};

