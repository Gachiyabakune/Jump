#include "SceneOpening.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"

namespace
{
	// 文字列点滅
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

    //何秒押されていないか
    constexpr int kWaitTime = 120;

	// 文字色
	const int kFontColor = GetColor(255, 255, 255);
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

    //AかBボタン
    if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
    {
        return (new SceneTitle);
    }
    return this;
}

void SceneOpening::draw()
{
    if (m_displayCount > kWaitTime)
    {
        DrawGraph(0, 0, m_BackHandle, false);
    }

    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 60,
            (Game::kScreenHight / 2) - 10,
            "press A or B", kFontColor, false);
    }
}
