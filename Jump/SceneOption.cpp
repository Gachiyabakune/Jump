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
	DrawString(4, 0, "A�{�^���ŃW�����v", GetColor(255, 255, 255));
	DrawString(4, 20, "�������ŃW�����v�͂��ς���", GetColor(255, 255, 255));
	DrawString(4, 40, "�����L�[�Ŕ�ԕ������ς���", GetColor(255, 255, 255));
	DrawString(4, 60, "Y�{�^���Ń^�C�g����", GetColor(255, 255, 255));

    //DrawGraph(0, 0, handle, false);
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