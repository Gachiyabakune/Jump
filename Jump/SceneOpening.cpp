#include "SceneOpening.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"

namespace
{
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

    //何秒押されていないか
    constexpr int kWaitTime = 1200;

	// 文字色
	const int kFontColor = GetColor(255, 255, 255);
    const int kColor = GetColor(0, 0, 0);
}

void SceneOpening::init()
{
    m_textBlinkFrame = 0;
    SetFontSize(20);

    m_BackHandle = LoadGraph("Data/sora.jpg");
}

void SceneOpening::end()
{
    DeleteGraph(m_BackHandle);
    SetFontSize(16);
}

SceneBase* SceneOpening::update()
{
    //kWaitTimeの間ボタンが押されなければ表示する
    m_displayCount++;
    // テキストの点滅
    m_textBlinkFrame++;
    if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
    {
        m_textBlinkFrame = 0;
    }

    int Pad;        //ジョイパッドの入力状態格納用変数
    //好きなボタン
    Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //入力状態をPadに格納
    for (int i = 0; i < 28; i++)
    {
        if (Pad & (1 << i))
        {
            Sound::play(Sound::SoundId_Decision);
            return (new SceneTitle);
        }
    }
    //if (!isFading())
    //{
    //    if (m_displayCount > kWaitTime)
    //    {
    //        // フェードアウト開始
    //        startFadeOut();
    //    }
    //}
    
    return this;
}

void SceneOpening::draw()
{
    if (m_displayCount > kWaitTime)
    {
        //if (isFading())
        //{
        //    bool isOut = isFadingOut();
        //    SceneBase::updateFade();
        //    // フェードアウト終了時にシーン切り替え
        //    if (!isFading() && isOut)
        //    {
        //        DrawGraph(0, 0, m_BackHandle, false);
        //    }
        //}
        DrawGraph(0, 0, m_BackHandle, false);
        
    }
    else
    {
        DrawBox(150, 50, 628, 380, kFontColor, true);
        DrawString(320, 190, "タイトル(仮)", kColor, false);
    }
   
    //テキスト点滅
    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 80,
            (Game::kScreenHight / 2) + 120,
            "Press the button", kFontColor, false);
    }
}
