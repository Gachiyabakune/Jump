#include "SceneOpening.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"
#include <string>

namespace
{
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

    //何秒押されていないか
    constexpr int kWaitTime = 120;

	// 文字色
	const int kFontColor = GetColor(255, 255, 255);
    const int kColor = GetColor(0, 0, 0);
}

SceneOpening::SceneOpening() :
    m_textBlinkFrame(0),
    m_titleHandle(-1),
    backHandle(-1),
    m_fontX(0),
    m_fontY(0),
    chageScene(false)

{
    sinRate = 0.0f;
    m_seq = Seq::SeqFadeIn;
}

void SceneOpening::init()
{
    m_textBlinkFrame = 0;
    SetFontSize(20);

    m_titleHandle = LoadGraph("Title/title.png");
    backHandle = LoadGraph("data/sora.png");

    m_fontX = 200;
    m_fontY = 200;

    sinRate = 0.0f;

    chageScene = false;
}

void SceneOpening::end()
{
    DeleteGraph(m_titleHandle);
    SetFontSize(16);
}

SceneBase* SceneOpening::update()
{
    switch (m_seq)
    {
    case Seq::SeqFadeIn:
        FadeInUpdate();
        break;
    case Seq::SeqUpdata:
        NormalUpdate();
        break;
    case Seq::SeqFadeOut:
        FadeOutUpdate();
        break;
    }
    if (chageScene)
    {
        return (new SceneTitle);
    }
   
    return (this);
} 

void SceneOpening::draw()
{
    DrawGraph(0, 0, backHandle, false);
    int moveY = static_cast<int>(sinf(sinRate * 2) * 4);
    DrawGraph(m_fontX, m_fontY + moveY, m_titleHandle, true);

    //テキスト点滅
    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 75,
            (Game::kScreenHight / 2) + 120,
            "Press the key", kColor, false);
    }

    //今から書く画像と、すでに描画されているスクリーンとの
    //ブレンドの仕方を指定している。
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeValue);
    //画面全体を真っ黒に塗りつぶす
    DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHight, 0x000000, true);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneOpening::FadeInUpdate()
{
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

void SceneOpening::NormalUpdate()
{
    //タイトルの上下移動
    sinRate += 0.05f;
    //kWaitTimeの間ボタンが押されなければ表示する
   // m_displayCount++;
    // テキストの点滅
    m_textBlinkFrame++;
    if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
    {
        m_textBlinkFrame = 0;
    }
    int Pad;        //ジョイパッドの入力状態格納用変数
   //すべてのボタンに反応させるため
    Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
    for (int i = 0; i < 28; i++)        //28個のボタン
    {
        if (Pad & (1 << i))
        {
            Sound::play(Sound::SoundId_Decision);
            m_seq = Seq::SeqFadeOut;
        }
    }
}

void SceneOpening::FadeOutUpdate()
{
    fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
    if (fadeTimer++ == fade_interval)
    {
        chageScene = true;
    }
}
