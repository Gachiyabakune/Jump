#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle(){}
	virtual ~SceneTitle() {}


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	//bool select1 = false;
	//bool select2 = false;
	//bool select3 = false;
	//bool select4 = false;

	// カーソル移動
	int cursorIndex = 0;
	int cursorNext = 0;
	int cursorMoveFrame = 0;
	//フォント
	int menuItemHandle;
	//インターバル
	int m_interval;
	int frameCount = 0;
	//サイン
	float sinRate = 0.0f;
};