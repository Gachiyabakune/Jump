#pragma once
#include "SceneBase.h"
class SceneOpening : public SceneBase
{
public:
	SceneOpening() 
	{
		m_textBlinkFrame = 0;
		m_displayCount = 0;
		m_titleHandle = -1;
		m_clip = -1;
	}
	virtual ~SceneOpening() {}


	virtual void init() override;
	virtual void end()override;

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//�@
	int m_displayCount;
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
};

