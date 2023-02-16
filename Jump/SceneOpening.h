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
	//　
	int m_displayCount;
	// タイトル背景
	int m_BackHandle;
	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;
};

