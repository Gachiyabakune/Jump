#pragma once
#include "SceneBase.h"
class SceneOpening : public SceneBase
{
public:
	SceneOpening() 
	{
		m_textBlinkFrame = 0;
		//m_displayCount = 0;
		nextScene = false;
		m_titleHandle = -1;
		m_clip = -1;
		m_seq = Seq::SeqFadeIn;
	}
	virtual ~SceneOpening() {}


	virtual void init() override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdate();
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate();
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate();

	enum class Seq
	{
		SeqFadeIn,		//�t�F�[�h�C��
		SeqUpdata,		//�ʏ��updata
		SeqFadeOut,		//�t�F�[�h�A�E�g
	};
	// ���݂̃Q�[���V�[�P���X
	Seq m_seq;

private:
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//�t�F�[�h�^�C�}�[
	int fadeValue = 255;				//���Z�`�̃u�����h�
	//�@
	//int m_displayCount;
	// �^�C�g��
	int m_titleHandle;
	//�f���f��
	int m_clip;
	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;
	//�t�H���g�̍��W
	int m_fontX;
	int m_fontY;
	//�t�H���g���㉺�ړ������邽�߂�sin
	float sinRate;

	bool nextScene;
};

