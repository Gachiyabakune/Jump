#pragma once
#include "SceneBase.h"
class SceneOpening : public SceneBase
{
public:
	SceneOpening() 
	{
		m_BackHandle = -1;
		m_textBlinkFrame = 0;
		m_displayCount = 0;
	}
	virtual ~SceneOpening() {}


	virtual void init() override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//�@
	int m_displayCount;
	// �^�C�g���w�i
	int m_BackHandle;
	// �e�L�X�g�_�ŗp�t���[���J�E���g
	int m_textBlinkFrame;
};

