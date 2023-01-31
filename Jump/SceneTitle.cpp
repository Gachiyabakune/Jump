#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Pad.h"
#include "game.h"

typedef enum 
{
	eMenu_Game,         //�Q�[��
	eMenu_Config,       //�ݒ�
	eMenu_End,			//�I��
	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Game;    //���݂̑I�����(�����̓Q�[���I��)

void SceneTitle::init()
{
	m_isEnd = false;
	m_interval = 0;
}

SceneBase* SceneTitle::update()
{
	//�Q�[���X�^�[�g
	//if (Pad::isTrigger(PAD_INPUT_1))
	
	if(CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		switch (NowSelect)
		{
		case eMenu_Game:
			return (new SceneMain);
		case eMenu_End:
			DxLib_End();
			printfDx("aaa");
		case eMenu_Config:
		
			SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

			//�|�[�Y�E�B���h�E�Z���t�@��(����)
			DrawBox(40, 40, 600, 440, GetColor(0,255,0), true);

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�ʏ�`��ɖ߂�

			//�|�[�Y�����b�Z�[�W
			DrawString(40 + 10, 40 + 10, "Pausing...", 0xffff88);

			//�|�[�Y�E�B���h�E�g��
			DrawBox(40, 40, 600, 440, GetColor(0, 255, 255), false);
		default:
			break;
		}
		
	}
	//��
	if (Pad::isTrigger(PAD_INPUT_UP)&& m_interval == 0)
	{
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		m_interval = 10;
	}
	//��
	if (Pad::isTrigger(PAD_INPUT_DOWN)&& m_interval == 0)
	{
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		m_interval = 10;
	}
	//�C���^�[�o��
	if (m_interval != 0)
	{
		m_interval--;
	}
	
	return this;
}

void SceneTitle::draw()
{
	int y = 0;
	DrawString(200, 150, "���j���[��ʂł��B", GetColor(255, 255, 255));
	DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 - 30,
		"�Q�[��", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2,
		"�I�v�V����", GetColor(255, 255, 255));
	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 30,
		"�I��", GetColor(255, 255, 255));
	switch (NowSelect)
	{//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Game://�Q�[���I�𒆂Ȃ�
		y = 258;    //�Q�[���̍��W���i�[
		break;
	case eMenu_Config:
		y = 288;
		break;
	case eMenu_End://�ݒ�I�𒆂Ȃ�
		y = 318;
		//�ݒ�̍��W���i�[
		break;
	}

	DrawString(Game::kScreenWidth / 2 - 70, y, "��", GetColor(255, 0, 255));
}