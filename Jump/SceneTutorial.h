#pragma once
#include "SceneBase.h"
#include "Player2.h"
#include "EasyMap.h"
class SceneTutorial : public SceneBase
{
public:
	SceneTutorial()
	{
		m_seq = Seq::SeqFadeIn;
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
	//フェードインの時のUpdate関数
	void FadeInUpdate();
	//通常状態のUpdate関数
	void NormalUpdate();
	//クリア後のUpdate関数
	void ClearUpdate();
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate();

	virtual void drawClear();	//クリア後のdraw処理

	void refreshScore();
	int getHiScore();
private:
	Player2* player = new Player2;
	EasyMap* map = new EasyMap;

	enum class Seq
	{
		SeqFadeIn,			//フェード中
		SeqUpdata,			//通常のupdata
		SeqClearUpdata,		//クリア後のupdata
		SeqFadeOut,		//フェードアウト
	};
	// 現在のゲームシーケンス
	Seq m_seq;

	//フェード関係
	static constexpr int fade_interval = 60;
	int fadeTimer = fade_interval;		//フェードタイマー
	int fadeValue = 255;				//黒短形のブレンド具合

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

	//シーン切り替え
	bool changeScene;
};