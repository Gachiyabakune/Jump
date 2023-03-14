#pragma once
#include "SceneBase.h"
#include "Player2.h"
#include "EasyMap.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial()
	{
		m_seq = Seq::SeqWait;
		m_timeTaken = 0;
		m_timer = 0;
		temp = 10000;
	}
	virtual ~SceneTutorial();


	virtual void init() override;
	virtual void end()override {}

	virtual SceneBase* update()override;
	virtual void draw()override;

private:
	virtual void updateWait();	//フェード中
	virtual void updateGame();	//ゲーム
	virtual void updateClear();	//クリア後のupdate処理

	virtual void drawClear();	//クリア後のdraw処理

	void refreshScore();
	int getHiScore();
private:
	Player2* player = new Player2;
	EasyMap* map = new EasyMap;

	enum class Seq
	{
		SeqWait,			//フェード中
		SeqUpdata,			//通常のupdata
		SeqClearUpdata,		//クリア後のupdata
	};
	// 現在のゲームシーケンス
	Seq m_seq;

	//かかった時間
	int m_timeTaken;
	int temp;
	int m_timer;
	//フォント関係
	int textHeight;
	int textWidth;
	int textDispWidth;
	int fontHandle;

	// 文字列グラフィックを生成
	int handle;

	//スコア
	int hiscore;
};