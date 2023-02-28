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
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return(new SceneTitle);
	}
	return this;
}

void SceneResult::draw()
{
	DrawString(4, 0, "ゲームクリア", GetColor(255, 255, 255));

	SetFontSize(8);
	DrawString(600, 550, "BGM：hitoshi by Senses Circuit", GetColor(255, 255, 255), false);
	DrawString(600, 560, "https://www.senses-circuit.com", GetColor(255, 255, 255), false);
	SetFontSize(16);
}