#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "DxLib.h"
#include "Pad.h"
#include "Sound.h"
#include "game.h"


SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
	delete(player);
	delete(map);
}

void SceneMain::init()
{
	player->setStage(map);
	player->init();
	map->setPlayer(player);
	map->init();

	//BGM‚ğÄ¶
	Sound::startBgm(Sound::SoundId_BgmMain,100);
}

SceneBase* SceneMain::update()
{
	player->updata();
	map->updata();

	//ƒNƒŠƒA”»’è
	if (player->gameClear())
	{
		//effect->updata();
		return(new SceneResult);
	}


#ifdef _DEBUG
	if (Pad::isTrigger(PAD_INPUT_5))
	{
		return(new SceneTitle);
	}
#endif 
	return this;

	return this;
}

void SceneMain::draw()
{
	map->draw();
	player->draw();
}
