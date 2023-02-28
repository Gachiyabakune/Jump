#pragma once
#include "SceneBase.h"
class SceneOption :
    public SceneBase
{
public:
	SceneOption() :
		m_handle(0)
	{
	}
	virtual ~SceneOption() {}


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	int m_handle;
};

