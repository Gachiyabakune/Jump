#pragma once
#include "SceneBase.h"

class SceneOption : public SceneBase
{
public:
	SceneOption();
	virtual ~SceneOption() {}


	virtual void init()override;
	virtual void end()override {}

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
	//�t�F�[�h�֌W
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//�t�F�[�h�^�C�}�[
	int fadeValue = 255;				//���Z�`�̃u�����h�

	//���̃V�[���ɍs���邩
	bool nextScene;

	//�摜
	int backHandle;
	//�t�H���g
	int explanationHandle;
};
