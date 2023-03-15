#include "SceneTitle.h"
#include "SceneResult.h"
#include "DxLib.h"
#include "SceneMain.h"
#include "Pad.h"

void SceneResult::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_isEnd = false;
}

SceneBase* SceneResult::update()
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneResult::draw()
{
	DrawString(4, 0, "Aボタンでジャンプ", GetColor(255, 255, 255));
	DrawString(4, 20, "長押しでジャンプ力が変わるよ", GetColor(255, 255, 255));
	DrawString(4, 40, "Yボタンでタイトルへ", GetColor(255, 255, 255));
}