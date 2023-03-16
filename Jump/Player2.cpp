#include "Player2.h"
#include "game.h"
#include "Pad.h"
#include "EasyMap.h"
#include "Sound.h"
#include <DxLib.h>

Player2::Player2() :
	x(0),
	y(0),
	pEmap(nullptr),
	moveFlag(false),
	jumpAfterInterval(true),
	boundFlag(false),
	jumpFlag(false),
	revers(false),
	idel(true),
	clearFlag(false),
	charge(false),
	jumpPower(0)
{
}

Player2::~Player2()
{
}

void Player2::init()
{
	//�L�����̃T�C�Y
	m_size = 30;
	// �v���C���[�̍��W��������
	x = Game::kScreenWidth - ChipSize * 12;
	y = Game::kScreenHight * Stage - ChipSize;

	// �v���C���[�̗������x��������
	fallSpeed = 0.0f;

	//�L�����N�^�[
	LoadDivGraph("data/texture.png",
		CChipAll,
		CChipX, CChipY,
		48, 48,
		Cchip);

	//���ʐݒ�
	Sound::setVolume(Sound::SoundId_Jump, 200);
}

void Player2::updata()
{
	// �v���C���[�̈ړ�����
	float MoveX, MoveY;

	// �ړ��ʂ̏�����
	MoveX = 0.0f;
	MoveY = 0.0f;

	//-----���E�̈ړ�������-----
	bool walk = false;		//�����Ă��邩�ǂ���

	//���������Ă��鎞���W�����v���ł��Ȃ���
	if ((Pad::isPress(PAD_INPUT_LEFT) && !moveFlag))
	{
		//�����ł���̂�idel��Ԃɂ͂��Ȃ�
		idel = false;
		MoveX -= Speed;
		revers = false;
		walk = true;
	}
	//�E�������Ă��鎞���W�����v���ł��Ȃ���
	if ((Pad::isPress(PAD_INPUT_RIGHT) && !moveFlag))
	{
		//�����ł���̂�idel��Ԃɂ͂��Ȃ�
		idel = false;
		MoveX += Speed;
		revers = true;
		walk = true;
	}
	//�W�����v�����ō����I�����ꂽ�ꍇ
	if (directionJump == 1)
	{
		if (!boundFlag)
		{
			MoveX -= Speed;	//�o�E���h���Ȃ��Ԃ͍�������
			revers = false;
		}
		else
		{
			MoveX += Speed;	//�o�E���h����Ƌt������
			revers = true;
		}
	}
	//�W�����v�����ŉE���I�����ꂽ�ꍇ
	else if (directionJump == 2)
	{
		if (!boundFlag)
		{
			MoveX += Speed;	//�o�E���h���Ȃ��Ԃ͉E������
			revers = true;
		}
		else
		{
			MoveX -= Speed;	//�o�E���h����Ƌt������
			revers = false;
		}
	}
	//�W�����v����
	jump(MoveX, MoveY);
	//�L�����N�^�[�̃A�j���[�V����
	cAnimation(walk);
	
#ifdef _DEBUG
	if (Pad::isPress(PAD_INPUT_4))
	{
		y -= 10;
	}
	else
	{
		// �d��
		fallSpeed += G;
	}

#else
	// �d��
	fallSpeed += G;
#endif
	// �������x���ړ��ʂɉ�����
	MoveY = fallSpeed;

	//lineY��Y���W��offset���݂̐��l����
	lineY = (int)(y - m_size * 0.5f + pEmap->getoffset());

	// �ړ��ʂɊ�Â��ăL�����N�^�̍��W���ړ�
	movePlayer(MoveX, MoveY);
}

void Player2::draw()
{
	//�L�����N�^�[�`��
	//���͂��������ŃL�����������Ă��������ς���
	if (revers)
	{
		DrawGraph((int)(x - 48 * 0.5f),
			(int)(y - 48 * 0.5f + pEmap->getoffset()),
			Cchip[chipNum], TRUE);
	}
	else
	{
		DrawTurnGraph((int)(x - 48 * 0.5f),
			(int)(y - 48 * 0.5f + pEmap->getoffset()),
			Cchip[chipNum], TRUE);
	}
#ifdef _DEBUG
	//�l�p ��ׂ�Ƃ��͐ԐF,��ׂȂ����͉��F
	if (!jumpFlag)
	{
		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pEmap->getoffset()),
			(int)(x - m_size * 0.5f) + m_size,
			(int)(y - m_size * 0.5f + pEmap->getoffset()) + m_size,
			GetColor(255, 0, 0), false);
	}
	else
	{

		DrawBox((int)(x - m_size * 0.5f),
			(int)(y - m_size * 0.5f + pEmap->getoffset()),
			(int)(x - m_size * 0.5f) + ChipSize,
			(int)(y - m_size * 0.5f + pEmap->getoffset()) + ChipSize,
			GetColor(255, 255, 0), false);
	}

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "%d", lineY);	//Y���W	
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%d", (int)(x - m_size * 0.5f));	//X���W
	DrawFormatString(0, 40, GetColor(255, 255, 255), "dir : %d", direction);	//Y���W	
	DrawFormatString(0, 60, GetColor(255, 255, 255), "dirJ : %d", directionJump);	//Y���W	

	DrawFormatString(0, 80, GetColor(255, 255, 255), " Jpower : %d", jumpPower);	//�W�����v�p���[
	DrawFormatString(0, 200, GetColor(255, 255, 255), "%d", chipNum);
#endif
}

void Player2::effect()
{
}

void Player2::jump(float MoveX, float MoveY)
{
	// �n�ɑ��������Ă���ꍇ�̂݃W�����v�{�^��(�{�^���P or �y�L�[)������
	if (!jumpFlag)
	{
		if (Pad::isPress(PAD_INPUT_1))
		{
			//���߂Ă���Ԃ͓����Ȃ�����
			moveFlag = true;
			//�����ł���̂�idel��Ԃɂ͂��Ȃ�
			idel = false;
			//�W�����v�p���[�`���[�W
			jumpPower++;
			charge = true;	//�`���[�W���Ă���	
			//�W�����v���ɂǂ̕����ɔ�Ԃ̂�������
			if (Pad::isPress(PAD_INPUT_LEFT))
			{
				direction = 1;	//���ɔ�ԂȂ�1
				revers = false;	//�L�����̔��]
			}
			else if (Pad::isPress(PAD_INPUT_RIGHT))
			{
				direction = 2;	//�E�ɔ�ԂȂ�2
				revers = true;	//�L�����̔��]
			}
			else
			{
				direction = 0;
			}
		}
		//�{�^���𗣂��������J�E���g�����܂�Ƌ����W�����v
		if (Pad::isRelase(PAD_INPUT_1) || jumpPower == CTLvMax)
		{
			//���ߒi�K���Z���Ə��W�����v
			if (CTLv1 >= jumpPower)
			{
				fallSpeed = -Lv1;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//���x��2�W�����v
			else if (CTLv2 >= jumpPower && jumpPower > CTLv1)
			{
				fallSpeed = -Lv2;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//���x��3�W�����v
			else if (CTLv3 >= jumpPower && jumpPower >= CTLv2)
			{
				fallSpeed = -Lv3;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//���x��4�W�����v
			else if (CTLv4 >= jumpPower && jumpPower >= CTLv3)
			{
				fallSpeed = -Lv4;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//���x��5�W�����v
			else if (CTLvMax > jumpPower && jumpPower >= CTLv4)
			{
				fallSpeed = -Lv5;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}
			//���x��Max�W�����v
			else if (CTLvMax == jumpPower)
			{
				fallSpeed = -LvMax;
				if (direction == 1)
				{
					directionJump = 1;
				}
				else if (direction == 2)
				{
					directionJump = 2;
				}
			}

			jumpFlag = true;				//�W�����v���Ƀt���O��ύX
			jumpAfterInterval = false;		//�W�����v��̃C���^�[�o��
			charge = false;					//�`���[�W���[�V����������
			jumpPower = 0;					//�W�����v�p���[�����ɖ߂�
			jumpMotion = true;

			Sound::play(Sound::SoundId_Jump);
		}
	}
	//���ł��Ȃ��Ƃ��ɕK�v�ȏ�������������
	if (!jumpFlag && !jumpAfterInterval)
	{
		//Sound::play(Sound::SoundId_fall);
		moveFlag = false;
		directionJump = 0;
		direction = 0;
		jumpAfterInterval = true;
		boundFlag = false;
		jumpMotion = false;
	}
}

//�L�����N�^�[�̃A�j���[�V����
void Player2::cAnimation(bool walk)
{
	//�����Ă���Ƃ�
	if (walk)
	{
		if (chipNum < 10)
		{
			chipNum = 72;
		}
		if (IdelInterval == 6)
		{
			chipNum++;
			IdelInterval = 0;
		}
		if (chipNum == 79)
		{
			chipNum = 72;
		}
		IdelInterval++;
	}
	////idel���
	//else if (idel)
	//{
	//	IdelInterval++;
	//	if (chipNum > 9)
	//	{
	//		chipNum = 0;
	//	}
	//	if (IdelInterval == 10)
	//	{
	//		chipNum++;
	//		IdelInterval = 0;
	//	}
	//}
	//�W�����v�O�`���[�W
	else if (charge)
	{
		chipNum = 107;
	}
	//�W�����v��
	else if (jumpMotion)
	{
		chipNum = 59;
	}
	else
	{
		chipNum = 0;
	}
}

//-----------------------------------------
// �L�����N�^���}�b�v�Ƃ̓����蔻����l�����Ȃ���ړ�����
//-----------------------------------------
int Player2::movePlayer(float MoveX, float MoveY)
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
	if (pEmap->GetChipParam(x + m_size * 0.5f - 16.0f, y + m_size * 0.5f + 1.0f) == 176)
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
int Player2::mapHitCheck(float X, float Y, float& MoveX, float& MoveY)
{
	float afterX, afterY;

	// �ړ��ʂ𑫂�
	afterX = X + MoveX;
	afterY = Y + MoveY;

	// �����蔻��̂���u���b�N�ɓ������Ă��邩�`�F�b�N
	if (pEmap->GetChipParam(afterX, afterY) == 12 || pEmap->GetChipParam(afterX, afterY) == 13 ||
		pEmap->GetChipParam(afterX, afterY) == 14 || pEmap->GetChipParam(afterX, afterY) == 15 ||
		pEmap->GetChipParam(afterX, afterY) == 22 || pEmap->GetChipParam(afterX, afterY) == 23 || 
		pEmap->GetChipParam(afterX, afterY) == 24 || pEmap->GetChipParam(afterX, afterY) == 6  || 
		pEmap->GetChipParam(afterX, afterY) ==  7 || pEmap->GetChipParam(afterX, afterY) == 8  || 
		pEmap->GetChipParam(afterX, afterY) == 31 || pEmap->GetChipParam(afterX, afterY) == 47 )
	{
		float blockLeftX, blockTopY, blockRightX, blockBottomY;

		// �������Ă�����ǂ��痣���������s��
		// �u���b�N�̏㉺���E�̍��W���Z�o
		blockLeftX = (float)((int)afterX / ChipSize) * ChipSize;			// ���ӂ� X ���W
		blockRightX = (float)((int)afterX / ChipSize + 1) * ChipSize;		// �E�ӂ� X ���W

		blockTopY = (float)((int)afterY / ChipSize) * ChipSize;			// ��ӂ� Y ���W
		blockBottomY = (float)((int)afterY / ChipSize + 1) * ChipSize;	// ���ӂ� Y ���W

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
			if (!boundFlag)
			{
				boundFlag = true;
			}
			else
			{
				boundFlag = false;
			}
			// ���ӂɓ��������ƕԂ�
			return 1;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (MoveX < 0.0f)
		{
			// �ړ��ʂ�␳����
			MoveX = blockRightX - X + 1.0f;
			//�ǂɓ�����Ɣ��˃t���O���I��
			if (!boundFlag)
			{
				boundFlag = true;
			}
			//������񓖂���ƌ��ɖ߂�
			else
			{
				boundFlag = false;
			}
			// �E�ӂɓ��������ƕԂ�
			return 2;
		}

		// �����ɗ�����K���Ȓl��Ԃ�
		return 4;
	}

	/*------�N���A�̎�(156�ɓ���������)�t���O��Ԃ�------*/
	if (pEmap->GetChipParam(afterX, afterY) == 156)
	{
		float blockLeftX, blockTopY, blockRightX, blockBottomY;

		// �������Ă�����ǂ��痣���������s��
		// �u���b�N�̏㉺���E�̍��W���Z�o
		blockLeftX = (float)((int)afterX / ChipSize) * ChipSize;			// ���ӂ� X ���W
		blockRightX = (float)((int)afterX / ChipSize + 1) * ChipSize;		// �E�ӂ� X ���W

		blockTopY = (float)((int)afterY / ChipSize) * ChipSize;			// ��ӂ� Y ���W
		blockBottomY = (float)((int)afterY / ChipSize + 1) * ChipSize;	// ���ӂ� Y ���W

		// ��ӂɓ������Ă����ꍇ
		if (MoveY > 0.0f)
		{
			clearFlag = true;	//�N���A�ɂ���
		}

		// ���ӂɓ������Ă����ꍇ
		if (MoveY < 0.0f)
		{
			clearFlag = true;
		}

		// ���ӂɓ������Ă����ꍇ
		if (MoveX > 0.0f)
		{
			clearFlag = true;
		}

		// �E�ӂɓ������Ă����ꍇ
		if (MoveX < 0.0f)
		{
			clearFlag = true;
		}

		// �����ɗ�����K���Ȓl��Ԃ�
		return 4;
	}
	// �ǂ��ɂ�������Ȃ������ƕԂ�
	return 0;
}
