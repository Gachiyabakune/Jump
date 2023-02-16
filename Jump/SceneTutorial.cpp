#include "SceneTutorial.h"
#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"

void SceneTutorial::init()
{
}

SceneBase* SceneTutorial::update()
{
	if (Pad::isTrigger(PAD_INPUT_4))
	{
		return (new SceneTitle);
	}
	return this;
}

void SceneTutorial::draw()
{
	DrawString(200, 100, "�`���[�g���A��", GetColor(255, 255, 255), false);
}
