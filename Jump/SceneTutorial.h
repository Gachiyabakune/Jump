#pragma once
#include "SceneBase.h"
#include "Player2.h"
#include "EasyMap.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial()
	{
		m_seq = Seq::SeqWait;
		m_timeTaken = 0;
		m_timer = 0;
		temp = 10000;
	}
	virtual ~SceneTutorial();


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	virtual void updateWait();	//�t�F�[�h��
	virtual void updateGame();	//�Q�[��
	virtual void updateClear();	//�N���A���update����

	virtual void drawClear();	//�N���A���draw����

	void refreshScore();
	int getHiScore();
private:
	Player2* player = new Player2;
	EasyMap* map = new EasyMap;

	enum class Seq
	{
		SeqWait,			//�t�F�[�h��
		SeqUpdata,			//�ʏ��updata
		SeqClearUpdata,		//�N���A���updata
	};
	// ���݂̃Q�[���V�[�P���X
	Seq m_seq;

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
};