#pragma once

namespace Game
{
#ifdef _DEBUG
	//�E�B���h�E���[�h�ݒ�
	constexpr bool kWindowmode = true;
#else
	//�E�B���h�E���[�h�ݒ�
	constexpr bool kWindowmode = false;
#endif
	const char* const kTitleText = "�f�`�l�d";
	//�E�B���h�E�T�C�Y
	constexpr int kScreenWidth = 768;	//768 or 1024
	constexpr int kScreenHight = 576;
	//�J���[���[�h
	constexpr int kColorDepth = 32;   //32 or 16
};