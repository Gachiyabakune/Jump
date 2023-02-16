#pragma once
#include "SceneBase.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial() {}
	virtual ~SceneTutorial() {}


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
};