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
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneResult::draw()
{
	DrawString(4, 0, "ƒGƒ“ƒh", GetColor(255, 255, 255));
}