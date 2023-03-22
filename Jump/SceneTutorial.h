#pragma once
#include "SceneBase.h"
#include "Player2.h"
#include "EasyMap.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial();
	virtual ~SceneTutorial();


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdate();
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate();
	//�N���A���Update�֐�
	void ClearUpdate();
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate();
	//�I�v�V��������update
	void OptionUpdate();

	void drawClear();	//�N���A���draw����
	void drawOption();

	void refreshScore();
	int getHiScore();
private:
	Player2* player = new Player2;
	EasyMap* map = new EasyMap;

	enum class Seq
	{
		SeqFadeIn,			//�t�F�[�h��
		SeqUpdata,			//�ʏ��updata
		SeqClearUpdata,		//�N���A���updata
		SeqFadeOut,		//�t�F�[�h�A�E�g
		SeqOption,
	};
	// ���݂̃Q�[���V�[�P���X
	Seq m_seq;

	//�t�F�[�h�֌W
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//�t�F�[�h�^�C�}�[
	int fadeValue = 255;				//���Z�`�̃u�����h�

	//������������
	int m_timeTaken;
	int frstPlaceTime;
	int m_timer;
	//�t�H���g�֌W
	int textHeight;
	int textWidth;
	int textDispWidth;
	int fontHandle;

	// ������O���t�B�b�N�𐶐�
	int handle;

	//�X�R�A
	int hiscore;

	//�V�[���؂�ւ�
	bool changeScene;
	
private:
	//�I�v�V����
	bool option;
	//�t�H���g
	int menuItemHandle;
	// �J�[�\���ړ�
	int cursorIndex;
	int cursorNext;
	int cursorMoveFrame;
	//�C���^�[�o��
	int m_interval;
	//�T�C��
	float sinRate;
};