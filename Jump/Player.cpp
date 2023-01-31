#include "Player.h"
#include "game.h"
#include "Pad.h"
#include "Map.h"
#include <DxLib.h>

#define G                (0.3F)                         // �L�����Ɋ|����d�͉����x
#define JUMP_POWER       (10.0f)                         // �L�����̃W�����v��
#define SPEED            (5.0f)                         // �L�����̈ړ��X�s�[�h

Player::Player() : 
	x(0),
	y(0),
	pmap(nullptr)
{
}

Player::~Player()
{
}

void Player::init()
{
	m_size = 32;
	// �v���C���[�̍��W��������
	x = Game::kScreenWidth - 32 * 18;
	y = Game::kScreenHight - 32 * 10;

	// �v���C���[�̗������x��������
	fallSpeed = 0.0f;

	// �W�����v���t���O��|��
	jumpFlag = false;

	//�L�����N�^�[
	LoadDivGraph("data/char.png",
		CharChipAll,
		CharChipX, CharChipY,
		MapSize, MapSize,
		Cchip);
}

void Player::updata()
{
	// �v���C���[�̈ړ�����
	float MoveX, MoveY;

	// �ړ��ʂ̏�����
	MoveX = 0.0f;
	MoveY = 0.0f;

	// ���E�̈ړ�������
	if (Pad::isPress(PAD_INPUT_LEFT))
	{
		//idel = false;
		MoveX -= SPEED;
	}
	if (Pad::isPress(PAD_INPUT_RIGHT))
	{
		//idel = false;
		MoveX += SPEED;
	}
	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
	if (jumpFlag == false)
	{
		if (Pad::isRelase(PAD_INPUT_1))
		{
			//idel = false;
			fallSpeed = -JUMP_POWER;
			jumpFlag = TRUE;
		}
	}
	// �d��
	fallSpeed += G;

	// �������x���ړ��ʂɉ�����
	MoveY = fallSpeed;

	// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
	movePlayer(MoveX, MoveY);
}

void Player::draw()
{
	DrawGraph((int)(x - m_size * 0.5f),
		(int)(y - m_size * 0.5f + pmap->getoffset()), Cchip[0], TRUE);
}

//-----------------------------------------
// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
//-----------------------------------------
int Player::movePlayer(float MoveX, float MoveY)
{
	float Dummy = 0.0f;
	float hsize;

	// �L�����N�^�̍���A�E��A�����A�E�������������蔻��̂���
	// �}�b�v�ɏՓ˂��Ă��邩���ׁA�Փ˂��Ă�����␳����

	// �����̃T�C�Y���Z�o
	hsize = m_size * 0.5f;

	// �悸�㉺�ړ����������Ń`�F�b�N�B���̂��߂Ɉړ��ʂȂ���Dummy�ϐ���n���Ă��܂�
	//---------------------------------------------------------------------//
	// MoveX,MoveY�́u�Q�Ɓv�œn���Ă��܂��B
	// ���̊֐��̒��ŁA�Ԃ������ꍇ�͈ړ��ʂ�␳���āA�ǂɂԂ���O�Ɏ~�߂܂�
	//---------------------------------------------------------------------//
	// �����̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
	if (mapHitCheck(x - hsize, y + hsize, Dummy, MoveY) == 3)
	{
		fallSpeed = 0.0f;
	}

	// �E���̃`�F�b�N�A�����u���b�N�̏�ӂɒ����Ă����痎�����~�߂�
	if (mapHitCheck(x + hsize, y + hsize, Dummy, MoveY) == 3)
	{
		fallSpeed = 0.0f;
	}

	// ����̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
	if (mapHitCheck(x - hsize, y - hsize, Dummy, MoveY) == 4)
	{
		fallSpeed *= -1.0f;
	}

	// �E��̃`�F�b�N�A�����u���b�N�̉��ӂɓ������Ă����痎��������
	if (mapHitCheck(x + hsize, y - hsize, Dummy, MoveY) == 4)
	{
		fallSpeed *= -1.0f;
	}

	// �␳���ꂽ�㉺�ړ����������Z���Ď��ۂɈړ��B�������ĂȂ������炻�̂܂܌v�Z�����
	y += MoveY;

	// ��ɍ��E�ړ����������Ń`�F�b�N
	// �����̃`�F�b�N
	mapHitCheck(x - hsize, y + hsize, MoveX, Dummy);

	// �E���̃`�F�b�N
	mapHitCheck(x + hsize, y + hsize, MoveX, Dummy);

	// ����̃`�F�b�N
	mapHitCheck(x - hsize, y - hsize, MoveX, Dummy);

	// �E��̃`�F�b�N
	mapHitCheck(x + hsize, y - hsize, MoveX, Dummy);

	// ���E�ړ����������Z
	x += MoveX;

	// �ڒn����
		// �L�����N�^�̍����ƉE���̉��ɒn�ʂ����邩���ׂ�
	if (pmap->GetChipParam(x - m_size * 0.5f, y + m_size * 0.5f + 1.0f) == 5)
	{
		// ���ꂪ����������W�����v���ɂ���
		jumpFlag = TRUE;
	}
	else
	{
		// ���ꂪ�݂�����ڒn���ɂ���
		jumpFlag = FALSE;
	}

	// �I��
	return 0;
}

//-----------------------------------------
// �}�b�v�Ƃ̓����蔻��
// �߂�l 0:������Ȃ�����  1:���ӂɓ�������  2:�E�ӂɓ������� 3:��ӂɓ�������  4:���ӂɓ�������
// ���ӁFMoveX �� MoveY�A�ǂ������Е����O����Ȃ��Ƃ܂Ƃ��ɓ��삵�܂���
// MoveX,MoveY�́u�Q�Ɓv�œn���Ă��܂��B
// ���̊֐��̒��ŁA�Ԃ������ꍇ�͈ړ��ʂ�␳���āA�ǂɂԂ���O�Ɏ~�߂܂�
//-----------------------------------------
int Player::mapHitCheck(float X, float Y, float& MoveX, float& MoveY)
{
	float afterX, afterY;

	// �ړ��ʂ𑫂�
	afterX = X + MoveX;
	afterY = Y + MoveY;

	// �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N
	if (pmap->GetChipParam(afterX, afterY) == 10)
	{
		float blockLeftX, blockTopY, blockRightX, blockBottomY;

		// �������Ă�����ǂ��痣���������s��
		// �u���b�N�̏㉺���E�̍��W���Z�o
		blockLeftX = (float)((int)afterX / MapSize) * MapSize;			// ���ӂ� X ���W
		blockRightX = (float)((int)afterX / MapSize + 1) * MapSize;		// �E�ӂ� X ���W

		blockTopY = (float)((int)afterY / MapSize) * MapSize;			// ��ӂ� Y ���W
		blockBottomY = (float)((int)afterY / MapSize + 1) * MapSize;	// ���ӂ� Y ���W

		// ��ӂɓ������Ă����ꍇ
		if (MoveY > 0.0f)
		{
			// �ړ��ʂ�␳����i
			MoveY = blockTopY - Y - 1.0f;

			// ��ӂɓ��������ƕԂ�
			return 3;
		}

		// ���ӂɓ������Ă����ꍇ
		if (MoveY < 0.0f)
		{
			// �ړ��ʂ�␳����
			MoveY = blockBottomY - Y + 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 4;
		}

		// ���ӂɓ������Ă����ꍇ
		if (MoveX > 0.0f)
		{
			// �ړ��ʂ�␳����
			MoveX = blockLeftX - X - 1.0f;

			// ���ӂɓ��������ƕԂ�
			return 1;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (MoveX < 0.0f)
		{
			// �ړ��ʂ�␳����
			MoveX = blockRightX - X + 1.0f;

			// �E�ӂɓ��������ƕԂ�
			return 2;
		}

		// �����ɗ�����K���Ȓl��Ԃ�
		return 4;
	}

	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return 0;
}
