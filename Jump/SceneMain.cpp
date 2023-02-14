#include "SceneMain.h"
#include "SceneTitle.h"
#include "SceneResult.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"


SceneMain::SceneMain():
	temp(0),
	tempNum(0),
	moveNum(0),
	idel(false)
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
