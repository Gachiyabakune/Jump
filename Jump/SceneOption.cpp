#include "SceneTitle.h"
#include "SceneOption.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "game.h"
#include "Pad.h"

SceneOption::SceneOption() :
    backHandle(-1),
    explanationHandle(-1),
	nextScene(false)
{
	m_seq = Seq::SeqFadeIn;
}

void SceneOption::init()
{
	nextScene = false;
    backHandle = LoadGraph("data/sora.png");

    explanationHandle = CreateFontToHandle("メイリオ", 20, 8, DX_FONTTYPE_ANTIALIASING_8X8);
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
    DrawGraph(0, 0, backHandle, false);

    DrawStringToHandle((Game::kScreenWidth/2)-120, (Game::kScreenHight/2)-80, 
        "Aボタンでジャンプ", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) - 50,
        "長押しでジャンプ力が変わるよ", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) - 20,
        "方向キーで飛ぶ方向が変わるよ", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) +10,
        "Yボタンでタイトルへ", GetColor(0, 0, 0), explanationHandle);
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