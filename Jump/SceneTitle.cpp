#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTutorial.h"
#include "SceneOpening.h"
#include "SceneOption.h"
#include "Sound.h"
#include "Pad.h"
#include "game.h"

namespace
{
	// タイトルとサンプルの説明
	const char* const kMenuItemMessage[] =
	{
		"EASY",
		"HARD",
		"OPERATION",
		"END",
	};
	// カーソル
	constexpr int kCursorMoveFrame = 30;
}

SceneTitle::SceneTitle() :
	cursorIndex(0),
	cursorNext(0),
	cursorMoveFrame(0),
	menuItemHandle(0),
	m_interval(0),
	frameCount(0)
{
	sinRate = 0.0f;
	for (int i = 0; i < 40; i++)
	{
		chip[i] = 0;
	}
}

void SceneTitle::init()
{
	//マップ
	LoadDivGraph("data/mapchip.png",
		40,
		10, 4,
		32, 32,
		chip);					

	//BGMを再生
	Sound::startBgm(Sound::SoundId_BgmTitle, 0);

	m_interval = 0;
	menuItemHandle = CreateFontToHandle("メイリオ", 24, 8, DX_FONTTYPE_ANTIALIASING_8X8);
}

SceneBase* SceneTitle::update()
{	
	frameCount++;
	sinRate += 0.1f;

	//下キー
	if (Pad::isTrigger(PAD_INPUT_DOWN) && m_interval == 0)
	{
		cursorNext++;
		if (cursorNext > _countof(kMenuItemMessage) - 1)
		{
			cursorNext = 0;
		}
		cursorMoveFrame = kCursorMoveFrame;
		m_interval = 30;
		Sound::play(Sound::SoundId_Select);
	}
	//上キー
	else if (Pad::isTrigger(PAD_INPUT_UP) && m_interval == 0)
	{
		cursorNext--;
		if (cursorNext == -1)
		{
			cursorNext = _countof(kMenuItemMessage) - 1;
		}
		cursorMoveFrame = kCursorMoveFrame;
		m_interval = 30;
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
	//インターバル
	if (m_interval != 0)
	{
		m_interval--;
	}

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		Sound::stopBgm(Sound::SoundId_BgmTitle);
		switch (cursorIndex)
		{
		case 0:
			Sound::play(Sound::SoundId_Decision);
			return (new SceneTutorial);
			break;
		case 1:
			Sound::play(Sound::SoundId_Decision);
			return (new SceneMain);
			break;
		case 2:
			Sound::play(Sound::SoundId_Decision);
			return (new SceneOption);
			break;
		case 3:
			Sound::play(Sound::SoundId_Decision);
			return (new SceneOpening);
			break;
		}
	}

	int volume = 0;
	volume += frameCount * 4;
	if (volume > 150)	volume = 150;
	Sound::setVolume(Sound::SoundId_BgmTitle, volume);

	return this;
}

void SceneTitle::draw()
{
	DrawGraph(270, 200, chip[21], TRUE);
	SetFontSize(32);
	DrawString(300, 200, "をみつけだせ", GetColor(255, 255, 255));
	SetFontSize(16);

	DrawString(330, 280, "Bボタンで選択", GetColor(255, 255, 255));

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
			// cursorMoveFrame kCursorMoveFrame->0と変化する
			float rate = static_cast<float>(cursorMoveFrame) / static_cast<float>(kCursorMoveFrame);	// 1.0->0.0
			if (cursorIndex == i)
			{
				// だんだん暗くなる
				r = 0xff * rate + 0x80 * (1.0f - rate);
				g = 0x40 * rate + 0x80 * (1.0f - rate);
				b = 0x40 * rate + 0x80 * (1.0f - rate);
			}
			else if (cursorNext == i)
			{
				// だんだん明るくなる
				r = 0xff * (1.0f - rate) + 0x80 * rate;
				g = 0x40 * (1.0f - rate) + 0x80 * rate;
				b = 0x40 * (1.0f - rate) + 0x80 * rate;
			}
			cursorY = (330 + 32 * cursorNext) * (1.0f - rate) + (330 + 32 * cursorIndex) * rate;
		}
		DrawStringToHandle(350, posY, kMenuItemMessage[i], GetColor(r, g, b), menuItemHandle);
	}
	{
		int cursorHeight = static_cast<int>(sinf(sinRate) * 12.0f);	// 実際にはHeight/2
		DrawTriangle(335, static_cast<int>(cursorY) + 12,
			325, static_cast<int>(cursorY) + 12 - cursorHeight,
			325, static_cast<int>(cursorY) + 12 + cursorHeight, 0xff0000, true);
		DrawTriangle(335, static_cast<int>(cursorY) + 12,
			325, static_cast<int>(cursorY) + 12 - cursorHeight,
			325, static_cast<int>(cursorY) + 12 + cursorHeight, 0xffffff, false);
	}
}