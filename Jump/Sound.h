#pragma once

// �T�E���h�֘A����
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		//SoundId_BgmMain,	// �I����ʂ�BGM
		//SoundId_BgmClear,	// �N���A���BGM

		// ���ʉ�
		SoundId_Jump,		// �W�����v����Ƃ�
		SoundId_fall,		// ���n����Ƃ�
		SoundId_Bound,	// ���˂���Ƃ�
		SoundId_Select,		// �I����ʂőI��ł���Ƃ�
		SoundId_Decision,	// �I����ʂŌ��肵���Ƃ�

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
