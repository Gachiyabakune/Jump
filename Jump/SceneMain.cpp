#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneOption.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"


namespace
{
	//テキスト
	const char* const kTitkeMessage = "GAME CLEAR";
	constexpr int kStandbyTime = 60;	//クリア後からフォントが出てくるまでの時間
	constexpr int kStandbyTime2 = 180;	//ランキングなどが出てくる時間
}

SceneMain::SceneMain() :
	m_timeTaken(0),
	m_timer(0),
	textHeight(0),
	textWidth(0),
	textDispWidth(0),
	fontHandle(0),
	handle(0),
	hiscore(0),
	changeScene(false)
{
	m_seq = Seq::SeqFadeIn;
	temp = 10000;
}

SceneMain::~SceneMain()
{
	delete(player);
	delete(map);
}

void SceneMain::init()
{
	player->setStage(map);
	player->init();
	map->setPlayer(player);
	map->init();

	//現在のシーケンス
	m_seq = Seq::SeqFadeIn;

	m_timeTaken = 0;	//経過時間

	hiscore = 1000;			//ハイスコア

	changeScene = false;	//シーン切り替え

	//BGMを再生
	Sound::startBgm(Sound::SoundId_BgmMain, 100);

	//フォント
	fontHandle = CreateFontToHandle("Playbill", 100, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	//文字列をグラフィックに
	textHeight = 100;
	textWidth = GetDrawStringWidthToHandle(kTitkeMessage,static_cast<int>(strlen(kTitkeMessage)), fontHandle);
	// 文字列グラフィックを生成
	handle = MakeScreen(textWidth, textHeight, true);

	SetDrawScreen(handle);
	DrawStringToHandle(0, 0, kTitkeMessage, GetColor(255, 255, 0), fontHandle);
	//ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
}

SceneBase* SceneMain::update()
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
	}

	if (changeScene)
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneMain::draw()
{
	map->draw();
	player->draw();

	if (player->gameClear())
	{
		drawClear();
	}

	//今から書く画像と、すでに描画されているスクリーンとの
   //ブレンドの仕方を指定している。
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
	//画面全体を真っ黒に塗りつぶす
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHight, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneMain::FadeInUpdate()
{
	player->updata();
	map->updata();
	//真っ黒から徐々に表示する場合場合
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
	//グラデーションを使って徐々に表示する場合
	/*fadeTimer_;*/
	if (fadeTimer-- == 0)
	{
		m_seq = Seq::SeqUpdata;
		fadeValue = 0;
	}
}

void SceneMain::NormalUpdate()
{
	player->updata();
	map->updata();

	//クリア判定
	if (player->gameClear())
	{
		m_seq = Seq::SeqClearUpdata;
	}
	m_timeTaken++;

	int volume = 0;
	volume += m_timeTaken * 2;
	if (volume > 100)	volume = 100;
	Sound::setVolume(Sound::SoundId_BgmMain, volume);
}

void SceneMain::ClearUpdate()
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
	Sound::setVolume(Sound::SoundId_BgmMain, volume);

	//volumeが0になるとBGM停止
	if (volume == 0)
	{
		Sound::stopBgm(Sound::SoundId_BgmMain);
	}
	//クリア後Yボタンを押すとタイトルへ
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		m_seq = Seq::SeqFadeOut;
	}
}

void SceneMain::FadeOutUpdate()
{
	fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
	if (fadeTimer++ == fade_interval)
	{
		changeScene = true;
	}
}

void SceneMain::drawClear()
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
			DrawFormatString(250, 430, GetColor(255, 255, 255), "ランキング1位になりました:%d秒", temp);
		}
		else if (temp > hiscore)
		{
			DrawFormatString(250, 430, GetColor(255, 255, 255), "ランキング1位のタイム:%d秒", hiscore);
		}
		else
		{
			DrawFormatString(250, 430, GetColor(255, 255, 255), "ランキング1位になりました:%d秒", temp);
		}

		DrawString(250, 460, "Yボタンでタイトルへ", GetColor(255, 255, 255));
	}
}

void SceneMain::refreshScore()
{
	FILE* fp = NULL;
	errno_t error;
	hiscore = getHiScore();
	error = fopen_s(&fp, "HardMap.txt", "r");
	if (fp != NULL)
	{
		fscanf_s(fp, "%d", &hiscore);
		fclose(fp);
	}
	if (fp == NULL || hiscore > temp)
	{
		error = fopen_s(&fp, "HardMap.txt", "w");
		fprintf_s(fp, "%d", temp);
		fclose(fp);
	}
}

int SceneMain::getHiScore()
{
	FILE* fp = NULL;
	errno_t error;
	error = fopen_s(&fp, "HardMap.txt", "r");
	if (fp == NULL) return 0;
	fscanf_s(fp, "%d", &hiscore);
	fclose(fp);
	return hiscore;
}
