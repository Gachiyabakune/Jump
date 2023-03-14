#pragma once

// �T�E���h�֘A����
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		SoundId_BgmMain,	// ����X�e�[�W��BGM
		SoundId_BgmEasy,	// ���񂽂�ȃX�e�[�W��BGM
		//SoundId_BgmClear,	// �N���A��̂�BGM
		//SoundId_Title,		//�^�C�g����ʂ�BGM

		// ���ʉ�
		SoundId_Jump,		// �W�����v����Ƃ�
		SoundId_Select,		// �I����ʂőI��ł���Ƃ�
		SoundId_Decision,	// �I����ʂŌ��肵���Ƃ�
		//SoundId_Clear,		//�N���A�����Ƃ��̉�

		SoundId_Num
	}SoundId;

	// ���[�h�A�A�����[�h
	void load();
	void unload();

	// BGM�̍Đ�
	void startBgm(SoundId id, int volume = 255);
	void stopBgm(SoundId id);

	// ���ʉ��̍Đ�
	void play(SoundId id);

	// ���ʐݒ�	0~255
	void setVolume(SoundId id, int volume);
}
