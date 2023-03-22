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

    explanationHandle = CreateFontToHandle("���C���I", 20, 8, DX_FONTTYPE_ANTIALIASING_8X8);
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
        "A�{�^���ŃW�����v", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) - 50,
        "�������ŃW�����v�͂��ς���", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) - 20,
        "�����L�[�Ŕ�ԕ������ς���", GetColor(0, 0, 0), explanationHandle);
    DrawStringToHandle((Game::kScreenWidth / 2) - 120, (Game::kScreenHight / 2) +10,
        "Y�{�^���Ń^�C�g����", GetColor(0, 0, 0), explanationHandle);
}

void SceneOption::FadeInUpdate()
{
    //�^�������珙�X�ɕ\������ꍇ�ꍇ
    fadeValue = 255 * (static_cast<float>(fadeTimer) / static_cast<float>(fade_interval));
    //�O���f�[�V�������g���ď��X�ɕ\������ꍇ
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