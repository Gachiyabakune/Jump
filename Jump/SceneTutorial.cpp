#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "DxLib.h"
#include "Sound.h"
#include "Pad.h"
#include "game.h"
#include <cassert>

namespace
{
	//�e�L�X�g
	const char* const kTitkeMessage = "GAME CLEAR";
	constexpr int kStandbyTime = 60;	//�N���A�ォ��t�H���g���o�Ă���܂ł̎���
	constexpr int kStandbyTime2 = 180;	//�����L���O�Ȃǂ��o�Ă��鎞��
}
namespace
{
	// �^�C�g���ƃT���v���̐���
	const char* const kMenuItemMessage[] =
	{
		"�ŏ�����",
		"������",
		"�^�C�g����",
	};
	// �J�[�\��
	constexpr int kCursorMoveFrame = 6;
}

SceneTutorial::SceneTutorial():
	textHeight(0),
    textWidth(0),
    textDispWidth(0),
    fontHandle(0),
	m_timeTaken(0),
	m_timer(0),
	handle(0),
	hiscore(0),
	option(false),
	changeScene(false)
{
	m_seq = Seq::SeqFadeIn;
	frstPlaceTime = 10000;
}

SceneTutorial::~SceneTutorial()
{
	delete(player);
	delete(map);
}

void SceneTutorial::init()
{
	player->setStage(map);
	player->init();
	map->setPlayer(player);
	map->init();

	//���݂̃V�[�P���X
	m_seq = Seq::SeqFadeIn;

	m_timeTaken = 0;	//�o�ߎ���

	hiscore = 1000;			//�n�C�X�R�A

	changeScene = false;	//�V�[���؂�ւ�

	//BGM���Đ�
	Sound::startBgm(Sound::SoundId_BgmEasy,0);

	//�t�H���g
	fontHandle = CreateFontToHandle("Playbill", 100, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	menuItemHandle = CreateFontToHandle("���S�V�b�N�@��", 32, 8, DX_FONTTYPE_ANTIALIASING_8X8);
	//��������O���t�B�b�N��
	textHeight = 100;
	textWidth = GetDrawStringWidthToHandle(kTitkeMessage, static_cast<int>(strlen(kTitkeMessage)), fontHandle);
	// ������O���t�B�b�N�𐶐�
	handle = MakeScreen(textWidth, textHeight, true);

	SetDrawScreen(handle);
	DrawStringToHandle(0, 0, kTitkeMessage, GetColor(255, 255, 0), fontHandle);
	//�_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
}

SceneBase* SceneTutorial::update()
{
	switch (m_seq)
	{
	case Seq::SeqFadeIn:
		FadeInUpdate();
		break;
	case Seq::SeqUpdata:
		NormalUpdate();
		break;
	case Seq::SeqClearUpdata:
		ClearUpdate();
		break;
	case Seq::SeqFadeOut:
		FadeOutUpdate();
		break;
	case Seq::SeqOption:
		OptionUpdate();
		break;
	}

	if (changeScene)
	{
		return(new SceneTitle);
	}
	
	return this;
}

void SceneTutorial::draw()
{
	map->draw();
	player->draw();
	if (player->gameClear())
	{
		drawClear();
	}
	if (option)
	{
		drawOption();
	}
	if (option)
	{
		DrawString(0, 260, "true",GetColor(255, 255, 255));
	}
	else
	{
		DrawString(0, 260, "false", GetColor(255, 255, 255));
	}
	
	//�����珑���摜�ƁA���łɕ`�悳��Ă���X�N���[���Ƃ�
   //�u�����h�̎d�����w�肵�Ă���B
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	//��ʑS�̂�^�����ɓh��Ԃ�
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHight, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneTutorial::FadeInUpdate()
{
	player->updata();
	map->updata();
	//�^�������珙�X�ɕ\������ꍇ�ꍇ
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
	//�O���f�[�V�������g���ď��X�ɕ\������ꍇ
	/*fadeTimer_;*/
	if (fadeTimer-- == 0)
	{
		m_seq = Seq::SeqUpdata;
		fadeValue = 0;
	}
}

void SceneTutorial::NormalUpdate()
{
	player->updata();
	map->updata();
	//�N���A�����
	if (player->gameClear())
	{
		m_seq = Seq::SeqClearUpdata;
	}
	m_timeTaken++;

	int volume = 0;
	volume += m_timeTaken * 2;
	if (volume > 100)	volume = 100;
	Sound::setVolume(Sound::SoundId_BgmEasy, volume);

	//�|�[�Y
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_seq = Seq::SeqOption;
		option = true;
	}
}

void SceneTutorial::ClearUpdate()
{
	map->clearUpdata();
	refreshScore();
	m_timer++;	//�^�C�}�[
	frstPlaceTime = m_timeTaken / 60;
	if (m_timer > kStandbyTime)	//10�b�ԃX�N���[���������
	{
		textDispWidth++;
	}

	//�N���A����Ƃ��񂾂�BGM���������Ȃ�
	int volume = 100;
	volume -= m_timer * 2;
	if (volume < 0)	volume = 0;
	Sound::setVolume(Sound::SoundId_BgmEasy, volume);

	//volume��0�ɂȂ��BGM��~
	if (volume == 0)
	{
		Sound::stopBgm(Sound::SoundId_BgmEasy);
	}
	//�N���A��Y�{�^���������ƃ^�C�g����
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		m_seq = Seq::SeqFadeOut;
	}
}

void SceneTutorial::FadeOutUpdate()
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
	if (fadeTimer++ == fade_interval)
	{
		changeScene = true;
	}
}

void SceneTutorial::OptionUpdate()
{
	if (Pad::isTrigger(PAD_INPUT_8))
	{
		m_seq = Seq::SeqUpdata;
		option = false;
	}

	sinRate += 0.1f;

	//���L�[
	if (Pad::isTrigger(PAD_INPUT_DOWN) && m_interval == 0)
	{
		cursorNext++;
		if (cursorNext > _countof(kMenuItemMessage) - 1)
		{
			cursorNext = 0;
		}
		cursorMoveFrame = kCursorMoveFrame;
		m_interval = 6;
		Sound::play(Sound::SoundId_Select);
	}
	//��L�[
	else if (Pad::isTrigger(PAD_INPUT_UP) && m_interval == 0)
	{
		cursorNext--;
		if (cursorNext == -1)
		{
			cursorNext = _countof(kMenuItemMessage) - 1;
		}
		cursorMoveFrame = kCursorMoveFrame;
		m_interval = 6;
		Sound::play(Sound::SoundId_Select);
	}
	if (cursorIndex != cursorNext)
	{
		cursorMoveFrame--;
		if (cursorMoveFrame <= 0)
		{
			cursorIndex = cursorNext;
			cursorMoveFrame = 0;
		}
	}
	//�C���^�[�o��
	if (m_interval != 0)
	{
		m_interval--;
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		//Sound::stopBgm(Sound::SoundId_BgmTitle);
		switch (cursorIndex)
		{
		case 0:
			//Sound::play(Sound::SoundId_Decision);
			//return (new SceneTutorial);
			break;
		case 1:
			//Sound::play(Sound::SoundId_Decision);
			//return (new SceneMain);
			break;
		case 2:
			//Sound::play(Sound::SoundId_Decision);
			//return (new SceneOption);
			break;
		}
	}
}

void SceneTutorial::drawClear()
{
	if (m_timer > kStandbyTime)	//10�b�ԃX�N���[���������
	{
		DrawRectGraph(200, 50 + 100, 0, 0, textDispWidth, textHeight, handle, true);
		for (int i = 0; i < 8; i++)
		{
			int x = 200 + textDispWidth + i * 2;
			int y = 50 + 100 + i * 2;
			DrawRectGraph(x, y,
				textDispWidth + i * 2, 0,
				2, textHeight, handle, true);
		}
	}
	if (m_timer > kStandbyTime2)
	{
		DrawFormatString(250, 400, GetColor(255, 255, 255), "�^�C��%d�b", frstPlaceTime);	//Y���W

		if (frstPlaceTime < hiscore)
		{
			DrawFormatString(250, 430, GetColor(255, 255, 255), "�����L���O1�ʂɂȂ�܂���:%d�b", frstPlaceTime);
		}
		else if (frstPlaceTime > hiscore)
		{
			DrawFormatString(250, 430, GetColor(255, 255, 255), "�����L���O1�ʂ̃^�C��:%d�b", hiscore);
		}
		else
		{
			DrawFormatString(250, 430, GetColor(255, 255, 255), "�����L���O1�ʂɂȂ�܂���:%d�b", frstPlaceTime);
		}

		DrawString(250, 460, "Y�{�^���Ń^�C�g����", GetColor(255, 255, 255));
	}
}

void SceneTutorial::drawOption()
{
	constexpr int pw_width = 500;	//�|�[�Y�g�̕�
	constexpr int pw_height = 400;	//�|�[�Y�g�̍���
	constexpr int pw_start_x = (Game::kScreenWidth - pw_width) / 2;	//�|�[�Y�g�̍�
	constexpr int pw_start_y = (Game::kScreenHight - pw_height) / 2;	//�|�[�Y�g��

	SetDrawBlendMode(DX_BLENDMODE_MULA, 196);

	//�|�[�Y�E�B���h�E�Z���t�@��(����)
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, GetColor(0, 0, 0), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//�ʏ�`��ɖ߂�

	//�|�[�Y�����b�Z�[�W
	DrawString(pw_start_x + 10, pw_start_y + 10, "Pausing...", 0xffff88);

	//�|�[�Y�E�B���h�E�g��
	DrawBox(pw_start_x, pw_start_y, pw_start_x + pw_width, pw_start_y + pw_height, 0xffffff, false);

	float cursorY = 0.0f;
	for (int i = 0; i < _countof(kMenuItemMessage); i++)
	{
		int r = 0x80;
		int g = 0x80;
		int b = 0x80;
		int posY = 330 + 32 * i;
		if (cursorIndex == cursorNext)
		{
			if (cursorIndex == i)
			{
				r = 0xff;
				g = 0x40;
				b = 0x40;
				cursorY = static_cast<float>(posY);
			}
		}
		else
		{
			// cursorMoveFrame kCursorMoveFrame->0�ƕω�����
			float rate = static_cast<float>(cursorMoveFrame) / static_cast<float>(kCursorMoveFrame);	// 1.0->0.0
			if (cursorIndex == i)
			{
				// ���񂾂�Â��Ȃ�
				r = 0xff * rate + 0x80 * (1.0f - rate);
				g = 0x40 * rate + 0x80 * (1.0f - rate);
				b = 0x40 * rate + 0x80 * (1.0f - rate);
			}
			else if (cursorNext == i)
			{
				// ���񂾂񖾂邭�Ȃ�
				r = 0xff * (1.0f - rate) + 0x80 * rate;
				g = 0x40 * (1.0f - rate) + 0x80 * rate;
				b = 0x40 * (1.0f - rate) + 0x80 * rate;
			}
			cursorY = (330 + 32 * cursorNext) * (1.0f - rate) + (330 + 32 * cursorIndex) * rate;
		}
		DrawStringToHandle(350, posY, kMenuItemMessage[i], GetColor(r, g, b), menuItemHandle);
	}
	{
		int cursorHeight = static_cast<int>(sinf(sinRate) * 12.0f);	// ���ۂɂ�Height/2
		DrawTriangle(335, static_cast<int>(cursorY) + 12,
			325, static_cast<int>(cursorY) + 12 - cursorHeight,
			325, static_cast<int>(cursorY) + 12 + cursorHeight, 0xff0000, true);
		DrawTriangle(335, static_cast<int>(cursorY) + 12,
			325, static_cast<int>(cursorY) + 12 - cursorHeight,
			325, static_cast<int>(cursorY) + 12 + cursorHeight, 0xffffff, false);
	}
}

void SceneTutorial::refreshScore()
{
	FILE* fp = NULL;
	errno_t error;
	hiscore = getHiScore();
	error = fopen_s(&fp, "test.txt", "r");
	if (fp != NULL)
	{
		fscanf_s(fp, "%d", &hiscore);
		fclose(fp);
	}
	if (fp == NULL || hiscore > frstPlaceTime)
	{
		error = fopen_s(&fp, "test.txt", "w");
		fprintf_s(fp, "%d",frstPlaceTime);
		fclose(fp);
	}
}

int SceneTutorial::getHiScore()
{
	FILE* fp = NULL;
	errno_t error;
	error = fopen_s(&fp, "test.txt", "r");
	if (fp == NULL) return 0;
	fscanf_s(fp, "%d", &hiscore);
	fclose(fp);
	return hiscore;
}

