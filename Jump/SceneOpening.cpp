#include "SceneOpening.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"
#include <string>

namespace
{
	// ������_��
	constexpr int kTextDispFrame = 45;
	constexpr int kTextHideFrame = 15;

    //���b������Ă��Ȃ���
    constexpr int kWaitTime = 120;

	// �����F
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
    //�^�C�g���̏㉺�ړ�
    sinRate += 0.05f;
    //kWaitTime�̊ԃ{�^����������Ȃ���Ε\������
    m_displayCount++;
    // �e�L�X�g�̓_��
    m_textBlinkFrame++;
    if (m_textBlinkFrame >= kTextDispFrame + kTextHideFrame)
    {
        m_textBlinkFrame = 0;
    }
    if (isFading())
    {
        bool isOut = isFadingOut();
        SceneBase::updateFade();
        // �t�F�[�h�A�E�g�I�����ɃV�[���؂�ւ�
        if (!isFading() && isOut)
        {
            return (new SceneTitle);
        }
    }
    int Pad;        //�W���C�p�b�h�̓��͏�Ԋi�[�p�ϐ�
    if (!isFading())
    {
        //���ׂẴ{�^���ɔ��������邽��
        Pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
        for (int i = 0; i < 28; i++)        //28�̃{�^��
        {
            if (Pad & (1 << i))
            {
                Sound::play(Sound::SoundId_Decision);
                // �t�F�[�h�A�E�g�J�n
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
   
    //    //�f�����[�r�[���Đ�
    //    PlayMovie("Clip/Demo.mp4",1, DX_MOVIEPLAYTYPE_NORMAL);
    //}
    //else
    {
        int moveY = sinf(sinRate * 2) * 4;
        DrawGraph(m_fontX, m_fontY + moveY, m_titleHandle, false);
    }
   
    //DrawFormatString(300, 550, GetColor(255, 255, 255), "%d�b��f�����[�r�[������܂�",);

    //�e�L�X�g�_��
    if (m_textBlinkFrame < kTextDispFrame)
    {
        DrawString((Game::kScreenWidth / 2) - 75,
            (Game::kScreenHight / 2) + 120,
            "Press the key", kFontColor, false);
    }
}
