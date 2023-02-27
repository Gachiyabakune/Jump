#include "SceneOpening.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"

namespace
{
	// ������_��
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

    //���b������Ă��Ȃ���
    constexpr int kWaitTime = 1200;

	// �����F
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
    //kWaitTime�̊ԃ{�^����������Ȃ���Ε\������
    m_displayCount++;
    // �e�L�X�g�̓_��
    m_textBlinkFrame++;
    if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
    {
        m_textBlinkFrame = 0;
    }

    int Pad;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�
    //�D���ȃ{�^��
    Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
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
    //        // �t�F�[�h�A�E�g�J�n
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
        //    // �t�F�[�h�A�E�g�I�����ɃV�[���؂�ւ�
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
        DrawString(320, 190, "�^�C�g��(��)", kColor, false);
    }
   
    //�e�L�X�g�_��
    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 80,
            (Game::kScreenHight / 2) + 120,
            "Press the button", kFontColor, false);
    }
}
