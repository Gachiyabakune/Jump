#pragma once

#include "SceneBase.h"

class SceneManager
{
public:
	
public:
public:
	SceneManager();
	virtual ~SceneManager();

	void init();
	void end();

	void update();
	void draw();

private:
	SceneBase* m_pScene;
};
