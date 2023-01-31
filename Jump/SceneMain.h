#pragma once
#include "SceneBase.h"
#include "Player.h"
#include "Map.h"
#include "game.h"

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();


	virtual void init();
	virtual void end() {}

	virtual SceneBase* update();
	virtual void draw();

private:
	
	int temp;
	int tempNum;
	int moveNum;
	bool idel;
	
	Player* player = new Player;
	Map* map = new Map;
};