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
}

SceneBase* SceneMain::update()
{
	player->updata();
	map->updata();
	
	static int volume, count = 0;
	volume = count * 4;
	if (count > 63) count = 63;
	count++;
	Sound::startBgm(Sound::SoundId_BgmMain,volume);

	//ƒNƒŠƒA”»’è
	if (player->gameClear())
	{
		return(new SceneResult);
	}

	return this;
}

void SceneMain::draw()
{
	map->draw();
	player->draw();
}
