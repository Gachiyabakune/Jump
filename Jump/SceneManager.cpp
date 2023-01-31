#include "SceneManager.h"
#include <cassert>

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneResult.h"


SceneManager::SceneManager() :
	m_pScene(nullptr)
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::init(SceneKind kind)
{
	m_kind = kind;
	switch (m_kind)
	{
	case SceneManager::kSceneKindTitle:
		m_pScene = new SceneTitle;
		break;
	/*case SceneManager::kSceneKindMy:
		m_pScene = new SceneResult;
		break;*/
	case SceneManager::kSceneKindMain:
		m_pScene = new SceneMain;
		break;
	case SceneManager::kSceneKindNum:
		m_pScene = new SceneResult;
		break;
	default:
		assert(false);
		break;
	}
	m_pScene->init();
}

void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->end();
	delete m_pScene;
}

void SceneManager::update()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	SceneBase* pScene = m_pScene->update();
	if (pScene != m_pScene)
	{
		//前のシーンの終了処理
		m_pScene->end();
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->init();
	}
}


void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene) return;

	m_pScene->draw();
}