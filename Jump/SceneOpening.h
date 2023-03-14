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
	//　
	int m_displayCount;
	// タイトル
	int m_titleHandle;
	//デモ映像
	int m_clip;
	// テキスト点滅用フレームカウント
	int m_textBlinkFrame;
	//フォントの座標
	int m_fontX;
	int m_fontY;
	//フォントを上下移動させるためのsin
	float sinRate;
};

