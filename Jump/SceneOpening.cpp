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

void SceneOpening::init()
{
    m_textBlinkFrame = 0;
    SetFontSize(20);

    m_titleHandle = LoadGraph("Title/title.png");

    m_fontX = 200;
    m_fontY = 200;

    sinRate = 0.0f;
}

void SceneOpening::end()
{
    DeleteGraph(m_titleHandle);
    SetFontSize(16);
}

SceneBase* SceneOpening::update()
{
    //タイトルの上下移動
    sinRate += 0.05f;
    //kWaitTimeの間ボタンが押されなければ表示する
    m_displayCount++;
    // テキストの点滅
    m_textBlinkFrame++;
    if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
    {
        m_textBlinkFrame = 0;
    }
    if (isFading())
    {
        bool isOut = isFadingOut();
        SceneBase::updateFade();
        // フェードアウト終了時にシーン切り替え
        if (!isFading() && isOut)
        {
            return (new SceneTitle);
        }
    }
    int Pad;        //ジョイパッドの入力状態格納用変数
    if (!isFading())
    {
        //すべてのボタンに反応させるため
        Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
        for (int i = 0; i < 28; i++)        //28個のボタン
        {
            if (Pad & (1 << i))
            {
                Sound::play(Sound::SoundId_Decision);
                // フェードアウト開始
                startFadeOut();
            }
        }
    }
    return this;
} 

void SceneOpening::draw()
{
    //if (m_displayCount > kWaitTime)
    //{
    //    //DrawGraph(0, 0, m_clip, false);
   
    //    //デモムービーを再生
    //    PlayMovie("Clip/Demo.mp4",1, DX_MOVIEPLAYTYPE_NORMAL);
    //}
    //else
    {
        int moveY = sinf(sinRate * 2) * 4;
        DrawGraph(m_fontX, m_fontY + moveY, m_titleHandle, false);
    }
   
    //DrawFormatString(300, 550, GetColor(255, 255, 255), "%d秒後デモムービーが流れます",);

    //テキスト点滅
    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 75,
            (Game::kScreenHight / 2) + 120,
            "Press the key", kFontColor, false);
    }
}
