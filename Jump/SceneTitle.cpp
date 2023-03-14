#include "SceneTitle.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "SceneTutorial.h"
#include "SceneOpening.h"
#include "SceneOption.h"
#include "Sound.h"
#include "Pad.h"
#include "game.h"

//typedef enum 
//{
//	eMenu_Game_Easy,		//チュートリアル
//	eMenu_Game_Hard,         //ゲーム
//	eMenu_Config,       //設定
//	eMenu_End,			//終了
//	eMenu_Num,        //本項目の数
//} eMenu;

//static int NowSelect = eMenu_Game_Easy;    //現在の選択状態(初期はゲーム選択中)

namespace
{
	// タイトルとサンプルの説明
	const char* const kTitkeMessage = "いい感じのUIサンプル";
	const char* const kMenuItemMessage[] =
	{
		"かんたん",
		"むずかしい",
		"そうさ",
		"おわる",
	};
	// 数字フォントのサイズ
	constexpr int kFontWidth = 16;
	constexpr int kFontHeight = 32;
	// カーソル
	constexpr int kCursorMoveFrame = 30;
	// ウインドウ
	constexpr int kWindowAppearFrame = 30;
	// 文字色
	const int kFontColor = GetColor(125, 125, 125);
	const int kFontSelectColor = GetColor(255, 255, 255);
}

void SceneTitle::init()
{
	m_interval = 0;
	menuItemHandle = CreateFontToHandle("メイリオ", 24, 8, DX_FONTTYPE_ANTIALIASING_8X8);
}

SceneBase* SceneTitle::update()
{	
	//if(Pad::isTrigger(PAD_INPUT_2))
	//{
	//	switch (NowSelect)
	//	{
	//	case eMenu_Game_Easy:
	//		 Sound::play(Sound::SoundId_Decision);
	//		return (new SceneTutorial);
	//		break;
	//	case eMenu_Game_Hard:
	//		Sound::play(Sound::SoundId_Decision);
	//		return (new SceneMain);
	//		break;
	//	case eMenu_End:
	//		return (new SceneOpening);
	//		break;
	//	case eMenu_Config:
	//		//return (new SceneOption);
	//		break;
	//	default:
	//		break;
	//	}
	//	
	//}
	////上
	//if (Pad::isTrigger(PAD_INPUT_UP))
	//{
	//	NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	//	Sound::play(Sound::SoundId_Select);
	//}
	////下
	//if (Pad::isTrigger(PAD_INPUT_DOWN))
	//{
	//	NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
	//	Sound::play(Sound::SoundId_Select);
	//}
	
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
		m_interval = 60;
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
		switch (cursorIndex)
		{
		case 0:
			return (new SceneTutorial);
			break;
		case 1:
			return (new SceneMain);
			break;
		case 2:
			//return (new Scene)
			break;
		case 3:
			return (new SceneOpening);
			break;
		}
	}
	return this;
}

void SceneTitle::draw()
{
	//int y = 0;
	//DrawString(200, 150, "", GetColor(255, 255, 255));
	//DrawString(200, 170, "上下キーで選択し、2ボタンを押して下さい。", GetColor(255, 255, 255));
	//if (select1)
	//{
	//	DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 - 30,
	//		"かんたん", kFontSelectColor);
	//}
	//else
	//{
	//	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 - 30,
	//		"かんたん", kFontColor);
	//}
	//if (select2)
	//{
	//	DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2,
	//		"むずかしい", kFontSelectColor);
	//}
	//else
	//{
	//	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2,
	//		"むずかしい", kFontColor);
	//}
	//if (select3)
	//{
	//	DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 + 30,
	//		"そうさ", kFontSelectColor);
	//}
	//else
	//{
	//	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 30,
	//		"そうさ", kFontColor);
	//}
	//if (select4)
	//{
	//	DrawString(Game::kScreenWidth / 2 - 25, Game::kScreenHight / 2 + 60,
	//		"おわる", kFontSelectColor);
	//}
	//else
	//{
	//	DrawString(Game::kScreenWidth / 2 - 40, Game::kScreenHight / 2 + 60,
	//		"おわる", kFontColor);
	//}

	////選んだ項目によって座標や色などを変えているのでコードが長くなる
	//switch (NowSelect)
	//{//現在の選択状態に従って処理を分岐
	//case eMenu_Game_Easy://ゲーム選択中なら
	//	y = 258;    //ゲームの座標を格納
	//	select1 = true;
	//	select2 = false;
	//	select3 = false;
	//	select4 = false;
	//	break;
	//case eMenu_Game_Hard:
	//	y = 288;
	//	select2 = true;
	//	select1 = false;
	//	select3 = false;
	//	select4 = false;
	//	break;
	//case eMenu_Config:
	//	y = 318;
	//	select3 = true;
	//	select1 = false;
	//	select2 = false;
	//	select4 = false;
	//	break;
	//case eMenu_End:
	//	y = 348;
	//	select4 = true;
	//	select2 = false;
	//	select3 = false;
	//	select1 = false;
	//	break;
	//}

	//DrawString(Game::kScreenWidth / 2 - 70, y, "⇒", GetColor(255, 0, 255));

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
				cursorY = posY;
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
		DrawStringToHandle(256, posY, kMenuItemMessage[i], GetColor(r, g, b), menuItemHandle);
	}
	{
		int cursorHeight = sinf(sinRate) * 12.0f;	// 実際にはHeight/2
		DrawTriangle(248, cursorY + 12,
			238, cursorY + 12 - cursorHeight,
			238, cursorY + 12 + cursorHeight, 0xff0000, true);
		DrawTriangle(248, cursorY + 12,
			238, cursorY + 12 - cursorHeight,
			238, cursorY + 12 + cursorHeight, 0xffffff, false);
	}
}