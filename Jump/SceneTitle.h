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
	// カーソル移動
	int cursorIndex;
	int cursorNext;
	int cursorMoveFrame;
	//フォント
	int menuItemHandle;
	//インターバル
	int m_interval;
	int frameCount;
	//サイン
	float sinRate;

	//宝箱を表示させるため
	int chip[40];
};