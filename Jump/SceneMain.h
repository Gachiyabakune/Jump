#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Map.h"
#include "game.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end() {}

	virtual SceneBase* update();
	virtual void draw();

private:
	//�t�F�[�h�C���̎���Update�֐�
	void FadeInUpdate();
	//�ʏ��Ԃ�Update�֐�
	void NormalUpdate();
	//�N���A���Update�֐�
	void ClearUpdate();
	//�t�F�[�h�A�E�g�̎���Update�֐�
	void FadeOutUpdate();

	virtual void drawClear();	//�N���A���draw����

	void refreshScore();
	int getHiScore();
private:
	Player* player = new Player;
	Map* map = new Map;
	enum class Seq
	{
		SeqFadeIn,			//�t�F�[�h��
		SeqUpdata,			//�ʏ��updata
		SeqClearUpdata,		//�N���A���updata
		SeqFadeOut,		//�t�F�[�h�A�E�g
	};
	// ���݂̃Q�[���V�[�P���X
	Seq m_seq;

	//�t�F�[�h�֌W
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//�t�F�[�h�^�C�}�[
	int fadeValue = 255;				//���Z�`�̃u�����h�

	//������������
	int m_timeTaken;
	int temp;
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
};