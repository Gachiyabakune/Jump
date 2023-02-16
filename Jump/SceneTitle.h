#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
	SceneTitle()
	{
		m_boolerval = 0;
	}
	virtual ~SceneTitle() {}


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	bool m_boolerval;
	bool select1 = false;
	bool select2 = false;
	bool select3 = false;
	bool select4 = false;
};