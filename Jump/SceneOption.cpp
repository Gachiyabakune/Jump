#include "SceneTitle.h"
#include "SceneOption.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Pad.h"

SceneOption::SceneOption() :
    handle(-1),
	nextScene(false)
{
	m_seq = Seq::SeqFadeIn;
}

void SceneOption::init()
{
	nextScene = false;
    //handle = LoadGraph("data/pad.png");
}

SceneBase* SceneOption::update()
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
    if (nextScene)
    {
        return (new SceneTitle);
    }
	return this;
}

void SceneOption::draw()
{
	DrawString(4, 0, "Aボタンでジャンプ", GetColor(255, 255, 255));
	DrawString(4, 20, "長押しでジャンプ力が変わるよ", GetColor(255, 255, 255));
	DrawString(4, 40, "方向キーで飛ぶ方向が変わるよ", GetColor(255, 255, 255));
	DrawString(4, 60, "Yボタンでタイトルへ", GetColor(255, 255, 255));

    //DrawGraph(0, 0, handle, false);
}

void SceneOption::FadeInUpdate()
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

void SceneOption::NormalUpdate()
{
    if (Pad::isTrigger(PAD_INPUT_4))
    {
        m_seq = Seq::SeqFadeOut;
    }
}

void SceneOption::FadeOutUpdate()
{
    fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
    if (fadeTimer++ == fade_interval)
    {
        nextScene = true;
    }
}