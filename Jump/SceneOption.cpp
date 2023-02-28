#include "SceneOption.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"

void SceneOption::init()
{
	m_handle = LoadGraph("Data/pad.png");
}

SceneBase* SceneOption::update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return (new SceneTitle);
	}
	return nullptr;
}

void SceneOption::draw()
{
	DrawGraph(0, 0, m_handle, false);   
}
