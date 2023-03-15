#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() {}


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	// �J�[�\���ړ�
	int cursorIndex;
	int cursorNext;
	int cursorMoveFrame;
	//�t�H���g
	int menuItemHandle;
	//�C���^�[�o��
	int m_interval;
	int frameCount;
	//�T�C��
	float sinRate;

	//�󔠂�\�������邽��
	int chip[40];
};