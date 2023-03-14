#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "DxLib.h"
#include "Sound.h"
#include "Pad.h"
#include "game.h"
#include <cassert>

namespace
{
	//テキスト
	const char* const kTitkeMessage = "GAME CLEAR";
	constexpr int kStandbyTime = 60;
	constexpr int kStandbyTime2 = 120;
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

	//現在のシーケンス
	m_seq = Seq::SeqUpdata;

	m_timeTaken = 0;	//経過時間

	hiscore = 1000;			//ハイスコア

	//BGMを再生
	Sound::startBgm(Sound::SoundId_BgmEasy,0);

	//フォント
	fontHandle = CreateFontToHandle("Playbill", 100, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//文字列をグラフィックに
	textHeight = 100;
	textWidth = GetDrawStringWidthToHandle(kTitkeMessage, strlen(kTitkeMessage), fontHandle);
	// 文字列グラフィックを生成
	handle = MakeScreen(textWidth, textHeight, true);

	SetDrawScreen(handle);
	DrawStringToHandle(0, 0, kTitkeMessage, GetColor(255, 255, 0), fontHandle);
	//ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
}

SceneBase* SceneTutorial::update()
{
	switch (m_seq)
	{
	case Seq::SeqWait:
		updateWait();
		break;
	case Seq::SeqUpdata:
		updateGame();
		break;
	case Seq::SeqClearUpdata:
		updateClear();
		break;
	}
	//デバック用
#ifdef _DEBUG
	if (Pad::isTrigger(PAD_INPUT_5))
	{
		return(new SceneTitle);
	}
#endif 
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
}

void SceneTutorial::updateWait()
{
	SceneBase::updateFade();
	if (isFading())	return;	// フェードイン、アウト中は動かない
	m_seq = Seq::SeqUpdata;
}

void SceneTutorial::updateGame()
{
	player->updata();
	map->updata();
	//クリアすると
	if (player->gameClear())
	{
		m_seq = Seq::SeqClearUpdata;
	}
	m_timeTaken++;

	int volume = 0;
	volume += m_timeTaken * 2;
	if (volume > 100)	volume = 100;
	Sound::setVolume(Sound::SoundId_BgmEasy, volume);
}

void SceneTutorial::updateClear()
{
	map->clearUpdata();
	refreshScore();
	m_timer++;	//タイマー
	temp = m_timeTaken / 60;
	if (m_timer > kStandbyTime)	//10秒間スクロールした後に
	{
		textDispWidth++;
	}

	//クリアするとだんだんBGMが小さくなる
	int volume = 100;
	volume -= m_timer * 2;
	if (volume < 0)	volume = 0;
	Sound::setVolume(Sound::SoundId_BgmEasy, volume);

	//volumeが0になるとBGM停止
	if (volume == 0)
	{
		Sound::stopBgm(Sound::SoundId_BgmEasy);
	}
}

void SceneTutorial::drawClear()
{
	if (m_timer > kStandbyTime)	//10秒間スクロールした後に
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
		DrawFormatString(250, 400, GetColor(255, 255, 255), "タイム%d秒", temp);	//Y座標

		if (temp < hiscore)
		{
			DrawFormatString(250, 480, GetColor(255, 255, 255), "ランキング1位になりました:%d秒", temp);
		}
		else if (temp > hiscore)
		{
			DrawFormatString(250, 480, GetColor(255, 255, 255), "ランキング1位のタイム:%d秒", hiscore);
		}
		else
		{
			DrawFormatString(250, 480, GetColor(255, 255, 255), "ランキング1位になりました:%d秒", temp);
		}
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
	if (fp == NULL || hiscore > temp)
	{
		error = fopen_s(&fp, "test.txt", "w");
		fprintf_s(fp, "%d",temp);
		fclose(fp);
	}
	else if (fp == NULL || hiscore < temp)
	{
		DrawFormatString(250, 450, GetColor(255, 255, 255), "1位は%d秒", hiscore);
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

