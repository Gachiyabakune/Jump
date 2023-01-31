#include "SceneTitle.h"
#include "SceneResult.h"
#include "DxLib.h"
#include "SceneMain.h"

void SceneResult::init()
{
	m_textPosY = 0;
	m_textVecY = 4;

	m_handle = 0;
	m_isEnd = false;
}

SceneBase* SceneResult::update()
{
	return this;
}

void SceneResult::draw()
{
	DrawString(4, 0, "ƒGƒ“ƒh", GetColor(255, 255, 255));
}